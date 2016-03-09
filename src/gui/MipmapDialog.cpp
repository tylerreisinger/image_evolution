#include "MipmapDialog.h"

#include "ui_mipmap_dialog.h"

MipmapDialog::MipmapDialog(const MipmapSettings& values, QWidget* parent):
    QDialog(parent),
    ui(new Ui::MipmapDialog())
{
    ui->setupUi(this);

    setup_signals();
    set_values(values);
}

MipmapDialog::~MipmapDialog()
{
 
}
 
void MipmapDialog::set_values(const MipmapSettings& values)
{
    m_values = values;
    m_accepted_values = values;
    update_ui();
}
 
void MipmapDialog::update_is_adaptive_scaling_enabled(bool val)
{
    ui->min_mipmap_value->setEnabled(val);
    ui->max_mipmap_value->setEnabled(val);
    ui->enlarge_threshold_value->setEnabled(val);
}
 
void MipmapDialog::setup_signals()
{
    connect(ui->mipmap_value, 
            static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int new_val) {
                m_values.current_mipmap_level = new_val;
            });

    connect(ui->min_mipmap_value,
            static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int new_val) {
                m_values.initial_mipmap_level = new_val;
            });

    connect(ui->max_mipmap_value,
            static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int new_val) {
                m_values.final_mipmap_level = new_val;
            });

    connect(ui->enlarge_threshold_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double new_val) {
                m_values.enlarge_threshold_base = new_val/100.0;
            });

    connect(ui->is_adaptive_enabled, &QCheckBox::stateChanged,
            this, &MipmapDialog::on_adaptive_scaling_checked);

    //Buttons
    connect(ui->apply_button, &QPushButton::clicked,
            this, &MipmapDialog::on_accept);

    connect(ui->okay_button, &QPushButton::clicked,
            this, [this]() {
                on_accept();
                this->hide();
            });

    connect(ui->cancel_button, &QPushButton::clicked,
            this, [this]() {
                m_values = m_accepted_values;
                update_ui();
                this->hide();
            });

}
 
void MipmapDialog::update_ui()
{  
    ui->mipmap_value->setValue(m_values.current_mipmap_level);
    ui->min_mipmap_value->setValue(m_values.initial_mipmap_level);
    ui->max_mipmap_value->setValue(m_values.final_mipmap_level);
    ui->enlarge_threshold_value->setValue(m_values.enlarge_threshold_base*100);
    ui->is_adaptive_enabled->setChecked(m_values.is_adaptive_scaling_enabled);
    update_is_adaptive_scaling_enabled(m_values.is_adaptive_scaling_enabled);
}
 
void MipmapDialog::on_accept()
{
    m_accepted_values = m_values;
    emit values_accepted(); 
}
 
void MipmapDialog::on_adaptive_scaling_checked(int val)
{
    bool bool_value = static_cast<bool>(val);
    m_values.is_adaptive_scaling_enabled = bool_value;
    update_is_adaptive_scaling_enabled(bool_value);
}
 
