#include "viewwidget.h"

#include <QDebug>

#define MODEL_SIZE 20.

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
    this->model = SolarSystem("Sol", 696340.);
    this->model.addPlanet("Mercury", 88., 2439.7, 57910000.);
    this->model.addPlanet("Venus", 225., 6051.8, 108200000.);
    this->model.addPlanet("Earth", 365., 6371., 149600000.);
    this->model.addPlanet("Mars", 687., 3389.5, 227900000.);
    this->model.addPlanet("Jupiter", (float)12*365, 69911., 778000000.);
    this->model.addPlanet("Saturn", (float)29*365, 58232., 1434000000.);
    this->model.addPlanet("Uranus", (float)84*365, 25362., 2871000000.);
    this->model.addPlanet("Neptune", (float)165*365, 24622., 4495000000.);
    this->model.normalise(MODEL_SIZE);
    this->speed = 1.;
}

void ViewWidget::updateSpeed(int newSpeed)
{
    this->speed = (float)newSpeed/10.;
    update();
}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE);
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
}

void ViewWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(1.,1.,1., 0., 0.,0., 0.,1.,0.);

    GLfloat light_pos[] = {0., 10., 0., 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    this->model.tick(this->speed);
    std::vector<Planet> planets = this->model.getPlanets();

    this->planet(3., 20, 20);

    for(unsigned int i = 0; i < planets.size(); i++)
    {
//        qDebug() << planets.at(i).getPosition();
        glPushMatrix();
        glRotatef(planets.at(i).getPosition(), 0., 1., 0.);
        glTranslatef(planets.at(i).getDistanceFromSun() + 3., 0., 0.);
        this->planet(planets.at(i).getRadius(), 20, 20);
        glPopMatrix();
    }

    glFlush();
}
