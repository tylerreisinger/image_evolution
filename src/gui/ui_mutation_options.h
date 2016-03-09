/********************************************************************************
** Form generated from reading UI file 'mutation_options.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_OPTIONS_H
#define UI_MUTATION_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MutateDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *swap_value;
    QDoubleSpinBox *replace_value;
    QSlider *mutation_rate_slider;
    QDoubleSpinBox *component_mutation_value;
    QSlider *element_mutation_slider;
    QLabel *label_3;
    QDoubleSpinBox *mutation_rate_value;
    QDoubleSpinBox *element_mutation_value;
    QDoubleSpinBox *perturbation_value;
    QLabel *label_7;
    QLabel *label_5;
    QSlider *component_mutation_slider;
    QSlider *perturbation_slider;
    QSlider *replace_slider;
    QSlider *swap_slider;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_2;
    QSlider *perturbation_width_slider;
    QDoubleSpinBox *perturbation_width_value;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okay_button;
    QPushButton *cancel_button;
    QPushButton *apply_button;

    void setupUi(QDialog *MutateDialog)
    {
        if (MutateDialog->objectName().isEmpty())
            MutateDialog->setObjectName(QStringLiteral("MutateDialog"));
        MutateDialog->resize(556, 349);
        verticalLayout = new QVBoxLayout(MutateDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(MutateDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        swap_value = new QDoubleSpinBox(MutateDialog);
        swap_value->setObjectName(QStringLiteral("swap_value"));
        swap_value->setDecimals(1);
        swap_value->setMaximum(100);

        gridLayout->addWidget(swap_value, 5, 2, 1, 1);

        replace_value = new QDoubleSpinBox(MutateDialog);
        replace_value->setObjectName(QStringLiteral("replace_value"));
        replace_value->setEnabled(false);
        replace_value->setButtonSymbols(QAbstractSpinBox::NoButtons);
        replace_value->setDecimals(1);
        replace_value->setMaximum(100);

        gridLayout->addWidget(replace_value, 6, 2, 1, 1);

        mutation_rate_slider = new QSlider(MutateDialog);
        mutation_rate_slider->setObjectName(QStringLiteral("mutation_rate_slider"));
        mutation_rate_slider->setMaximum(1000);
        mutation_rate_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(mutation_rate_slider, 0, 1, 1, 1);

        component_mutation_value = new QDoubleSpinBox(MutateDialog);
        component_mutation_value->setObjectName(QStringLiteral("component_mutation_value"));
        component_mutation_value->setDecimals(1);
        component_mutation_value->setMaximum(100);
        component_mutation_value->setSingleStep(1);

        gridLayout->addWidget(component_mutation_value, 2, 2, 1, 1);

        element_mutation_slider = new QSlider(MutateDialog);
        element_mutation_slider->setObjectName(QStringLiteral("element_mutation_slider"));
        element_mutation_slider->setMaximum(100);
        element_mutation_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(element_mutation_slider, 1, 1, 1, 1);

        label_3 = new QLabel(MutateDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        mutation_rate_value = new QDoubleSpinBox(MutateDialog);
        mutation_rate_value->setObjectName(QStringLiteral("mutation_rate_value"));
        mutation_rate_value->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        mutation_rate_value->setProperty("showGroupSeparator", QVariant(false));
        mutation_rate_value->setSuffix(QStringLiteral("%"));
        mutation_rate_value->setDecimals(2);
        mutation_rate_value->setMaximum(100);
        mutation_rate_value->setSingleStep(0.1);

        gridLayout->addWidget(mutation_rate_value, 0, 2, 1, 1);

        element_mutation_value = new QDoubleSpinBox(MutateDialog);
        element_mutation_value->setObjectName(QStringLiteral("element_mutation_value"));
        element_mutation_value->setDecimals(1);
        element_mutation_value->setMaximum(100);
        element_mutation_value->setSingleStep(1);

        gridLayout->addWidget(element_mutation_value, 1, 2, 1, 1);

        perturbation_value = new QDoubleSpinBox(MutateDialog);
        perturbation_value->setObjectName(QStringLiteral("perturbation_value"));
        perturbation_value->setDecimals(1);

        gridLayout->addWidget(perturbation_value, 4, 2, 1, 1);

        label_7 = new QLabel(MutateDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_5 = new QLabel(MutateDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        component_mutation_slider = new QSlider(MutateDialog);
        component_mutation_slider->setObjectName(QStringLiteral("component_mutation_slider"));
        component_mutation_slider->setMaximum(100);
        component_mutation_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(component_mutation_slider, 2, 1, 1, 1);

        perturbation_slider = new QSlider(MutateDialog);
        perturbation_slider->setObjectName(QStringLiteral("perturbation_slider"));
        perturbation_slider->setMaximum(100);
        perturbation_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(perturbation_slider, 4, 1, 1, 1);

        replace_slider = new QSlider(MutateDialog);
        replace_slider->setObjectName(QStringLiteral("replace_slider"));
        replace_slider->setEnabled(false);
        replace_slider->setMaximum(100);
        replace_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(replace_slider, 6, 1, 1, 1);

        swap_slider = new QSlider(MutateDialog);
        swap_slider->setObjectName(QStringLiteral("swap_slider"));
        swap_slider->setMaximum(100);
        swap_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(swap_slider, 5, 1, 1, 1);

        label_9 = new QLabel(MutateDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        label_11 = new QLabel(MutateDialog);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        label_2 = new QLabel(MutateDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        perturbation_width_slider = new QSlider(MutateDialog);
        perturbation_width_slider->setObjectName(QStringLiteral("perturbation_width_slider"));
        perturbation_width_slider->setMaximum(50);
        perturbation_width_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(perturbation_width_slider, 3, 1, 1, 1);

        perturbation_width_value = new QDoubleSpinBox(MutateDialog);
        perturbation_width_value->setObjectName(QStringLiteral("perturbation_width_value"));
        perturbation_width_value->setDecimals(1);
        perturbation_width_value->setMaximum(50);
        perturbation_width_value->setSingleStep(1);

        gridLayout->addWidget(perturbation_width_value, 3, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        okay_button = new QPushButton(MutateDialog);
        okay_button->setObjectName(QStringLiteral("okay_button"));

        horizontalLayout->addWidget(okay_button);

        cancel_button = new QPushButton(MutateDialog);
        cancel_button->setObjectName(QStringLiteral("cancel_button"));

        horizontalLayout->addWidget(cancel_button);

        apply_button = new QPushButton(MutateDialog);
        apply_button->setObjectName(QStringLiteral("apply_button"));

        horizontalLayout->addWidget(apply_button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MutateDialog);

        QMetaObject::connectSlotsByName(MutateDialog);
    } // setupUi

    void retranslateUi(QDialog *MutateDialog)
    {
        MutateDialog->setWindowTitle(QApplication::translate("MutateDialog", "Dialog", 0));
        label->setText(QApplication::translate("MutateDialog", "Mutation Rate:", 0));
        swap_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        replace_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        component_mutation_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        label_3->setText(QApplication::translate("MutateDialog", "Element Mutation Rate:", 0));
        element_mutation_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        perturbation_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        label_7->setText(QApplication::translate("MutateDialog", "Perturbation Chance:", 0));
        label_5->setText(QApplication::translate("MutateDialog", "Component Mutation Rate:", 0));
#ifndef QT_NO_STATUSTIP
        perturbation_slider->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_9->setText(QApplication::translate("MutateDialog", "Swap Chance:", 0));
        label_11->setText(QApplication::translate("MutateDialog", "Replace Chance:", 0));
        label_2->setText(QApplication::translate("MutateDialog", "Perturbation Width:", 0));
        perturbation_width_value->setSuffix(QApplication::translate("MutateDialog", "%", 0));
        okay_button->setText(QApplication::translate("MutateDialog", "Okay", 0));
        cancel_button->setText(QApplication::translate("MutateDialog", "Cancel", 0));
        apply_button->setText(QApplication::translate("MutateDialog", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class MutateDialog: public Ui_MutateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_OPTIONS_H
