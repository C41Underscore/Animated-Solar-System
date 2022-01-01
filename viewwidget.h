#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include <QTimer>
#include <QObject>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "solarsystem.h"
#include <stb_image.h>



class ViewWidget : public QGLWidget
{
    Q_OBJECT
public:
    ViewWidget(QWidget* parent);
    void moveCamera(bool up, bool down, bool left, bool right);
    void updateZoom(bool trueForUp);
    void rotateCamera(bool trueForRight);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    SolarSystem model;
    float speed;
    float lightPosition;
    float zoom;
    int cameraFocus;
    bool newFocus;
    float movementX;
    float movementZ;
    float rotation;
    void artificalSatillite(float size);
    void satilliteArm(float size);
    void satilliteDish(double r, int lats, int longs);
    void satillitePanel(float size);

public slots:
    void updateSpeed(int newSpeed);
    void updateView(const QString& objectName);

};

#endif // VIEWWIDGET_H
