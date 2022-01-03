#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    viewPort = new ViewWidget(this);
    viewPort->setFocusPolicy(Qt::StrongFocus);

    speedControl = new QSlider(Qt::Horizontal);
    speedControl->setMaximum(100);
    speedControl->setMinimum(0);
    speedControl->setSingleStep(1);
    speedControl->setSliderPosition(5);
    connect(speedControl, SIGNAL(valueChanged(int)), viewPort, SLOT(updateSpeed(int)));

    focusControl = new QComboBox();
    focusControl->addItems({"The Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"});
    focusControl->setCurrentIndex(0);
    focusControl->view()->installEventFilter(new Filter());
    connect(focusControl, SIGNAL(currentTextChanged(QString)), viewPort, SLOT(updateView(QString)));

    resetButton = new QPushButton("Reset Position", this);
    connect(resetButton, SIGNAL(clicked()), viewPort, SLOT(resetPosition()));

    marcControl = new QCheckBox("Marc?", this);
    connect(marcControl, SIGNAL(stateChanged(int)), viewPort, SLOT(bigMarcTime(int)));

    layout->addWidget(viewPort);
    layout->addWidget(speedControl);
    layout->addWidget(marcControl);
    layout->addWidget(focusControl);
}

MainWindow::~MainWindow()
{
    delete viewPort;
    delete speedControl;
    delete marcControl;
    delete layout;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        this->viewPort->moveCamera(true, false, false, false, false, false);
    }
    if(event->key() == Qt::Key_E)
    {
        this->viewPort->moveCamera(false, true, false, false, false, false);
    }
    if(event->key() == Qt::Key_W)
    {
        this->viewPort->moveCamera(false, false, true, false, false, false);
    }
    if(event->key() == Qt::Key_S)
    {
        this->viewPort->moveCamera(false, false, false, true, false, false);
    }
    if(event->key() == Qt::Key_A)
    {
        this->viewPort->moveCamera(false, false, false, false, true, false);
    }
    if(event->key() == Qt::Key_D)
    {
        this->viewPort->moveCamera(false, false, false, false, false, true);
    }
    if(event->key() == Qt::Key_Z)
    {
        this->viewPort->updateZoom(true);
    }
    if(event->key() == Qt::Key_X)
    {
        this->viewPort->updateZoom(false);
    }
    if(event->key() == Qt::Key_Up)
    {
        this->viewPort->rotateCamera(true, false, false, false);
    }
    if(event->key() == Qt::Key_Down)
    {
        this->viewPort->rotateCamera(false, true, false, false);
    }
    if(event->key() == Qt::Key_Left)
    {
        this->viewPort->rotateCamera(false, false, true, false);
    }
    if(event->key() == Qt::Key_Right)
    {
        this->viewPort->rotateCamera(false, false, false, true);
    }
}
