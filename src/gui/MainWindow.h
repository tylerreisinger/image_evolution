#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include <QGraphicsScene>

#include "GuiBridge.h"

class EvolutionDriver;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_target_image(Image image);


    void advance_generation();
private:
    void update_gfx();
    void load_population();

    void setup_signals();
    void next_state_clicked();
    void prev_state_clicked();
    void evolution_toggle_clicked();
    void update_state_button_status();

    void state_updated();
    void population_updated();

    void on_open_image(bool);

    void on_save_state_image(bool);
    void handle_save_state_image();

    void reset_evolution(Image new_image);

    std::unique_ptr<EvolutionDriver> initialize_evolution(Image image);

    Ui::MainWindow* ui; 
    std::unique_ptr<QGraphicsScene> m_gfx_scene;
    QGraphicsPixmapItem* m_state_render;
    std::unique_ptr<GuiBridge> m_bridge;
    EvolutionDriver* m_driver;
    std::unique_ptr<Image> m_target_image;

    Population m_display_pop;
    int m_gen_number = 0;
    int m_display_state_idx = 0;
    bool m_running = false;
};

#endif // MAINWINDOW_H
