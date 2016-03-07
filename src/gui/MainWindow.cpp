#include "MainWindow.h"

#include "ui_mainwindow.h"

#include <sstream>

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

#include "EvolutionDriver.h"
#include "Image.h"
#include "MutateDialog.h"
#include "InitialSettingsDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Evolution");

    m_gfx_scene = std::make_unique<QGraphicsScene>();
    m_state_render = new QGraphicsPixmapItem();
    m_reference_render = new QGraphicsPixmapItem();
    m_gfx_scene->addItem(m_state_render);
    m_gfx_scene->addItem(m_reference_render);
    on_opacity_change();

    ui->state_viewer->setScene(m_gfx_scene.get());

    setup_signals();

    set_simulation_unloaded_state();
    update_simulation_buttons();
    update_state_button_status();
    state_updated();
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::unique_ptr<EvolutionDriver> MainWindow::initialize_evolution(
        std::unique_ptr<Image> image)
{
    auto driver = std::make_unique<EvolutionDriver>();

    driver->set_target_image(std::move(image));

    auto start_pop = make_initial_population(driver->get_rng());

    driver->set_population(std::move(start_pop));

    return driver;
}
 
void MainWindow::set_target_image(std::unique_ptr<Image> image)
{
    auto qimage = image->to_qimage();
    m_reference_render->setPixmap(QPixmap::fromImage(qimage));
    reset_evolution(std::move(image));
}
 
void MainWindow::advance_generation()
{
    m_bridge->step(); 
}
 
void MainWindow::update_gfx()
{
    auto& draw_state = m_display_pop[m_display_state_idx];  
    
    auto state_render = m_driver->render_state(draw_state); 

    QImage state_img = state_render->to_qimage();

    m_state_render->setPixmap(QPixmap::fromImage(state_img));
}

void MainWindow::load_population()
{
    std::tie(m_display_pop, m_gen_number) = m_bridge->get_current_evolution_state();
}
 
Population MainWindow::make_initial_population(ImageEvolver::GeneratorType& rng)
{
    return make_random_fixed_size_population(m_initial_settings.population_size, 
            m_initial_settings.rectangle_count * 8, rng);
}
 
void MainWindow::setup_signals()
{
    //Main GUI
    connect(ui->next_state_button, &QPushButton::clicked,
            this, &MainWindow::next_state_clicked); 
    connect(ui->prev_state_button, &QPushButton::clicked,
            this, &MainWindow::prev_state_clicked); 

    connect(ui->next_generation_button, &QPushButton::clicked,
            this, &MainWindow::advance_generation);

    connect(ui->toggle_evolution_button, &QPushButton::clicked,
            this, &MainWindow::evolution_toggle_clicked);

    connect(ui->opacity_slider, &QSlider::valueChanged,
            this, &MainWindow::on_opacity_change);

    //Context menu
    //File
    connect(ui->action_Save_Current_State, &QAction::triggered,
            this, &MainWindow::handle_save_state_image);

    connect(ui->action_Load_Reference_Image, &QAction::triggered,
            this, &MainWindow::on_open_image);

    //Simulation
    connect(ui->action_Reset, &QAction::triggered,
            this, &MainWindow::reset_simulation);

    connect(ui->actionConfigure_Mutations, &QAction::triggered,
            this, &MainWindow::open_mutation_config);

    connect(ui->action_Initial_Settings, &QAction::triggered,
            this, &MainWindow::open_initial_settings_dialog);
}
 
void MainWindow::next_state_clicked()
{
    set_active_state(m_display_state_idx + 1);
    update_gfx();
}

void MainWindow::prev_state_clicked() {
    set_active_state(m_display_state_idx - 1);
    update_gfx();
}
 
void MainWindow::evolution_toggle_clicked()
{
    if(!m_running) {
        m_running = true;
        m_bridge->resume();
    } else {
        m_running = false;
        m_bridge->pause();
    }
    update_simulation_buttons();
}
 
void MainWindow::update_state_button_status()
{
    if(m_display_state_idx == 0) {
        if(m_display_pop.size() > 0) {
            ui->next_state_button->setDisabled(false);
        } else {
            ui->next_state_button->setDisabled(true);
        }
        ui->prev_state_button->setDisabled(true); 
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
    auto num_states = m_display_pop.size();
    auto state_num = m_display_state_idx;
    if(num_states > 0) {
        state_num += 1;
    }

    std::stringstream state_num_text;
    state_num_text << "State " << state_num << " of " 
        << num_states;
    ui->state_number_label->setText(state_num_text.str().c_str());

    if(num_states > 0) {
        std::stringstream state_score_text;
        state_score_text << "Score: " << m_display_pop[m_display_state_idx].score();
        ui->state_score_label->setText(state_score_text.str().c_str());
    }
    update_state_button_status();
}
 
void MainWindow::population_updated()
{
    load_population();
    std::stringstream generation_text;
    generation_text << "Generation #" << m_gen_number;
    
    ui->generation_lbl->setText(generation_text.str().c_str());

    auto avg_score = m_display_pop.total_score() / m_display_pop.size();

    std::stringstream avg_score_text;
    avg_score_text << "Average Score: " << avg_score;
    ui->average_score_label->setText(avg_score_text.str().c_str());

    std::stringstream best_score_text;
    best_score_text << "Best Score: " << m_display_pop[0].score();
    ui->best_score_label->setText(best_score_text.str().c_str());

    state_updated();
    update_gfx();
}
 
void MainWindow::open_mutation_config()
{
    if(m_mutate_dialog == nullptr) {
        m_mutate_dialog = std::make_unique<MutateDialog>(m_mutator);

        connect(m_mutate_dialog.get(), &MutateDialog::values_accepted,
               this, &MainWindow::set_mutator);
    }
    m_mutate_dialog->set_mutator(m_mutator);
    m_mutate_dialog->show();
}
 
void MainWindow::open_initial_settings_dialog()
{
    if(m_initial_settings_dialog == nullptr) {
        m_initial_settings_dialog = 
            std::make_unique<InitialSettingsDialog>(m_initial_settings);

        connect(m_initial_settings_dialog.get(), &InitialSettingsDialog::values_accepted,
                this, &MainWindow::set_initial_settings);
    } 
    m_initial_settings_dialog->set_values(m_initial_settings);
    m_initial_settings_dialog->show();
}
 
void MainWindow::set_mutator()
{
    m_mutator = m_mutate_dialog->mutator();
    if(has_loaded_simulation()) {
        m_driver->evolver().set_mutator(std::make_unique<Mutator>(m_mutator));
    }
}
 
void MainWindow::set_initial_settings()
{
    m_initial_settings = m_initial_settings_dialog->values(); 
}
 
void MainWindow::on_opacity_change()
{
    m_reference_render->setOpacity(ui->opacity_slider->value() / 100.0); 
}
 
void MainWindow::handle_save_state_image()
{
    auto selected_state = m_display_pop[m_display_state_idx];
    auto filename = QFileDialog::getSaveFileName(this, "Save State Image", ".", 
            "Image Files (*.png *.bmp *.jpg)").toStdString();

    if(!filename.empty()) {
        auto img = m_driver->evolver().render_state(selected_state);

        if(!save_image(filename, *img)) {
            QMessageBox msg;
            auto message = "Unable to save file '" + filename + "'.";
            msg.setText(message.c_str());
            msg.exec();
        }
    }
}
 
void MainWindow::reset_simulation()
{
    auto pop = make_initial_population(m_driver->get_rng());
    m_bridge->reinitialize_population(std::move(pop));

    set_simulation_loaded_state();
    set_active_state(0);
    m_running = false;
    update_simulation_buttons();

    population_updated();
}
 
void MainWindow::on_open_image(bool)
{
    auto filename = QFileDialog::getOpenFileName(this, "Open Reference Image", ".",
           "Image Files(*.png *.bmp *.jpg)").toStdString();

    if(!filename.empty()) {
        auto img = Image::load_image(filename);
        if(img == nullptr) {
            QMessageBox msg;
            auto message = "Unable to load image '" + filename + "'.";
            msg.setText(message.c_str());
            msg.exec();
        } else {
            set_target_image(std::move(img));
        }

    }
}
 
void MainWindow::reset_evolution(std::unique_ptr<Image> new_image)
{
    if(m_bridge != nullptr) {
        m_bridge->stop();
        m_bridge->join();
    }

    auto driver = initialize_evolution(std::move(new_image));

    m_bridge = std::make_unique<GuiBridge>(std::move(driver));
    m_driver = &m_bridge->evolution_driver();
    m_driver->evolver().set_mutator(std::make_unique<Mutator>(m_mutator));

    connect(m_bridge.get(), &GuiBridge::population_updated,
            this, &MainWindow::population_updated);

    set_simulation_loaded_state();
    set_active_state(0);

    m_running = false;
    update_simulation_buttons();

    population_updated();
}
 
void MainWindow::update_simulation_buttons()
{
    if(m_running) {
        ui->toggle_evolution_button->setText("Stop Evolution");
        ui->next_generation_button->setEnabled(false);
    } else {
        ui->toggle_evolution_button->setText("Start Evolution");
        ui->next_generation_button->setEnabled(true);
    }

    if(!has_loaded_simulation()) {
        ui->next_generation_button->setEnabled(false);
        ui->toggle_evolution_button->setEnabled(false);
    }
}
 
void MainWindow::set_active_state(int idx)
{
    if(idx < m_display_pop.size()) {
        m_display_state_idx = idx;
        update_state_button_status();
        state_updated();
    }
}
 
void MainWindow::set_simulation_unloaded_state()
{
    ui->action_Reset->setEnabled(false);   
    ui->action_Save_Current_State->setEnabled(false);

    ui->next_generation_button->setEnabled(false);
    ui->toggle_evolution_button->setEnabled(false);
}
 
void MainWindow::set_simulation_loaded_state()
{
    ui->action_Reset->setEnabled(true);   
    ui->action_Save_Current_State->setEnabled(true);

    ui->next_generation_button->setEnabled(true);
    ui->toggle_evolution_button->setEnabled(true);
}
 
