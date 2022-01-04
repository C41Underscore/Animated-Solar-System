#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <vector>
#include <string>
#include "planet.h"

class SolarSystem
{
public:
    SolarSystem();
    SolarSystem(std::string starName, float starRotationSpeed);
    ~SolarSystem();
    void addPlanet(Planet newPlanet);
    void tick(float speed); // an Earth day
    std::vector<Planet> getPlanets();
    void normalise(float scalar, std::string specifiedPlanet = "");
    Planet getStar();

    float getStarRotation() const;
    void setStarRotation(float newStarRotation);

private:
    std::vector<Planet> planets;
    Planet* star;
    float starRotationSpeed;
    float starRotation;
};

#endif // SOLARSYSTEM_H
