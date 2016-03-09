#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include <QGraphicsScene>

#include "GuiBridge.h"
#include "Population.h"
#include "ImageEvolver.h"
#include "InitialSettings.h"
#include "MipmapSettings.h"

class EvolutionDriver;

class MutateDialog;
class InitialSettingsDialog;
class MipmapDialog;
class AdaptiveScalingController;

class QLabel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_target_image(std::unique_ptr<Image> image);

    bool has_loaded_simulation() const {return m_bridge != nullptr;}

    void advance_generation();
private:
    void setup_statusbar();

    void update_gfx();
    void load_population();

    Population make_initial_population(ImageEvolver::GeneratorType& rng);

    void setup_signals();
    void next_state_clicked();
    void prev_state_clicked();
    void evolution_toggle_clicked();
    void update_state_button_status();

    void state_updated();
    void population_updated();

    void reset_simulation();

    void on_open_image(bool);

    void open_mutation_config();
    void open_initial_settings_dialog();
    void open_mipmap_settings_dialog();
    void set_mutator();
    void set_initial_settings();
    void set_mipmap_settings();

    void on_update_tick();
    void on_opacity_change();
    void on_save_state_image(bool);
    void handle_save_state_image();

    std::unique_ptr<AdaptiveScalingController> make_scaling_controller(
            const MipmapSettings& settings) const;

    void reset_evolution(std::unique_ptr<Image> new_image);

    void update_simulation_buttons();

    void set_active_state(int idx);

    void set_simulation_unloaded_state();
    void set_simulation_loaded_state();

    void update_population_info_display();

    std::unique_ptr<EvolutionDriver> initialize_evolution(std::unique_ptr<Image> image);

    Ui::MainWindow* ui; 
    std::unique_ptr<QGraphicsScene> m_gfx_scene;
    QGraphicsPixmapItem* m_state_render;
    QGraphicsPixmapItem* m_reference_render = nullptr;
    std::unique_ptr<GuiBridge> m_bridge;
    EvolutionDriver* m_driver;

    std::unique_ptr<MutateDialog> m_mutate_dialog;
    std::unique_ptr<InitialSettingsDialog> m_initial_settings_dialog;
    std::unique_ptr<MipmapDialog> m_mipmap_dialog;

    InitialSettings m_initial_settings;
    MipmapSettings m_mipmap_settings;
    Mutator m_mutator;

    QTimer* m_update_timer;

    //Status bar controls
    QLabel* m_open_file_label;

    Population m_display_pop;
    int m_gen_number = 0;
    int m_display_state_idx = 0;
    bool m_running = false;

    int m_update_delay_ms = 50;
};

#endif // MAINWINDOW_H
