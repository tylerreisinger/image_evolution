#include "MainWindow.h"

#include "ui_mainwindow.h"

#include <sstream>

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "EvolutionDriver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_gfx_scene = std::make_unique<QGraphicsScene>();
    m_state_render = new QGraphicsPixmapItem();
    m_gfx_scene->addItem(m_state_render);

    ui->state_viewer->setScene(m_gfx_scene.get());

    auto driver = initialize_evolution();

    m_bridge = std::make_unique<GuiBridge>(std::move(driver));
    m_driver = &m_bridge->evolution_driver();

    population_updated();
    //load_population();
    //update_gfx();

    setup_signals();
    update_state_button_status();

    m_bridge->start_evolution();
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::unique_ptr<EvolutionDriver> MainWindow::initialize_evolution()
{
    auto driver = std::make_unique<EvolutionDriver>();

    auto ref_image = Image::load_image("../../reference_images/rygcbm-hexagon.png");
    m_target_image = std::make_unique<Image>(std::move(ref_image));

    driver->set_target_image(m_target_image->clone());

    auto start_pop = make_random_fixed_size_population(40, 96, driver->get_rng());

    driver->set_population(std::move(start_pop));

    return driver;
}
 
void MainWindow::set_target_image(Image image)
{
    m_target_image = std::make_unique<Image>(std::move(image)); 
    m_driver->set_target_image(m_target_image->clone());
}
 
void MainWindow::advance_generation()
{
    m_bridge->step(); 
}
 
void MainWindow::update_gfx()
{
    auto& draw_state = m_display_pop[m_display_state_idx];  
    
    auto state_render = m_driver->evolver().render_state(draw_state); 

    QImage state_img = state_render.to_qimage();

    m_state_render->setPixmap(QPixmap::fromImage(state_img));
}

void MainWindow::load_population()
{
    std::tie(m_display_pop, m_gen_number) = m_bridge->get_current_evolution_state();
}
 
void MainWindow::setup_signals()
{
    connect(ui->next_state_button, &QPushButton::clicked,
            this, &MainWindow::next_state_clicked); 
    connect(ui->prev_state_button, &QPushButton::clicked,
            this, &MainWindow::prev_state_clicked); 

    connect(ui->next_generation_button, &QPushButton::clicked,
            this, &MainWindow::advance_generation);

    connect(m_bridge.get(), &GuiBridge::population_updated,
            this, &MainWindow::population_updated);

    connect(ui->toggle_evolution_button, &QPushButton::clicked,
            this, &MainWindow::evolution_toggle_clicked);
}
 
void MainWindow::next_state_clicked()
{
    m_display_state_idx += 1;
    update_state_button_status();
    state_updated();
    update_gfx();
}

void MainWindow::prev_state_clicked() {
    m_display_state_idx -= 1;
    update_state_button_status();
    state_updated();
    update_gfx();
}
 
void MainWindow::evolution_toggle_clicked()
{
    if(!m_running) {
        ui->toggle_evolution_button->setText("Stop Evolution");
        ui->next_generation_button->setEnabled(false);
        m_running = true;
        m_bridge->resume();
    } else {
        ui->toggle_evolution_button->setText("Start Evolution");
        ui->next_generation_button->setEnabled(true);
        m_running = false;
        m_bridge->pause();
    }
}
 
void MainWindow::update_state_button_status()
{
    if(m_display_state_idx == 0) {
        ui->prev_state_button->setDisabled(true); 
        ui->next_state_button->setDisabled(false);
    } else if(m_display_state_idx == m_display_pop.size()-1) {
        ui->prev_state_button->setDisabled(false); 
        ui->next_state_button->setDisabled(true);
    } else {
        ui->prev_state_button->setDisabled(false); 
        ui->next_state_button->setDisabled(false);
    }
}
 
void MainWindow::state_updated()
{
    std::stringstream state_num_text;
    state_num_text << "State " << m_display_state_idx+1 << " of " 
        << m_display_pop.size();
    ui->state_number_label->setText(state_num_text.str().c_str());

    std::stringstream state_score_text;
    state_score_text << "Score: " << m_display_pop[m_display_state_idx].score();
    ui->state_score_label->setText(state_score_text.str().c_str());
}
 
void MainWindow::population_updated()
{
    load_population();
    std::stringstream generation_text;
    generation_text << "Generation #" << m_gen_number;
    
    ui->generation_lbl->setText(generation_text.str().c_str());

    state_updated();
    update_gfx();
}
 
