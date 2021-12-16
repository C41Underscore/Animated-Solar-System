#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ViewWidget* viewPort = new ViewWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(viewPort);
}

MainWindow::~MainWindow()
{
    delete viewPort;
    delete layout;
}
