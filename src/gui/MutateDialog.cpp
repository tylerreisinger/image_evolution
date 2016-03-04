#include "MutateDialog.h"

#include "ui_mutation_options.h"

MutateDialog::MutateDialog(const Mutator& mutator, QWidget* parent):
    QDialog(parent),
    ui(std::make_unique<Ui::MutateDialog>()),
    m_mutator(std::make_unique<Mutator>(mutator))
{
    ui->setupUi(this);
    this->setWindowTitle("Mutation Configuration");

    update_ui();
    setup_signals();
}

MutateDialog::~MutateDialog()
{
 
}
 
void MutateDialog::setup_signals() {
    //Sliders
    connect(ui->mutation_rate_value, 
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->mutation_rate_slider->setValue(val*10.0); 
                m_mutator->set_mutation_rate(val/100.0);
            });

    connect(ui->mutation_rate_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->mutation_rate_value->setValue(val/10.0);
            });

    connect(ui->element_mutation_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->element_mutation_slider->setValue(val);
                m_mutator->set_element_mutation_rate(val/100.0);
            });

    connect(ui->element_mutation_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->element_mutation_value->setValue(val);
            });

    connect(ui->component_mutation_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->component_mutation_slider->setValue(val);
                m_mutator->set_component_mutation_rate(val/100.0);
            });

    connect(ui->component_mutation_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->component_mutation_value->setValue(val);
            });

    connect(ui->perturbation_width_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->perturbation_width_slider->setValue(val);
                m_mutator->set_perturbation_width(val/100.0);
            });

    connect(ui->perturbation_width_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->perturbation_width_value->setValue(val);
            });

    connect(ui->perturbation_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->perturbation_slider->setValue(val);
                m_mutator->set_perturbation_chance(val/100.0);
                
                if(m_mutator->perturbation_chance() + m_mutator->swap_chance() > 1.0) {
                    ui->swap_value->setValue(100*(1.0 - m_mutator->perturbation_chance()));
                }
                update_replace_values();
            });

    connect(ui->perturbation_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->perturbation_value->setValue(val);
            });

    connect(ui->swap_value,
            static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, [this](double val) {
                ui->swap_slider->setValue(val);
                m_mutator->set_swap_chance(val/100.0);

                if(m_mutator->perturbation_chance() + m_mutator->swap_chance() > 1.0) {
                    ui->perturbation_value->setValue(100*(1.0 - m_mutator->swap_chance()));
                }
                update_replace_values();
            });

    connect(ui->swap_slider, &QSlider::valueChanged,
            this, [this](int val) {
                ui->swap_value->setValue(val);
            });

    //Buttons
    connect(ui->accept_button, &QPushButton::clicked,
            this, &MutateDialog::on_accept);

}
 
void MutateDialog::update_ui()
{
    ui->mutation_rate_slider->setValue(m_mutator->mutation_rate()*100);
    ui->mutation_rate_value->setValue(m_mutator->mutation_rate()*100);

    ui->element_mutation_slider->setValue(m_mutator->element_mutation_rate()*100);
    ui->element_mutation_value->setValue(m_mutator->element_mutation_rate()*100);

    ui->component_mutation_slider->setValue(m_mutator->component_mutation_rate()*100);
    ui->component_mutation_value->setValue(m_mutator->component_mutation_rate()*100);

    ui->perturbation_width_slider->setValue(m_mutator->perturbation_width()*100);
    ui->perturbation_width_value->setValue(m_mutator->perturbation_width()*100);

    ui->perturbation_slider->setValue(m_mutator->perturbation_chance()*100);
    ui->perturbation_value->setValue(m_mutator->perturbation_chance()*100);

    ui->swap_slider->setValue(m_mutator->swap_chance()*100);
    ui->swap_value->setValue(m_mutator->swap_chance()*100);

    update_replace_values();
}
 
void MutateDialog::update_replace_values()
{
    ui->replace_value->setValue(m_mutator->replace_chance()*100); 
    ui->replace_slider->setValue(m_mutator->replace_chance()*100); 
}
 
void MutateDialog::on_accept()
{
    emit values_accepted();
}
