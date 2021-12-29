#include "viewwidget.h"

#include <QDebug>

static float MODEL_SIZE = 20.;

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{
    this->model = SolarSystem("Sol", 696340.);
    this->model.addPlanet(Planet("Mercury", 88., 2439.7, 57910000.));
    this->model.addPlanet(Planet("Venus", 225., 6051.8, 108200000.));
    Planet earth("Earth", 365., 6371., 149600000.);
    earth.addSatillite(Satillite(27., 1737.4, 384400., true));
    this->model.addPlanet(earth);
    this->model.addPlanet(Planet("Mars", 687., 3389.5, 227900000.));
    Planet jupiter("Jupiter", (float)12*365, 69911., 778000000.);
    jupiter.addSatillite(Satillite(85./24., 1560.8, 671100.,  true));
    jupiter.addSatillite(Satillite(172./24., 2631.2, 1070400., true));
    jupiter.addSatillite(Satillite(42./24., 1821.6, 421800., true));
    this->model.addPlanet(jupiter);
    this->model.addPlanet(Planet("Saturn", (float)29*365, 58232., 1434000000.));
    this->model.addPlanet(Planet("Uranus", (float)84*365, 25362., 2871000000.));
    this->model.addPlanet(Planet("Neptune", (float)165*365, 24622., 4495000000.));
    this->model.normalise(MODEL_SIZE);
    this->speed = 0.005;
    this->lightPosition = 5.;
    this->starSize = 3.;
    this->cameraFocus = -1.;
}

void ViewWidget::updateSpeed(int newSpeed)
{
    this->speed = (float)newSpeed/100.;
    update();
}

void ViewWidget::updateView(const QString& objectName)
{
    std::vector<Planet> planets = this->model.getPlanets();
    unsigned int planetIndex = -1;
    if(objectName.compare("The Sun") != 0)
    {
        for(unsigned int i = 0; i < planets.size(); i++)
        {
            if(objectName.compare(planets.at(i).getName().c_str()) == 0)
            {
                planetIndex = i;
                break;
            }
        }
    }
    this->cameraFocus = planetIndex;
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
    glEnable(GL_NORMALIZE);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void ViewWidget::satillitePanel(float size)
{
    glBegin(GL_POLYGON);
        glVertex3f(0., 0., 0.);
        glVertex3f(size*3, 0., 0.);
        glVertex3f(size*3, 0., size*2);
        glVertex3f(0., 0., size*2);
    glEnd();
}

void ViewWidget::satilliteDish(double r, int lats, int longs)
{
    int i, j;
    int cutOff = longs/2;
    for(i = 0; i <= lats; i++)
    {
        if(i > cutOff)
        {
            return;
        }
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
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

void ViewWidget::satilliteArm(float size)
{
    glBegin(GL_POLYGON);
        GLUquadric* satilliteDishArm1 = gluNewQuadric();
        gluCylinder(satilliteDishArm1, size/3, size/3, size, 50, 50);
        gluDeleteQuadric(satilliteDishArm1);
    glEnd();
}

void ViewWidget::artificalSatillite(float size)
{
    // create sphere
    glPushMatrix();
    GLfloat satillite_body_ambient_and_diffuse[] = {};
    GLfloat satillite_body_specular[] = {};
    GLfloat satillite_body_shininess[] = {};
    glBegin(GL_POLYGON);
        GLUquadric* satilliteBody = gluNewQuadric();
        gluSphere(satilliteBody, size, 20, 20);
        gluDeleteQuadric(satilliteBody);
    glEnd();
    glPopMatrix();
    // create first cylinders
    GLfloat satillite_dish_arm_ambient_and_diffuse[] = {};
    GLfloat satillite_dish_arm_specular[] = {};
    GLfloat satillite_dish_arm_shininess[] = {};
    // first arm
    glPushMatrix();
    glTranslatef(0.0, size*2-0.5, 0.0);
    glRotatef(90., 1., 0., 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // second arm
    glPushMatrix();
    glTranslatef(0.0, -size+0.5, 0.0);
    glRotatef(90., 1., 0., 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // create dishes
    // create first dish
    GLfloat satillite_dish_ambient_and_diffuse[] = {};
    GLfloat satillite_dish_specular[] = {};
    GLfloat satillite_dish_shininess[] = {};
    glPushMatrix();
    glTranslatef(0., size*2, 0.);
    glRotatef(270., 1., 0., 0.);
    glTranslatef(0., 0., (2./5.)*size);
    this->satilliteDish(size/1.5, 20, 20);
    glPopMatrix();
    // create second dish
    glPushMatrix();
    glTranslatef(0., -size*2, 0.);
    glRotatef(90., 1., 0., 0.);
    glTranslatef(0., 0., (2./5.)*size);
    this->satilliteDish(size/1.5, 20, 20);
    glPopMatrix();
    // create second cylinders
    GLfloat satillite_panel_arm_ambient_and_diffuse[] = {};
    GLfloat satillite_panel_arm_specular[] = {};
    GLfloat satillite_panel_arm_shininess[] = {};
    glPushMatrix();
    glTranslatef(-size*2+0.5, 0.0, 0.0);
    glRotatef(90., 0., 1.0, 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // second arm
    glPushMatrix();
    glTranslatef(size-0.5, 0.0, 0.0);
    glRotatef(90., 0., 1.0, 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // create solar panels (rectangles)
    GLfloat satillite_panel_ambient_and_diffuse[] = {};
    GLfloat satillite_panel_specular[] = {};
    GLfloat satillite_panel_shininess[] = {};
    GLfloat panel_normals[] = {0., 1., 0.};
    // first panel
    glNormal3f(panel_normals[0], panel_normals[1], panel_normals[2]);
    glPushMatrix();
    glTranslatef(size*2-0.5, 0., -size);
    this->satillitePanel(size);
    glPopMatrix();
    // second panel
    glPushMatrix();
    glTranslatef(-size*5+0.5, 0., -size);
    this->satillitePanel(size);
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

    if(this->cameraFocus > -1)
    {
        Planet focusPlanet = planets.at(this->cameraFocus);
        float planetX = (planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize)*sin(planets.at(this->cameraFocus).getPosition());
        float planetZ = (planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize)*cos(planets.at(this->cameraFocus).getPosition());
        glScalef(2./focusPlanet.getRadius(), 2./focusPlanet.getRadius(), 2./focusPlanet.getRadius());
        glTranslatef(-planetX, 0., -planetZ);
    }

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
    glMaterialf(GL_FRONT, GL_EMISSION, sun_emission);

    glBegin(GL_POLYGON);
        GLUquadric* sunQuadric = gluNewQuadric();
        gluSphere(sunQuadric, this->starSize, 16, 16);
        gluDeleteQuadric(sunQuadric);
    glEnd();

    GLfloat planet_ambient_and_diffuse[] = {0.78, 0.57, 0.11, 1.0};
    GLfloat planet_emission = 0.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient_and_diffuse);
    glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);

//    this->artificalSatillite(1.);

    for(unsigned int i = 0; i < planets.size(); i++)
    {
        glPushMatrix();
        float planetX = (planets.at(i).getDistanceFromSun() + this->starSize)*sin(planets.at(i).getPosition());
        float planetZ = (planets.at(i).getDistanceFromSun() + this->starSize)*cos(planets.at(i).getPosition());
        glTranslatef(planetX, 0., planetZ);
        glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient_and_diffuse);
        glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
        glBegin(GL_POLYGON);
            GLUquadric* planetQuadric = gluNewQuadric();
            gluSphere(planetQuadric, planets.at(i).getRadius(), 16, 16);
            gluDeleteQuadric(planetQuadric);
        glEnd();
        glPopMatrix();
        std::vector<Satillite>* satillites = planets.at(i).getSatillites();
        for(unsigned int j = 0; j < satillites->size(); j++)
        {
            glPushMatrix();
            float satilliteX = (satillites->at(j).getDistanceFromPlanet() + satillites->at(j).getRadius()*2)*sin(satillites->at(j).getPosition());
            float satilliteZ = (satillites->at(j).getDistanceFromPlanet() + satillites->at(j).getRadius()*2)*cos(satillites->at(j).getPosition());
            glTranslatef(planetX, 0., planetZ);
            glTranslatef(satilliteX, 0., satilliteZ);
            if(satillites->at(j).isMoon())
            {
                glBegin(GL_POLYGON);
                    GLUquadric* moonQuadric = gluNewQuadric();
                    gluSphere(moonQuadric, satillites->at(j).getRadius(), 20, 20);
                    gluDeleteQuadric(moonQuadric);
                glEnd();
            }
            else
            {
                this->artificalSatillite(satillites->at(j).getRadius());
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
//    qDebug() << -planets.at(this->cameraFocus).getDistanceFromSun() << -planets.at(this->cameraFocus).getPosition();
//    glTranslatef(planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize, 0. ,0.);
//    glRotatef(-planets.at(this->cameraFocus).getPosition(), 0., 1., 0.);
//    glTranslatef(-planets.at(this->cameraFocus).getDistanceFromSun() + this->starSize, 0., 0.);
//    glRotatef(this->starSize, 0.0, 1.0, 0.0);
    glFlush();
}
