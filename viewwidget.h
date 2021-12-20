#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QObject>
#include <GL/glu.h>
#include <math.h>
#include "solarsystem.h"


class ViewWidget : public QGLWidget
{
    Q_OBJECT
public:
    ViewWidget(QWidget* parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    SolarSystem model;
    float speed;
    void planet(double r, int lats, int longs);

public slots:
    void updateSpeed(int newSpeed);
};

#endif // VIEWWIDGET_H
