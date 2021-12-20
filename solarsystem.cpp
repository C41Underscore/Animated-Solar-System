#include "solarsystem.h"

#include <QDebug>

SolarSystem::SolarSystem()
{

}

SolarSystem::SolarSystem(std::string starName, float starRadius)
{
    this->star = new Planet(starName, 0., starRadius, 0.);
    this->planets = std::vector<Planet>();
}

void SolarSystem::addPlanet(std::string name, float orbitPeriod, float radius, float distanceFromSun)
{
    Planet newPlanet(name, orbitPeriod, radius, distanceFromSun+this->star->getRadius());
    this->planets.push_back(newPlanet);
}

std::vector<Planet> SolarSystem::getPlanets()
{
    return this->planets;
}

void SolarSystem::tick(float speed)
{
    for(unsigned int i = 0; i < this->planets.size(); i++)
    {
        this->planets.at(i).updatePosition(speed);
    }
}

void SolarSystem::normalise(float scalar)
{
    float highest_radius = -1.;
    float highest_distance = -1.;
    for(unsigned int i = 0; i < this->planets.size(); i++)
    {
        if(this->planets.at(i).getRadius() > highest_radius)
        {
            highest_radius = this->planets.at(i).getRadius();
        }
        if(this->planets.at(i).getDistanceFromSun() > highest_distance)
        {
            highest_distance = this->planets.at(i).getDistanceFromSun();
        }
    }
    for(unsigned int i = 0; i < this->planets.size(); i++)
    {
        float newRadius = this->planets.at(i).getRadius()/highest_radius;
        float newDistance = (this->planets.at(i).getDistanceFromSun()/highest_distance)*scalar + this->star->getRadius()/highest_distance;
        this->planets.at(i).setRadius(newRadius);
        this->planets.at(i).setDistanceFromSun(newDistance);
    }

}

Planet SolarSystem::getStar()
{
    return *this->star;
}

SolarSystem::~SolarSystem()
{
    delete this->star;
}

Planet::Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun)
{
    this->name = name;
    this->orbitPeriod = orbitPeriod;
    this->radius = radius;
    this->distanceFromSun = distanceFromSun;
    this->orbitSpeed = 360./this->orbitPeriod;
    this->position = 0;
}

void Planet::updatePosition(float speed)
{
    this->position += speed*this->orbitSpeed;
    if(this->position > 360.)
    {
        this->position -= 360.;
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
