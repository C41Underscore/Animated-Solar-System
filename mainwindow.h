#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QSlider>
#include <QComboBox>
#include <QKeyEvent>
#include <QAbstractItemView>

#include "viewwidget.h"

class Filter: public QObject
{
    Q_OBJECT
public:
    bool eventFilter(QObject* object, QEvent* event)
    {
        if(event->type() == QEvent::KeyPress)
        {
            return true;
        }
        return false;
    }
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);

private:
    ViewWidget* viewPort;
    QSlider* speedControl;
    QSlider* zoomControl;
    QComboBox* focusControl;
    QBoxLayout* layout;
};
#endif // MAINWINDOW_H
