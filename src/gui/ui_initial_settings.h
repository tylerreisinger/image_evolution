/********************************************************************************
** Form generated from reading UI file 'initial_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIAL_SETTINGS_H
#define UI_INITIAL_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InitialSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *rectangle_count;
    QLabel *label_2;
    QSpinBox *population_size;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okay_button;
    QPushButton *cancel_button;

    void setupUi(QDialog *InitialSettingsDialog)
    {
        if (InitialSettingsDialog->objectName().isEmpty())
            InitialSettingsDialog->setObjectName(QStringLiteral("InitialSettingsDialog"));
        InitialSettingsDialog->resize(270, 144);
        verticalLayout = new QVBoxLayout(InitialSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(InitialSettingsDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rectangle_count = new QSpinBox(InitialSettingsDialog);
        rectangle_count->setObjectName(QStringLiteral("rectangle_count"));
        rectangle_count->setMinimum(1);
        rectangle_count->setMaximum(500);

        formLayout->setWidget(0, QFormLayout::FieldRole, rectangle_count);

        label_2 = new QLabel(InitialSettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        population_size = new QSpinBox(InitialSettingsDialog);
        population_size->setObjectName(QStringLiteral("population_size"));
        population_size->setMinimum(1);
        population_size->setMaximum(1000);

        formLayout->setWidget(1, QFormLayout::FieldRole, population_size);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okay_button = new QPushButton(InitialSettingsDialog);
        okay_button->setObjectName(QStringLiteral("okay_button"));

        horizontalLayout->addWidget(okay_button);

        cancel_button = new QPushButton(InitialSettingsDialog);
        cancel_button->setObjectName(QStringLiteral("cancel_button"));

        horizontalLayout->addWidget(cancel_button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InitialSettingsDialog);

        QMetaObject::connectSlotsByName(InitialSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *InitialSettingsDialog)
    {
        InitialSettingsDialog->setWindowTitle(QApplication::translate("InitialSettingsDialog", "Dialog", 0));
        label->setText(QApplication::translate("InitialSettingsDialog", "Rectangle Count:", 0));
        label_2->setText(QApplication::translate("InitialSettingsDialog", "Population Size:", 0));
        okay_button->setText(QApplication::translate("InitialSettingsDialog", "Okay", 0));
        cancel_button->setText(QApplication::translate("InitialSettingsDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class InitialSettingsDialog: public Ui_InitialSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIAL_SETTINGS_H
