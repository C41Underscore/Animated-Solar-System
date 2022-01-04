#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <string>
#include <QDebug>

#include "satillite.h"

class Planet
{
private:
    std::string name;
    float orbitPeriod;
    float radius;
    float distanceFromSun;
    float orbitSpeed;
    float rotationSpeed;
    float position;
    float rotation;
    GLuint textureUnitIndex;
    std::vector<Satillite*> satillites;

public:
    Planet(std::string name, float orbitPeriod, float radius, float distanceFromSun, float rotationPeriod);
    std::string getName();
    float getOrbitPeriod();
    float getRadius();
    float getDistanceFromSun();
    float getOrbitSpeed();
    float getPosition();
    GLuint getTextureUnitIndex();
    std::vector<Satillite*>* getSatillites();
    void updatePosition(float speed);
    void setRadius(float radius);
    void setDistanceFromSun(float distance);
    void setTextureUnitIndex(GLuint unit);
    void addSatillite(Satillite* newSatillite);
    void updateSatillitePositions(float speed);
    void setRotationSpeed(float newRotationSpeed);
    float getRotationSpeed() const;
    float getRotation() const;
    void setRotation(float newRotation);
};

#endif // PLANET_H
