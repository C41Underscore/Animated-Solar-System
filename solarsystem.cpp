#include "solarsystem.h"

#include <QDebug>

SolarSystem::SolarSystem()
{

}

SolarSystem::SolarSystem(std::string starName, float starRadius, float starRotationSpeed)
{
    this->star = new Planet(starName, 0., starRadius, 0., starRotationSpeed);
    this->planets = std::vector<Planet>();
    this->starRotation = 0.;
    this->starRotationSpeed = 360./starRotationSpeed;
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
    this->starRotation += speed*starRotationSpeed;
    if(this->starRotation > 360.)
    {
        this->starRotation -= 360.;
    }
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
        std::vector<Satillite*>* satillites = this->planets.at(i).getSatillites();
        for(unsigned int j = 0; j < satillites->size(); j++)
        {
//            float newSatilliteDistance = satillites->at(j).getDistanceFromPlanet()/this->planets.at(i).getDistanceFromSun();
            float newSatilliteDistance = satillites->at(j)->getDistanceFromPlanet()/highest_distance;
//            float newSatilliteRadius = satillites->at(j).getRadius()/this->planets.at(i).getRadius();
            float newSatilliteRadius = satillites->at(j)->getRadius()/highest_radius;
            satillites->at(j)->setDistanceFromPlanet(newSatilliteDistance);
            satillites->at(j)->setRadius(newSatilliteRadius);
        }
        float newRadius = this->planets.at(i).getRadius()/highest_radius;
        float newDistance = (this->planets.at(i).getDistanceFromSun()/highest_distance)*scalar;
        this->planets.at(i).setRadius(newRadius);
        this->planets.at(i).setDistanceFromSun(newDistance);
        for(unsigned int j = 0; j < satillites->size(); j++)
        {
            satillites->at(j)->setDistanceFromPlanet(satillites->at(j)->getDistanceFromPlanet() + this->planets.at(i).getRadius());
        }
    }
}

Planet SolarSystem::getStar()
{
    return *this->star;
}

float SolarSystem::getStarRotation() const
{
    return starRotation;
}

void SolarSystem::setStarRotation(float newStarRotation)
{
    starRotation = newStarRotation;
}

SolarSystem::~SolarSystem()
{
    delete this->star;
}
