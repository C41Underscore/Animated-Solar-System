#ifndef SATILLITE_H
#define SATILLITE_H

#import <math.h>

class Satillite
{
public:
    Satillite(float orbitPeriod, float radius, float distanceFromPlanet, bool isMoon);

private:
    float orbitPeriod;
    float radius;
    float distanceFromPlanet;
    float orbitSpeed;
    float position;
    float verticalPosition;
    int texture;
    bool moon;

public:
    void updatePosition(float speed);
    float getDistanceFromPlanet();
    float getRadius();
    float getOrbitSpeed();
    float getPosition();
    float getVerticalPosition();
    bool isMoon();
    void setRadius(float radius);
    void setDistanceFromPlanet(float distance);
};

#endif // SATILLITE_H
