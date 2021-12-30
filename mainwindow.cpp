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
    speedControl->setSliderPosition(1);
    connect(speedControl, SIGNAL(valueChanged(int)), viewPort, SLOT(updateSpeed(int)));

    zoomControl = new QSlider(Qt::Horizontal);
//    zoomControl->setMaximum(25);
//    zoomControl->setMinimum(1);
//    zoomControl->setSingleStep(1);
//    zoomControl->setSliderPosition(1);
//    connect(zoomControl, SIGNAL(valueChanged(int)), viewPort, SLOT(updateZoom(int)));

    focusControl = new QComboBox();
    focusControl->addItems({"The Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"});
    focusControl->setCurrentIndex(0);
    focusControl->view()->installEventFilter(new Filter());
    connect(focusControl, SIGNAL(currentTextChanged(const QString&)), viewPort, SLOT(updateView(const QString&)));


    layout->addWidget(viewPort);
    layout->addWidget(speedControl);
    layout->addWidget(zoomControl);
    layout->addWidget(focusControl);
}

MainWindow::~MainWindow()
{
    delete viewPort;
    delete speedControl;
    delete layout;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        this->viewPort->moveCamera(true, false, false, false);
    }
    if(event->key() == Qt::Key_S)
    {
        this->viewPort->moveCamera(false, true, false, false);
    }
    if(event->key() == Qt::Key_A)
    {
        this->viewPort->moveCamera(false, false, true, false);
    }
    if(event->key() == Qt::Key_D)
    {
        this->viewPort->moveCamera(false, false, false, true);
    }
    if(event->key() == Qt::Key_Up)
    {
        this->viewPort->updateZoom(true);
    }
    if(event->key() == Qt::Key_Down)
    {
        this->viewPort->updateZoom(false);
    }
    if(event->key() == Qt::Key_Left)
    {
        this->viewPort->rotateCamera(false);
    }
    if(event->key() == Qt::Key_Right)
    {
        this->viewPort->rotateCamera(true);
    }
}
