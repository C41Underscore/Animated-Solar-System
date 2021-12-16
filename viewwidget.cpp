#include "viewwidget.h"

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{

}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4., 4., -4., 4., -4., 4.);
    glMatrixMode(GL_MODELVIEW);
}

void ViewWidget::planet()
{
    glColor3f(1.0, 0.843, 0.0);
    glBegin(GL_POLYGON);
      glVertex3f(-1., 1., 1.);
      glVertex3f(-1., 1., -1.);
      glVertex3f(-1., -1., -1.);
      glVertex3f(-1., -1., 1.);
    glEnd();

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
      glVertex3f( 1.0, -1.0,  1.0);
      glVertex3f( 1.0, -1.0, -1.0);
      glVertex3f( 1.0,  1.0, -1.0);
      glVertex3f( 1.0,  1.0,  1.0);
      glEnd();

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
      glVertex3f(-1.0, -1.0, -1.0);
      glVertex3f( 1.0, -1.0, -1.0);
      glVertex3f( 1.0,  1.0, -1.0);
      glVertex3f(-1.0,  1.0, -1.0);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f( 1.0, -1.0, 1.0);
      glVertex3f( 1.0,  1.0, 1.0);
      glVertex3f(-1.0,  1.0, 1.0);
    glEnd();


    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
      glVertex3f(1., -1., -1.);
      glVertex3f(1., -1., 1.);
      glVertex3f(1., 1., 1.);
      glVertex3f(1., 1., -1.);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
      glVertex3f(-1., 1., 1.);
      glVertex3f(-1., 1., -1.);
      glVertex3f(1., 1., -1.);
      glVertex3f(1., 1., 1.);
     glEnd();
}

void ViewWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ViewWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->planet();

    glLoadIdentity();

    gluLookAt(0.,0.,0., 1.0,1.0,1.0, 0.0,0.0,1.0);

    glFlush();
}
