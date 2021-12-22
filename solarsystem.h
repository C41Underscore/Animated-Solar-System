#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <vector>
#include <string>
#include "planet.h"

#define EARTH_DEGREE_MOVEMENT_PER_DAY (360/365)

class SolarSystem
{
public:
    SolarSystem();
    SolarSystem(std::string starName, float starRadius);
    ~SolarSystem();
    void addPlanet(Planet newPlanet);
    void tick(float speed); // an Earth day
    std::vector<Planet> getPlanets();
    void normalise(float scalar, std::string specifiedPlanet = "");
    Planet getStar();

private:
    std::vector<Planet> planets;
    Planet* star;
};

#endif // SOLARSYSTEM_H
