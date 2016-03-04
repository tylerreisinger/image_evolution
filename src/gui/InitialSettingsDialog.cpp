#include "InitialSettingsDialog.h"

#include "ui_initial_settings.h"

InitialSettingsDialog::InitialSettingsDialog(const InitialSettings& values,
        QWidget* parent):
    QDialog(parent),
    m_accepted_initial_settings(values),
    m_initial_settings(values),
    ui(std::make_unique<Ui::InitialSettingsDialog>())
{
    ui->setupUi(this);
    this->setWindowTitle("Initial Settings");

    setup_signals();
    update_ui();
}

InitialSettingsDialog::~InitialSettingsDialog() {
}

void InitialSettingsDialog::set_values(const InitialSettings& values) {
    m_initial_settings = values; 
    update_ui();
}
 
void InitialSettingsDialog::setup_signals() {
    connect(ui->rectangle_count,
            static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) {
                m_initial_settings.rectangle_count = value;
            });

    connect(ui->population_size, 
            static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value){
                m_initial_settings.population_size = value;
            }); 

    //Buttons
    connect(ui->okay_button, &QPushButton::clicked,
            this, [this]() {
                on_accept();
                this->hide();
            });    

    connect(ui->cancel_button, &QPushButton::clicked,
            this, [this]() {
                m_initial_settings = m_accepted_initial_settings;
                update_ui();
                this->hide();
            });

}
 
void InitialSettingsDialog::update_ui() {
    ui->rectangle_count->setValue(m_initial_settings.rectangle_count);
    ui->population_size->setValue(m_initial_settings.population_size);
}
 
void InitialSettingsDialog::on_accept() {
    m_accepted_initial_settings = m_initial_settings;
    emit values_accepted(); 
}
 
