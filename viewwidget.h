#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QObject>
#include <GL/glu.h>
#include <GL/glut.h>
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
    float lightPosition;
    int starSize;
    int cameraFocus;
    void sphere(double r, int lats, int longs);
    void artificalSatillite(float size);

public slots:
    void updateSpeed(int newSpeed);
    void updateSizes(const QString& objectName);
    void updateStarSize(int newSize);
};

#endif // VIEWWIDGET_H
