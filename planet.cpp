#include "planet.h"

void Planet::setRotationSpeed(float newRotationSpeed)
{
    this->rotationSpeed = newRotationSpeed;
}

float Planet::getRotationSpeed() const
{
    return this->rotationSpeed;
}

float Planet::getRotation() const
{
    return rotation;
}

void Planet::setRotation(float newRotation)
{
    rotation = newRotation;
}

Planet::Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun, float rotationPeriod)
{
    this->name = name;
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromSun = distanceFromSun;
    this->orbitSpeed = 360./this->orbitPeriod;
    this->rotationSpeed = 360./rotationPeriod;
    this->position = 0;
    this->rotation = 0.;
    this->satillites = std::vector<Satillite*>();
}

void Planet::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
    }
    this->rotation += speed*this->rotationSpeed;
    if(this->rotation > 360.)
    {
        this->rotation -= 360.;
    }
    this->updateSatillitePositions(speed);
}

void Planet::updateSatillitePositions(float speed)
{
    for(unsigned int i = 0; i < this->satillites.size(); i++)
    {
        this->satillites.at(i)->updatePosition(speed);
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

GLuint Planet::getTextureUnitIndex()
{
    return this->textureUnitIndex;
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

void Planet::setTextureUnitIndex(GLuint unit)
{
    this->textureUnitIndex = unit;
}

void Planet::addSatillite(Satillite* newSatillite)
{
    this->satillites.push_back(newSatillite);
}

std::vector<Satillite*>* Planet::getSatillites()
{
    return &this->satillites;
}
