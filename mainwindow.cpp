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

    sizeControl = new QComboBox();
    sizeControl->addItems({"Standard", "The Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"});
    sizeControl->setCurrentIndex(0);
    connect(sizeControl, SIGNAL(currentTextChanged(const QString&)), viewPort, SLOT(updateSizes(const QString&)));


    layout->addWidget(viewPort);
    layout->addWidget(speedControl);
    layout->addWidget(sizeControl);
}

MainWindow::~MainWindow()
{
    delete viewPort;
    delete speedControl;
    delete layout;
}
