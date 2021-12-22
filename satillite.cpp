#include "satillite.h"

Satillite::Satillite(float orbitPeriod, float radius, float distanceFromPlanet, bool isMoon)
{
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromPlanet = distanceFromPlanet;
    this->isMoon = isMoon;
}

void Satillite::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
    }
}

float Satillite::getPosition()
{
    return this->position;
}
