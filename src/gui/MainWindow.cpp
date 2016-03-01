#include "MainWindow.h"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_gfx_scene = std::make_unique<QGraphicsScene>();
}

MainWindow::~MainWindow()
{
    delete ui;
}
