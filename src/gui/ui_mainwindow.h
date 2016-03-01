/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *generation_lbl;
    QGraphicsView *state_viewer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *average_score_label;
    QLabel *best_score_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *state_number_label;
    QLabel *state_score_label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *prev_state_button;
    QPushButton *next_state_button;
    QVBoxLayout *verticalLayout_3;
    QPushButton *toggle_evolution_button;
    QPushButton *next_generation_button;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        generation_lbl = new QLabel(centralWidget);
        generation_lbl->setObjectName(QStringLiteral("generation_lbl"));

        verticalLayout->addWidget(generation_lbl);

        state_viewer = new QGraphicsView(centralWidget);
        state_viewer->setObjectName(QStringLiteral("state_viewer"));

        verticalLayout->addWidget(state_viewer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        average_score_label = new QLabel(centralWidget);
        average_score_label->setObjectName(QStringLiteral("average_score_label"));

        horizontalLayout_3->addWidget(average_score_label);

        best_score_label = new QLabel(centralWidget);
        best_score_label->setObjectName(QStringLiteral("best_score_label"));

        horizontalLayout_3->addWidget(best_score_label);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        state_number_label = new QLabel(centralWidget);
        state_number_label->setObjectName(QStringLiteral("state_number_label"));

        horizontalLayout_2->addWidget(state_number_label);

        state_score_label = new QLabel(centralWidget);
        state_score_label->setObjectName(QStringLiteral("state_score_label"));

        horizontalLayout_2->addWidget(state_score_label);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        prev_state_button = new QPushButton(centralWidget);
        prev_state_button->setObjectName(QStringLiteral("prev_state_button"));

        verticalLayout_2->addWidget(prev_state_button);

        next_state_button = new QPushButton(centralWidget);
        next_state_button->setObjectName(QStringLiteral("next_state_button"));

        verticalLayout_2->addWidget(next_state_button);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        toggle_evolution_button = new QPushButton(centralWidget);
        toggle_evolution_button->setObjectName(QStringLiteral("toggle_evolution_button"));

        verticalLayout_3->addWidget(toggle_evolution_button);

        next_generation_button = new QPushButton(centralWidget);
        next_generation_button->setObjectName(QStringLiteral("next_generation_button"));

        verticalLayout_3->addWidget(next_generation_button);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 26));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        generation_lbl->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        average_score_label->setText(QApplication::translate("MainWindow", "Average Score:", 0));
        best_score_label->setText(QApplication::translate("MainWindow", "Best Score:", 0));
        state_number_label->setText(QApplication::translate("MainWindow", "State #/#", 0));
        state_score_label->setText(QApplication::translate("MainWindow", "State Score", 0));
        prev_state_button->setText(QApplication::translate("MainWindow", "Previous State", 0));
        next_state_button->setText(QApplication::translate("MainWindow", "Next State", 0));
        toggle_evolution_button->setText(QApplication::translate("MainWindow", "Start Evolution", 0));
        next_generation_button->setText(QApplication::translate("MainWindow", "Next Generation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
