#include "planet.h"

Planet::Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun)
{
    this->name = name;
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromSun = distanceFromSun;
    this->orbitSpeed = 360./this->orbitPeriod;
    this->position = 0;
    this->satillites = std::vector<Satillite>();
}

void Planet::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
    }
    this->updateSatillitePositions(speed);
}

void Planet::updateSatillitePositions(float speed)
{
    for(unsigned int i = 0; i < this->satillites.size(); i++)
    {
        this->satillites.at(i).updatePosition(speed);
    }
}

std::string Planet::getName()
{
    return this->name;
}

float Planet::getOrbitPeriod()
{
    return this->orbitPeriod;
}

float Planet::getRadius()
{
    return this->radius;
}

float Planet::getDistanceFromSun()
{
    return this->distanceFromSun + this->radius;
}

float Planet::getOrbitSpeed()
{
    return this->orbitSpeed;
}

float Planet::getPosition()
{
    return this->position;
}

void Planet::setRadius(float radius)
{
    this->radius = radius;
}

void Planet::setDistanceFromSun(float distance)
{
    this->distanceFromSun = distance;
}

void Planet::addSatillite(Satillite newSatillite)
{
    this->satillites.push_back(newSatillite);
}

std::vector<Satillite>* Planet::getSatillites()
{
    return &this->satillites;
}
