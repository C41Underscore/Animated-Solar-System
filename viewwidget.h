#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <GL/glu.h>
#include <math.h>
#include "solarsystem.h"


class ViewWidget : public QGLWidget
{
public:
    ViewWidget(QWidget* parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    SolarSystem model;
    void planet(double r, int lats, int longs);
};

#endif // VIEWWIDGET_H
