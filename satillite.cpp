#include "satillite.h"

#include <QDebug>

Satillite::Satillite(float orbitPeriod, float radius, float distanceFromPlanet, bool isMoon)
{
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromPlanet = distanceFromPlanet;
    this->moon = isMoon;
    this->orbitSpeed = 360./this->orbitPeriod;
    this->position = 0.;
    this->texturesSet = false;
    if(!isMoon)
    {
        this->verticalPosition = 0.;
    }
    else
    {
        this->verticalPosition = -1.;
    }
}

void Satillite::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
    }
    if(!this->isMoon())
    {
        this->verticalPosition += speed*this->orbitSpeed;
//        qDebug() << this->verticalPosition;
        if(this->verticalPosition > 360.)
        {
            this->verticalPosition -= 360.;
        }
    }
}

float Satillite::getDistanceFromPlanet()
{
    return this->distanceFromPlanet;
}

float Satillite::getPosition()
{
    return this->position;
}

float Satillite::getVerticalPosition()
{
    return this->verticalPosition;
}

float Satillite::getRadius()
{
    return this->radius;
}

GLfloat* Satillite::getAmbient()
{
    return this->ambient;
}

GLfloat* Satillite::getDiffuse()
{
    return this->diffuse;
}

GLfloat* Satillite::getSpecular()
{
    return this->specular;
}

GLfloat Satillite::getShininess()
{
    return this->shininess;
}

GLfloat Satillite::getEmissive()
{
    return this->emissive;
}

bool Satillite::isMoon()
{
    return this->moon;
}

bool Satillite::texturesAreSet()
{
    return this->texturesSet;
}

void Satillite::setRadius(float radius)
{
    this->radius = radius;
}

void Satillite::setDistanceFromPlanet(float distance)
{
    this->distanceFromPlanet = distance;
}

void Satillite::setLighting(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, GLfloat emissive)
{
    if(this->isMoon())
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
        this->emissive = emissive;
        this->texturesSet = true;
    }
}
