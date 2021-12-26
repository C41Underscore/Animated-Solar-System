#include "viewwidget.h"

#include <QDebug>

static float MODEL_SIZE = 20.;

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


//static materialStruct brassMaterials = {
//  { 0.33, 0.22, 0.03, 1.0},
//  { 0.78, 0.57, 0.11, 1.0},);
//  { 0.99, 0.91, 0.81, 1.0},
//  27.8
//};

//static materialStruct sunMaterials = {
//  { 0.33, 0.22, 0.03, 1.0},
//  { 1.0, 0.87, 0., 1.0},
//  { 0.0, 0.0, 0.0, 0.0},
//  100.0
//};

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{
    this->model = SolarSystem("Sol", 696340.);
    this->model.addPlanet(Planet("Mercury", 88., 2439.7, 57910000.));
    this->model.addPlanet(Planet("Venus", 225., 6051.8, 108200000.));
    Planet earth("Earth", 365., 6371., 149600000.);
    this->model.addPlanet(earth);
    this->model.addPlanet(Planet("Mars", 687., 3389.5, 227900000.));
//    Planet jupiter("Jupiter", (float)12*365, 69911., 778000000.);
//    jupiter.addSatillite(Satillite(27., 1737.4, 384400., true));
//    this->model.addPlanet(jupiter);
//    this->model.addPlanet(Planet("Saturn", (float)29*365, 58232., 1434000000.));
//    this->model.addPlanet(Planet("Uranus", (float)84*365, 25362., 2871000000.));
//    this->model.addPlanet(Planet("Neptune", (float)165*365, 24622., 4495000000.));
    this->model.normalise(MODEL_SIZE);
    this->speed = 1.;
    this->lightPosition = 5.;
    this->starSize = 10.;
    this->cameraFocus = 0;
}

void ViewWidget::updateSpeed(int newSpeed)
{
    this->speed = (float)newSpeed/10.;
    update();
}

void ViewWidget::updateSizes(const QString& objectName)
{
//    this->model.normalise(MODEL_SIZE, objectName.toStdString());
    std::vector<Planet> planets = this->model.getPlanets();
    int objectPos = 0.;
    for (unsigned int i = 0; i < planets.size(); i++)
    {
        if(planets.at(i).getName().compare(objectName.toStdString()) == 0)
        {
            objectPos = i;
            break;
        }
    }
    this->cameraFocus = objectPos;
    qDebug() << this->cameraFocus;
    update();
}

void ViewWidget::updateStarSize(int newSize)
{
    this->starSize = newSize;
    update();
}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    float betterModelSize = MODEL_SIZE + 1.;
    glOrtho(-betterModelSize, betterModelSize, -betterModelSize, betterModelSize, -betterModelSize, betterModelSize);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void ViewWidget::sphere(double r, int lats, int longs)
{
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

void ViewWidget::artificalSatillite(float size)
{
    // create sphere
    glBegin(GL_POLYGON);
        GLUquadric* satilliteBody = gluNewQuadric();
        gluSphere(satilliteBody, 1.0, 20, 20);
        gluDeleteQuadric(satilliteBody);
    glEnd();
    // create first cylinders
    // first arm
    glPushMatrix();
    glBegin(GL_POLYGON);
        GLUquadric* satilliteDishArm1 = gluNewQuadric();
        gluCylinder(satilliteDishArm1, 0.1, 0.1, 0.5, 20, 20);
        gluDeleteQuadric(satilliteDishArm1);
    glEnd();
    glPopMatrix();
    // second arm
    glPushMatrix();
    glBegin(GL_POLYGON);
        GLUquadric* satilliteDishArm2 = gluNewQuadric();
        gluCylinder(satilliteDishArm2, 0.1, 0.1, 0.5, 20, 20);
        gluDeleteQuadric(satilliteDishArm2);
    glEnd();
    glPopMatrix();
    // create hemispheres
    // create second cylinders
    glPushMatrix();
    glBegin(GL_POLYGON);
        GLUquadric* satillitePanelArm1 = gluNewQuadric();
        gluCylinder(satillitePanelArm1, 0.1, 0.1, 0.5, 20, 20);
        gluDeleteQuadric(satillitePanelArm1);
    glEnd();
    glPopMatrix();
    // second arm
    glPushMatrix();
    glBegin(GL_POLYGON);
        GLUquadric* satillitePanelArm2 = gluNewQuadric();
        gluCylinder(satillitePanelArm2, 0.1, 0.1, 0.5, 20, 20);
        gluDeleteQuadric(satillitePanelArm2);
    glEnd();
    glPopMatrix();
    // create solar panels (rectangles)
    // first panel
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
    glEnd();
    glPopMatrix();
    // second panel
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., 0.);
    glEnd();
    glPopMatrix();
}

void ViewWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ViewWidget::paintGL()
{
//    glMatrixMode(GL_PROJECTION);
//    glOrtho(-MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    std::vector<Planet> planets = this->model.getPlanets();
    gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.);


    GLfloat light_pos[] = {0., 0., 0., 1.};
    this->lightPosition -= 0.01;
    //glOrtho(-this->lightPosition, this->lightPosition, -this->lightPosition, this->lightPosition, -this->lightPosition, this->lightPosition);
    if(this->lightPosition < 0.)
    {
        this->lightPosition = 5.;
    }
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

//    glScalef(this->lightPosition, this->lightPosition, this->lightPosition);

    this->model.tick(this->speed);
    GLfloat sun_ambient_and_diffuse[] = {1.0, 0.87, 0., 1.0};
    GLfloat sun_emission = 100.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun_ambient_and_diffuse);
    glMaterialf(GL_FRONT, GL_EMISSION,   sun_emission);

    glBegin(GL_POLYGON);
        GLUquadric* sunQuadric = gluNewQuadric();
        gluSphere(sunQuadric, this->starSize, 16, 16);
        gluDeleteQuadric(sunQuadric);
    glEnd();

    GLfloat planet_ambient_and_diffuse[] = {0.78, 0.57, 0.11, 1.0};
    GLfloat planet_emission = 0.0;

    for(unsigned int i = 0; i < planets.size(); i++)
    {
        glPushMatrix();
        glRotatef(planets.at(i).getPosition(), 0., 1., 0.);
        glTranslatef(planets.at(i).getDistanceFromSun() + this->starSize, 0., 0.);
        glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient_and_diffuse);
        glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
        glBegin(GL_POLYGON);
            GLUquadric* planetQuadric = gluNewQuadric();
            gluSphere(planetQuadric, planets.at(i).getRadius(), 16, 16);
            gluDeleteQuadric(planetQuadric);
        glEnd();
        glPopMatrix();
//        std::vector<Satillite> satillites = planets.at(i).getSatillites();
//        for(unsigned int j = 0; j < satillites.size(); j++)
//        {
//            glPushMatrix();
//            glRotatef(planets.at(i).getPosition(), 0., 1., 0.);
//            glTranslatef(planets.at(i).getDistanceFromSun() + this->starSize, 0., 0.);
//            glRotatef(satillites.at(j).getPosition(), 0., 1., 0.);
//            glTranslatef(0.1, 0., 0.);
//            this->sphere(0.05, 20, 20);
//            glPopMatrix();
//        }
    }
//    qDebug() << -planets.at(this->cameraFocus).getDistanceFromSun() << -planets.at(this->cameraFocus).getPosition();
//    glTranslatef(planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize, 0. ,0.);
//    glRotatef(-planets.at(this->cameraFocus).getPosition(), 0., 1., 0.);
//    glTranslatef(-planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize, 0., 0.);

    glFlush();
}
