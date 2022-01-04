#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QComboBox>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "viewwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);

private:
    ViewWidget* viewPort;
    QLabel* speedLabel;
    QSlider* speedControl;
    QHBoxLayout* speedLayout;
    QPushButton* resetButton;
    QCheckBox* marcControl;
    QLabel* focusLabel;
    QComboBox* focusControl;
    QHBoxLayout* focusLayout;
    QBoxLayout* layout;
};
#endif // MAINWINDOW_H
