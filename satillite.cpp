#include "satillite.h"

#include <QDebug>

Satillite::Satillite(float orbitPeriod, float radius, float distanceFromPlanet, bool isMoon)
{
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromPlanet = distanceFromPlanet;
    this->moon = isMoon;
    this->orbitSpeed = 360./this->orbitPeriod;
}

void Satillite::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
    }
    qDebug() << "Moon position: " << this->position;
}

float Satillite::getDistanceFromPlanet()
{
    return this->distanceFromPlanet;
}

float Satillite::getPosition()
{
    return this->position;
}

float Satillite::getRadius()
{
    return this->radius;
}

bool Satillite::isMoon()
{
    return this->moon;
}

void Satillite::setRadius(float radius)
{
    this->radius = radius;
}

void Satillite::setDistanceFromPlanet(float distance)
{
    this->distanceFromPlanet = distance;
}


