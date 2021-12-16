#include "viewwidget.h"

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{

}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4., 4., -4., 4., -4., 4.);
    glMatrixMode(GL_MODELVIEW);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void ViewWidget::planet(double r, int lats, int longs)
{
    materialStruct* p_front = &brassMaterials;

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
//    glColor3f(1., 1., 0.);
    int i, j;
        for(i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            double z0  = sin(lat0);
            double zr0 =  cos(lat0);

            double lat1 = M_PI * (-0.5 + (double) i / lats);
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            glBegin(GL_QUAD_STRIP);
            for(j = 0; j <= longs; j++) {
                double lng = 2 * M_PI * (double) (j - 1) / longs;
                double x = cos(lng);
                double y = sin(lng);

                glNormal3f(x * zr0, y * zr0, z0);
                glVertex3f(r * x * zr0, r * y * zr0, r * z0);
                glNormal3f(x * zr1, y * zr1, z1);
                glVertex3f(r * x * zr1, r * y * zr1, r * z1);
            }
            glEnd();
        }
}

void ViewWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    GLfloat light_pos[] = {0., 0., 10., 1.};
//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
}

void ViewWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    GLfloat light_pos[] = {15., 0., 0., 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);

    glPopMatrix();

//    glTranslatef(0.5, 0., 0.);

    this->planet(1., 20, 20);

    glPushMatrix();

    glTranslatef(4., 0., 0.);

    this->planet(0.3, 20, 20);

    glPopMatrix();

    glRotatef(1., 0., 1., 0.);

    glPushMatrix();

    gluLookAt(0.,0.,0., 0.0, 0.0,0.0, 1.0,0.0,0.0);

    glFlush();
}
