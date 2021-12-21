#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QSlider>
#include <QComboBox>

#include "viewwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ViewWidget* viewPort;
    QSlider* speedControl;
    QComboBox* sizeControl;
    QBoxLayout* layout;
};
#endif // MAINWINDOW_H
