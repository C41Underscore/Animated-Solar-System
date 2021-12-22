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

void SolarSystem::addPlanet(Planet newPlanet)
{
    newPlanet.setDistanceFromSun(newPlanet.getDistanceFromSun()+this->star->getRadius());
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

void SolarSystem::normalise(float scalar, std::string specifiedPlanet)
{
    float highest_radius = -1.;
    float highest_distance = -1.;
    bool validPlanet = false;
    if(specifiedPlanet.compare("The Sun") == 0)
    {
        highest_radius = this->star->getRadius();
        for(unsigned int i = 0; i < this->planets.size(); i++)
        {
            if(this->planets.at(i).getDistanceFromSun() > highest_distance)
            {
                highest_distance = this->planets.at(i).getDistanceFromSun();
            }
        }
    }
    else if(specifiedPlanet.compare("") != 0)
    {
        for(unsigned int i = 0; i < this->planets.size(); i++)
        {
            if(specifiedPlanet.compare(this->planets.at(i).getName()) == 0)
            {
                validPlanet = true;
                highest_radius = this->planets.at(i).getRadius();
                highest_distance = this->planets.at(i).getDistanceFromSun();
            }
        }
    }
    if(!validPlanet)
    {
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
    }
    for(unsigned int i = 0; i < this->planets.size(); i++)
    {
        float newRadius = this->planets.at(i).getRadius()/highest_radius;
        float newDistance = (this->planets.at(i).getDistanceFromSun()/highest_distance)*scalar;
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
