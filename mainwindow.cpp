#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    viewPort = new ViewWidget(this);

    speedControl = new QSlider(Qt::Horizontal);
    speedControl->setMaximum(100);
    speedControl->setMinimum(0);
    speedControl->setSingleStep(1);
    speedControl->setSliderPosition(1);
    connect(speedControl, SIGNAL(valueChanged(int)), viewPort, SLOT(updateSpeed(int)));

    layout->addWidget(viewPort);
    layout->addWidget(speedControl);

}

MainWindow::~MainWindow()
{
    delete viewPort;
    delete speedControl;
    delete layout;
}
