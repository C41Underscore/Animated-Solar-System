#include "viewwidget.h"

#include <QDebug>

static float MODEL_SIZE = 20.;

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{
    this->model = SolarSystem("Sol", 696340.);
    this->model.addPlanet(Planet("Mercury", 88., 2439.7, 57910000.));
    this->model.addPlanet(Planet("Venus", 225., 6051.8, 108200000.));
    Planet earth("Earth", 365., 6371., 149600000.);
    earth.addSatillite(Satillite(27., 1737.4, 384400., true)); // The Moon
    earth.addSatillite(Satillite(50., 500., 599999999., false)); // The Hubble, let's say
    this->model.addPlanet(earth);
    Planet mars("Mars", 687., 3389.5, 227900000.);
    mars.addSatillite(Satillite(8./24., 11.267, 9376., true)); // Phobos
    mars.addSatillite(Satillite(1.263, 6.2, 23458., true)); // Diemos
    this->model.addPlanet(mars);
    Planet jupiter("Jupiter", (float)12*365, 69911., 778000000.);
    jupiter.addSatillite(Satillite(85./24., 1560.8, 671100.,  true)); // Europa
    jupiter.addSatillite(Satillite(172./24., 2631.2, 1070400., true)); // Ganymede
    jupiter.addSatillite(Satillite(42./24., 1821.6, 421800., true)); // Io
    jupiter.addSatillite(Satillite(17., 2410.3, 1882700., true)); // Callisto
    this->model.addPlanet(jupiter);
    Planet saturn("Saturn", (float)29*365, 58232., 1434000000.);
    saturn.addSatillite(Satillite(16., 2574.7, 149598262., true)); // Titan
    this->model.addPlanet(saturn);
    Planet uranus("Uranus", (float)84*365, 25362., 2871000000.);
    uranus.addSatillite(Satillite(209./24., 788.4, 436300., true)); // Titania
    this->model.addPlanet(uranus);
    Planet neptune("Neptune", (float)165*365, 24622., 4495000000.);
    neptune.addSatillite(Satillite(141./24., 1353.4, 345759., true)); // Triton
    neptune.addSatillite(Satillite(50., 500., 599999999., false));
    this->model.addPlanet(neptune);
    this->model.normalise(MODEL_SIZE);
    this->speed = 0.0005;
    this->lightPosition = 5.;
    this->zoom = 1.;
    this->cameraFocus = -1.;
    this->newFocus = false;
    this->movementUp = 0.;
    this->movementRight = 0.;
    this->rotation = 0.;
}

void ViewWidget::moveCamera(bool up, bool down, bool left, bool right)
{
    float movement = 0.2;
    if(up)
    {
        this->movementUp += movement;
    }
    else if(down)
    {
        this->movementUp -= movement;
    }
    else if(left)
    {
        this->movementRight -= movement;
    }
    else if(right)
    {
        this->movementRight += movement;
    }
}

void ViewWidget::rotateCamera(bool trueForRight)
{
    float rotate = 0.2;
    if(trueForRight)
    {
        this->rotation += rotate;
    }
    else
    {
        this->rotation -= rotate;
    }
}

void ViewWidget::updateSpeed(int newSpeed)
{
    this->speed = (float)newSpeed/1000.;
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
    this->newFocus = true;
    update();
}

void ViewWidget::updateZoom(bool trueForUp)
{
    float zoom = 0.01;
    if(trueForUp)
    {
        this->zoom += zoom;
    }
    else
    {
        this->zoom -= zoom;
    }
    qDebug() << this->zoom;
    update();
}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    float betterModelSize = MODEL_SIZE + MODEL_SIZE/4.;
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
        glVertex3f(size*1.5, 0., 0.);
        glVertex3f(size*1.5, 0., size);
        glVertex3f(0., 0., size);
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
    glRotatef(90., 1., 0., 0.);
    glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, 0.);
    glPushMatrix();
    GLfloat satillite_arm_ambient_and_diffuse[] = {132./255., 135./255., 137./255., 0.5};
    GLfloat satillite_arm_specular[] = {132./255., 135./255., 137./255., 0.5};
    GLfloat satillite_arm_shininess = 85.;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, satillite_arm_ambient_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, satillite_arm_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, satillite_arm_shininess);
    glBegin(GL_POLYGON);
        GLUquadric* satilliteBody = gluNewQuadric();
        gluSphere(satilliteBody, size, 20, 20);
        gluDeleteQuadric(satilliteBody);
    glEnd();
    glPopMatrix();
    // create first cylinders
    // first arm
    glPushMatrix();
    glTranslatef(0.0, size*2, 0.0);
    glRotatef(90., 1., 0., 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // second arm
    glPushMatrix();
    glTranslatef(0.0, -size, 0.0);
    glRotatef(90., 1., 0., 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // create dishes
    // create first dish
    GLfloat satillite_dish_ambient_and_diffuse[] = {67./255., 70./255., 75./255., 0.75};
    GLfloat satillite_dish_specular[] = {67./255., 70./255., 75./255., 0.25};
    GLfloat satillite_dish_shininess = 60.;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, satillite_dish_ambient_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, satillite_dish_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, satillite_dish_shininess);
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, satillite_arm_ambient_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, satillite_arm_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, satillite_arm_shininess);
    glPushMatrix();
    glTranslatef(-size*2, 0.0, 0.0);
    glRotatef(90., 0., 1.0, 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // second arm
    glPushMatrix();
    glTranslatef(size, 0.0, 0.0);
    glRotatef(90., 0., 1.0, 0.);
    this->satilliteArm(size);
    glPopMatrix();
    // create solar panels (rectangles)
    GLfloat satillite_panel_ambient_and_diffuse[] = {0., 0., 1., 1.};
    GLfloat satillite_panel_specular[] = {0., 0., 1., 1.};
    GLfloat satillite_panel_shininess = 100.;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, satillite_panel_ambient_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, satillite_panel_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, satillite_panel_shininess);
    GLfloat panel_normals[] = {1., 0., 0.};
    // first panel
    glNormal3f(panel_normals[0], panel_normals[1], panel_normals[2]);
    glPushMatrix();
    glTranslatef(size*2, 0., -size/2.);
    this->satillitePanel(size);
    glPopMatrix();
    // second panel
    glPushMatrix();
    glTranslatef(-size*3.5, 0., -size/2.);
    this->satillitePanel(size);
    glPopMatrix();
//    glPopMatrix();
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
    float starSize = 10.;
    gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.);

    if(this->cameraFocus > -1)
    {
        Planet focusPlanet = planets.at(this->cameraFocus);
        float planetX = (planets.at(this->cameraFocus).getDistanceFromSun() + starSize)*sin(planets.at(this->cameraFocus).getPosition());
        float planetZ = (planets.at(this->cameraFocus).getDistanceFromSun() + starSize)*cos(planets.at(this->cameraFocus).getPosition());
        glTranslatef(-planetX, 0., -planetZ);
        this->newFocus = false;
        this->movementUp = 0.;
        this->movementRight = 0.;
    }
    glTranslatef(this->movementUp, 0., this->movementRight);
    glScalef(this->zoom, this->zoom, this->zoom);
    glRotatef(this->rotation, 0., 1., 0.);
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
        gluSphere(sunQuadric, starSize, 16, 16);
        gluDeleteQuadric(sunQuadric);
    glEnd();
//    this->artificalSatillite(5.);

    GLfloat planet_ambient_and_diffuse[] = {0.78, 0.57, 0.11, 1.0};
    GLfloat planet_emission = 0.0;
    GLfloat planet_shininess = 0.;

//    glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient_and_diffuse);
//    glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);

    for(unsigned int i = 0; i < planets.size(); i++)
    {
        glPushMatrix();
        float planetX = (planets.at(i).getDistanceFromSun() + starSize)*sin(planets.at(i).getPosition());
        float planetZ = (planets.at(i).getDistanceFromSun() + starSize)*cos(planets.at(i).getPosition());
        glTranslatef(planetX, 0., planetZ);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planet_ambient_and_diffuse);
        glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, planet_shininess);
        glBegin(GL_POLYGON);
            GLUquadric* planetQuadric = gluNewQuadric();
            gluSphere(planetQuadric, planets.at(i).getRadius(), 16, 16);
            gluDeleteQuadric(planetQuadric);
        glEnd();
        glPopMatrix();
        std::vector<Satillite>* satillites = planets.at(i).getSatillites();
        for(unsigned int j = 0; j < satillites->size(); j++)
        {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planet_ambient_and_diffuse);
            glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
            glMaterialf(GL_FRONT, GL_SHININESS, planet_shininess);
            glPushMatrix();
            Satillite currentSatillite = satillites->at(j);
            float satilliteX = 0., satilliteY = 0., satilliteZ = 0.;
            satilliteX = (currentSatillite.getDistanceFromPlanet() + currentSatillite.getRadius()*2)*cos(currentSatillite.getPosition());
            satilliteZ = (currentSatillite.getDistanceFromPlanet() + currentSatillite.getRadius()*2)*sin(currentSatillite.getPosition());
            glTranslatef(satilliteX, 0., satilliteZ);
            glTranslatef(planetX, 0., planetZ);

            // rotate
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

                // rotate around the planet
//                glPushMatrix();
////                glTranslatef(satilliteX, 0., satilliteZ);
////                glRotatef(90., 1., 0., 0.);
////                glTranslatef(planetX, 0., planetZ);
//                glTranslatef(planetX, 0., planetZ);
//////                glTranslatef(-satilliteX, 0., -satilliteZ);
//                glRotatef(30., 1., 0., 0.);
//                glTranslatef(-planetX, 0., -planetZ);
//                glTranslatef(satilliteX, 0., satilliteZ);
//                glRotatef(30., 0., 0., 1.);
//
                this->artificalSatillite(satillites->at(j).getRadius());
//                this->artificalSatillite(0.7);
//                glPopMatrix();
//                glRotatef(45., 1., 0., 1.);
                GLfloat reset_specular[] = {0., 0., 0., 0.};
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reset_specular);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glFlush();
}
