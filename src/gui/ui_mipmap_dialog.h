/********************************************************************************
** Form generated from reading UI file 'mipmap_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIPMAP_DIALOG_H
#define UI_MIPMAP_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MipmapDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_5;
    QSpinBox *mipmap_value;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QDoubleSpinBox *enlarge_threshold_value;
    QSpinBox *min_mipmap_value;
    QLabel *label_4;
    QLabel *label_3;
    QSpinBox *max_mipmap_value;
    QCheckBox *is_adaptive_enabled;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okay_button;
    QPushButton *cancel_button;
    QPushButton *apply_button;

    void setupUi(QDialog *MipmapDialog)
    {
        if (MipmapDialog->objectName().isEmpty())
            MipmapDialog->setObjectName(QStringLiteral("MipmapDialog"));
        MipmapDialog->resize(448, 327);
        verticalLayout = new QVBoxLayout(MipmapDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_5 = new QLabel(MipmapDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        mipmap_value = new QSpinBox(MipmapDialog);
        mipmap_value->setObjectName(QStringLiteral("mipmap_value"));
        mipmap_value->setMaximum(10);

        formLayout->setWidget(1, QFormLayout::FieldRole, mipmap_value);


        verticalLayout->addLayout(formLayout);

        groupBox = new QGroupBox(MipmapDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        enlarge_threshold_value = new QDoubleSpinBox(groupBox);
        enlarge_threshold_value->setObjectName(QStringLiteral("enlarge_threshold_value"));
        enlarge_threshold_value->setDecimals(8);
        enlarge_threshold_value->setMinimum(0);
        enlarge_threshold_value->setMaximum(1);
        enlarge_threshold_value->setSingleStep(2.5e-05);
        enlarge_threshold_value->setValue(0);

        gridLayout_2->addWidget(enlarge_threshold_value, 3, 1, 1, 1);

        min_mipmap_value = new QSpinBox(groupBox);
        min_mipmap_value->setObjectName(QStringLiteral("min_mipmap_value"));
        min_mipmap_value->setMaximum(10);

        gridLayout_2->addWidget(min_mipmap_value, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        max_mipmap_value = new QSpinBox(groupBox);
        max_mipmap_value->setObjectName(QStringLiteral("max_mipmap_value"));
        max_mipmap_value->setMaximum(10);

        gridLayout_2->addWidget(max_mipmap_value, 2, 1, 1, 1);

        is_adaptive_enabled = new QCheckBox(groupBox);
        is_adaptive_enabled->setObjectName(QStringLiteral("is_adaptive_enabled"));

        gridLayout_2->addWidget(is_adaptive_enabled, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okay_button = new QPushButton(MipmapDialog);
        okay_button->setObjectName(QStringLiteral("okay_button"));

        horizontalLayout->addWidget(okay_button);

        cancel_button = new QPushButton(MipmapDialog);
        cancel_button->setObjectName(QStringLiteral("cancel_button"));

        horizontalLayout->addWidget(cancel_button);

        apply_button = new QPushButton(MipmapDialog);
        apply_button->setObjectName(QStringLiteral("apply_button"));

        horizontalLayout->addWidget(apply_button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MipmapDialog);

        QMetaObject::connectSlotsByName(MipmapDialog);
    } // setupUi

    void retranslateUi(QDialog *MipmapDialog)
    {
        MipmapDialog->setWindowTitle(QApplication::translate("MipmapDialog", "Mipmap Settings", 0));
        label_5->setText(QApplication::translate("MipmapDialog", "Mipmap Level:", 0));
        groupBox->setTitle(QApplication::translate("MipmapDialog", "Adaptive Scaling", 0));
        label->setText(QApplication::translate("MipmapDialog", "Minimum Mipmap Level:", 0));
        enlarge_threshold_value->setPrefix(QString());
        enlarge_threshold_value->setSuffix(QApplication::translate("MipmapDialog", "%", 0));
        label_4->setText(QApplication::translate("MipmapDialog", "Enlarge Max Threshold:", 0));
        label_3->setText(QApplication::translate("MipmapDialog", "Maximum Mipmap Level:", 0));
        is_adaptive_enabled->setText(QApplication::translate("MipmapDialog", "Use Adaptive Scaling", 0));
        okay_button->setText(QApplication::translate("MipmapDialog", "Okay", 0));
        cancel_button->setText(QApplication::translate("MipmapDialog", "Cancel", 0));
        apply_button->setText(QApplication::translate("MipmapDialog", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class MipmapDialog: public Ui_MipmapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIPMAP_DIALOG_H
