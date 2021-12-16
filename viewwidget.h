#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>


class ViewWidget : public QGLWidget
{
public:
    ViewWidget(QWidget* parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void planet();
};

#endif // VIEWWIDGET_H
