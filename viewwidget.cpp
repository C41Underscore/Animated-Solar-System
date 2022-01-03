#include "viewwidget.h"

static float MODEL_SIZE = 20.;

#define MARC_DEKAMPS_TEX (GLuint)14
#define SUN_TEX (GLuint)0
#define MERCURY_TEX (GLuint)1
#define VENUS_TEX (GLuint)2
#define EARTH_TEX (GLuint)3
#define MARS_TEX (GLuint)4
#define JUPITER_TEX (GLuint)5
#define SATURN_TEX (GLuint)6
#define URANUS_TEX (GLuint)7
#define NEPTUNE_TEX (GLuint)8
#define THE_MOON_TEX (GLuint)9

std::vector<QPair<std::string, GLuint>> textures = std::vector<QPair<std::string, GLuint>>();
GLuint texUnits[16];

GLfloat nothing_ambient_and_diffuse[] = {0., 0., 0., 0.};
GLfloat nothing_specular[] = {0., 0., 0., 0.};
GLfloat nothing_shininess = 0.;
GLfloat nothing_emissive = 0.;

GLfloat silver_body_ambient_and_diffuse[] = {192./255., 192./255., 192./255., 1.0};
GLfloat silver_body_specular[] = {192./255., 192./255., 192./255., 0.00};
GLfloat silver_body_shininess = 0.1;
GLfloat silver_body_emissive = 0.;

GLfloat yellow_body_ambient_and_diffuse[] = {151./255., 151./255., 0., 1.0};
GLfloat yellow_body_specular[] = {0., 0., 0., 0.};
GLfloat yellow_body_shininess = 0.;
GLfloat yellow_body_emissive = 0.;

GLfloat pale_body_ambient_and_diffuse[] = {255./255., 229./255., 204./255., 1.0};
GLfloat pale_body_specular[] = {0., 0., 0., 0.};
GLfloat pale_body_shininess = 0.5;
GLfloat pale_body_emissive = 0.;

ViewWidget::ViewWidget(QWidget* parent) : QGLWidget(parent)
{
    this->model = SolarSystem("Sol", 696340., 27.);
    Planet mercury("Mercury", 88., 2439.7, 57910000., (58. + 15./24. + 0.5/24.), false);
    mercury.setTextureUnitIndex(MERCURY_TEX);
    this->model.addPlanet(mercury);
    Planet venus("Venus", 225., 6051.8, 108200000., (243.0226), false);
    venus.setTextureUnitIndex(VENUS_TEX);
    this->model.addPlanet(venus);
    Planet earth("Earth", 365., 6371., 149600000., 1., false);
    earth.setTextureUnitIndex(EARTH_TEX);
    Satillite* theMoon = new Satillite(27., 1737.4, 384400., true);
    theMoon->setTextureUnitIndex(THE_MOON_TEX);
    earth.addSatillite(theMoon); // The Moon
    earth.addSatillite(new Satillite(50., 500., 599999999., false)); // The Hubble, let's say
    this->model.addPlanet(earth);
    Planet mars("Mars", 687., 3389.5, 227900000., 1. + 1./24., false);
    mars.setTextureUnitIndex(MARS_TEX);
    mars.addSatillite(new Satillite(8./24., 11.267, 9376., true)); // Phobos
    mars.addSatillite(new Satillite(1.263, 6.2, 23458., true)); // Diemos
    mars.addSatillite(new Satillite(60., 400., 599999999., false));
    this->model.addPlanet(mars);
    Planet jupiter("Jupiter", (float)12*365, 69911., 778000000., (9./24. + (56./60.)/24.), false);
    jupiter.setTextureUnitIndex(JUPITER_TEX);
    Satillite* europa = new Satillite(85./24., 1560.8, 671100.,  true);
    europa->setLighting(pale_body_ambient_and_diffuse,
                        pale_body_ambient_and_diffuse,
                        pale_body_specular,
                        pale_body_shininess,
                        pale_body_emissive);
    jupiter.addSatillite(europa); // Europa
    Satillite* ganymede = new Satillite(172./24., 2631.2, 1070400., true);
    ganymede->setLighting(silver_body_ambient_and_diffuse,
                          silver_body_ambient_and_diffuse,
                          silver_body_specular,
                          silver_body_shininess,
                          silver_body_emissive);
    jupiter.addSatillite(ganymede); // Ganymede
    Satillite* io = new Satillite(42./24., 1821.6, 421800., true);
    io->setLighting(yellow_body_ambient_and_diffuse,
                    yellow_body_ambient_and_diffuse,
                    yellow_body_specular,
                    yellow_body_shininess,
                    yellow_body_emissive);
    jupiter.addSatillite(io); // Io
    Satillite* callisto = new Satillite(17., 2410.3, 1882700., true);
    callisto->setLighting(pale_body_ambient_and_diffuse,
                          pale_body_ambient_and_diffuse,
                          pale_body_specular,
                          pale_body_shininess,
                          pale_body_emissive);
    jupiter.addSatillite(callisto); // Callisto
    this->model.addPlanet(jupiter);
    Planet saturn("Saturn", (float)29*365, 58232., 1434000000., (10./24. + (42./60.)/24.), true);
    saturn.setRingSize(66900., 122170.);
    saturn.setTextureUnitIndex(SATURN_TEX);
    Satillite* titan = new Satillite(16., 2574.7, 149598262., true); // Titan
    titan->setLighting(yellow_body_ambient_and_diffuse,
                       yellow_body_ambient_and_diffuse,
                       yellow_body_specular,
                       yellow_body_shininess,
                       yellow_body_emissive);
    saturn.addSatillite(titan);
    this->model.addPlanet(saturn);
    Planet uranus("Uranus", (float)84*365, 25362., 2871000000., (17. + (14./60.)/24.), false);
    uranus.setTextureUnitIndex(URANUS_TEX);
    Satillite* titania = new Satillite(209./24., 788.4, 436300., true);
    titania->setLighting(silver_body_ambient_and_diffuse,
                         silver_body_ambient_and_diffuse,
                         silver_body_specular,
                         silver_body_shininess,
                         silver_body_emissive);
    uranus.addSatillite(titania); // Titania
    this->model.addPlanet(uranus);
    Planet neptune("Neptune", (float)165*365, 24622., 4495000000., (16./24. + (6./60.)/24.), false);
    neptune.setTextureUnitIndex(NEPTUNE_TEX);
    Satillite* triton = new Satillite(141./24., 1353.4, 345759., true);
    triton->setLighting(pale_body_ambient_and_diffuse,
                        pale_body_ambient_and_diffuse,
                        pale_body_specular,
                        pale_body_shininess,
                        pale_body_emissive);
    neptune.addSatillite(triton); // Triton
    neptune.addSatillite(new Satillite(50., 550., 599999999., false));
    this->model.addPlanet(neptune);
    this->model.normalise(MODEL_SIZE*2);
    this->speed = 0.0005;
    this->lightPosition = 5.;
    this->zoom = 1.;
    this->cameraFocus = -1.;
    this->newFocus = false;
    this->movementX = 0.;
    this->movementY = 0.;
    this->movementZ = 0.;
    this->rotationY = 0.;
    this->rotationZ = 0.;
    this->questionMarc = false;
}

void ViewWidget::moveCamera(bool up, bool down, bool forwards, bool backwards, bool left, bool right)
{
    if(this->cameraFocus == -1)
    {
        float movement = 0.5;
        if(up)
        {
            this->movementY -= movement;
        }
        else if(down)
        {
            this->movementY += movement;
        }
        else if(backwards)
        {
            this->movementX += movement;
            this->movementZ += movement;
        }
        else if(forwards)
        {
            this->movementX -= movement;
            this->movementZ -= movement;
        }
        else if(left)
        {
            this->movementX += movement;
            this->movementZ -= movement;
        }
        else if(right)
        {
            this->movementX -= movement;
            this->movementZ += movement;
        }
    }
}

void ViewWidget::rotateCamera(bool up, bool down, bool left, bool right)
{
    if(this->cameraFocus == -1)
    {
        float rotate = 0.5;
        if(up)
        {
            this->rotationZ += rotate;
        }
        if(down)
        {
            this->rotationZ -= rotate;
        }
        if(left)
        {
            this->rotationY += rotate;
        }
        if(right)
        {
            this->rotationY -= rotate;
        }
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
    float zoom = 0.25;
    if(trueForUp)
    {
        this->zoom += zoom;
    }
    else
    {
        this->zoom -= zoom;
        if(this->zoom < zoom)
        {
            this->zoom = zoom;
        }
    }
    update();
}

void ViewWidget::bigMarcTime(int state)
{
    this->questionMarc = state == 2 ? true : false;
    update();
}

void ViewWidget::resetPosition()
{
    this->movementX = 0.;
    this->movementY = 0.;
    this->movementZ = 0.;
    this->rotationY = 0.;
    this->rotationZ = 0.;
    this->zoom = 1.;
    this->cameraFocus = -1;
}

void ViewWidget::initializeGL()
{
    glClearColor(0., 0., 0., 0.);
    // big texture time
    glEnable(GL_TEXTURE_2D);

    textures.push_back(QPair<std::string, GLuint>("textures/Marc_Dekamps.bmp", MARC_DEKAMPS_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_sun.bmp", SUN_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_mercury.bmp", MERCURY_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_venus.bmp", VENUS_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/Mercator-projection.bmp", EARTH_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_moon.bmp", THE_MOON_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_mars.bmp", MARS_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_jupiter.bmp", JUPITER_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_saturn.bmp", SATURN_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_uranus.bmp", URANUS_TEX));
    textures.push_back(QPair<std::string, GLuint>("textures/2k_neptune.bmp", NEPTUNE_TEX));

    int w, h, nChannels;
    unsigned char* idata;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glGenTextures(1, &texUnits[textures.at(i).second]);
        glBindTexture(GL_TEXTURE_2D, texUnits[textures.at(i).second]);
        glPixelStorei(GL_UNPACK_ALIGNMENT, texUnits[textures.at(i).second]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        idata = stbi_load(textures.at(i).first.c_str(), &w, &h, &nChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, idata);
        stbi_image_free(idata);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // big texture time
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE, -MODEL_SIZE, MODEL_SIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

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
    std::vector<Planet> planets = this->model.getPlanets();
    float starSize = 10.;
    gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.);

    if(this->cameraFocus > -1)
    {
        Planet focusPlanet = planets.at(this->cameraFocus);
        float planetX = (planets.at(this->cameraFocus).getDistanceFromSun() + starSize)*sin(planets.at(this->cameraFocus).getPosition());
        float planetZ = (planets.at(this->cameraFocus).getDistanceFromSun() + starSize)*cos(planets.at(this->cameraFocus).getPosition());
        glScalef(this->zoom, this->zoom, this->zoom);
        glTranslatef(-planetX, 0., -planetZ);
        this->movementX = 0.;
        this->movementZ = 0.;
        this->rotationY = 0.;
    }
    else
    {
        glScalef(this->zoom, this->zoom, this->zoom);
        glTranslatef(this->movementX, this->movementY, this->movementZ);
        glRotatef(this->rotationY, 0., 1., 0.);
        glRotatef(this->rotationZ, 1., 0., 0.);
    }

    this->model.tick(this->speed);

    GLfloat sun_ambient_and_diffuse[] = {248./255., 213./255., 104./255., 1.};
    GLfloat sun_specular[] = {0., 0., 0., 0.};
    GLfloat sun_shininess = 0.;
    GLfloat sun_emission = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun_ambient_and_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, sun_shininess);
    glMaterialf(GL_FRONT, GL_EMISSION, sun_emission);

    glPushMatrix();
    glRotatef(this->model.getStarRotation(), 0., 1., 0.);
    glRotatef(90., 1., 0., 0.);
    glRotatef(180., 0., 0., 1.);

    if(this->questionMarc)
    {
        glBindTexture(GL_TEXTURE_2D, texUnits[MARC_DEKAMPS_TEX]);
    }
    else
    {
       glBindTexture(GL_TEXTURE_2D, texUnits[SUN_TEX]);
    }
    glTexEnvi(GL_TEXTURE_ENV, GL_MODULATE, texUnits[SUN_TEX]);

    glBegin(GL_POLYGON);
        GLUquadric* sunQuadric = gluNewQuadric();
        gluQuadricOrientation(sunQuadric, GLU_OUTSIDE);
        gluQuadricTexture(sunQuadric, GL_TRUE);
        gluSphere(sunQuadric, starSize, 100, 100);
        gluDeleteQuadric(sunQuadric);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    GLfloat light_pos[] = {0., 0., 0., 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat planet_ambient_and_diffuse[] = {1., 1., 1., 1.0};
    GLfloat planet_emission = 0.;
    GLfloat planet_shininess = .5;

    for(unsigned int i = 0; i < planets.size(); i++)
    {
        glPushMatrix();
        float planetX = (planets.at(i).getDistanceFromSun() + starSize)*sin(planets.at(i).getPosition());
        float planetZ = (planets.at(i).getDistanceFromSun() + starSize)*cos(planets.at(i).getPosition());
        glTranslatef(planetX, 0., planetZ);
        glRotatef(planets.at(i).getRotation(), 0, 1., 0.);
        glRotatef(90., 1., 0., 0.);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planet_ambient_and_diffuse);
        glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, planet_shininess);
        glBindTexture(GL_TEXTURE_2D, texUnits[planets.at(i).getTextureUnitIndex()]);
        glBegin(GL_POLYGON);
            GLUquadric* planetQuadric = gluNewQuadric();
            gluQuadricOrientation(planetQuadric, GLU_OUTSIDE);
            gluQuadricTexture(planetQuadric, GL_TRUE);
            gluSphere(planetQuadric, planets.at(i).getRadius(), 100, 100);
            gluDeleteQuadric(planetQuadric);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
        std::vector<Satillite*>* satillites = planets.at(i).getSatillites();
        for(unsigned int j = 0; j < satillites->size(); j++)
        {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planet_ambient_and_diffuse);
            glMaterialf(GL_FRONT, GL_EMISSION, planet_emission);
            glMaterialf(GL_FRONT, GL_SHININESS, planet_shininess);
            glPushMatrix();
            Satillite* currentSatillite = satillites->at(j);
            float satilliteX = 0., satilliteZ = 0.;
            satilliteX = (currentSatillite->getDistanceFromPlanet() + currentSatillite->getRadius()*2)*cos(currentSatillite->getPosition());
            satilliteZ = (currentSatillite->getDistanceFromPlanet() + currentSatillite->getRadius()*2)*sin(currentSatillite->getPosition());
            glTranslatef(satilliteX, 0., satilliteZ);
            glTranslatef(planetX, 0., planetZ);

            // rotate
            if(currentSatillite->isMoon())
            {
                if(currentSatillite->lightingIsSet())
                {
                    glMaterialfv(GL_FRONT, GL_AMBIENT, currentSatillite->getAmbient());
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, currentSatillite->getDiffuse());
                    glMaterialfv(GL_FRONT, GL_SPECULAR, currentSatillite->getSpecular());
                    glMaterialf(GL_FRONT, GL_SHININESS, currentSatillite->getShininess());
                    glMaterialf(GL_FRONT, GL_EMISSION, currentSatillite->getEmissive());
                }
                if(currentSatillite->getTexturesSet())
                {
                    glBindTexture(GL_TEXTURE_2D, texUnits[currentSatillite->getTextureUnitIndex()]);
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                glBegin(GL_POLYGON);
                    GLUquadric* moonQuadric = gluNewQuadric();
                    gluQuadricTexture(moonQuadric, GL_TRUE);
                    gluSphere(moonQuadric, currentSatillite->getRadius(), 100, 100);
                    gluDeleteQuadric(moonQuadric);
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);
                glMaterialfv(GL_FRONT, GL_AMBIENT, nothing_ambient_and_diffuse);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, nothing_ambient_and_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, nothing_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, nothing_shininess);
                glMaterialf(GL_FRONT, GL_EMISSION, nothing_emissive);
            }
            else
            {
                this->artificalSatillite(currentSatillite->getRadius());
                GLfloat reset_specular[] = {0., 0., 0., 0.};
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reset_specular);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glFlush();
}
