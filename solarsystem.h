#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <vector>
#include <string>

#define EARTH_DEGREE_MOVEMENT_PER_DAY (360/365)

class Planet
{
private:
    std::string name;
    float orbitPeriod;
    float radius;
    float distanceFromSun;
    float orbitSpeed;
    float position;
    int texture;

public:
    Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun);
    std::string getName();
    float getOrbitPeriod();
    float getRadius();
    float getDistanceFromSun();
    float getOrbitSpeed();
    float getPosition();
    void updatePosition(float speed);

    void setRadius(float radius);
    void setDistanceFromSun(float distance);
};

class SolarSystem
{
public:
    SolarSystem();
    SolarSystem(std::string starName, float starRadius);
    ~SolarSystem();
    void addPlanet(std::string name, float orbitPeriod, float radius, float distanceFromSun);
    void tick(float speed); // an Earth day
    std::vector<Planet> getPlanets();
    void normalise(float scalar, std::string specifiedPlanet = "");
    Planet getStar();

private:
    std::vector<Planet> planets;
    Planet* star;
};

#endif // SOLARSYSTEM_H
