#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <string>

#include "satillite.h"

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
    std::vector<Satillite> satillites;

public:
    Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun);
    std::string getName();
    float getOrbitPeriod();
    float getRadius();
    float getDistanceFromSun();
    float getOrbitSpeed();
    float getPosition();
    std::vector<Satillite> getSatillites();
    void updatePosition(float speed);
    void setRadius(float radius);
    void setDistanceFromSun(float distance);
    void addSatillite(Satillite newSatillite);
    void updateSatillitePositions();
};

#endif // PLANET_H
