#ifndef SATILLITE_H
#define SATILLITE_H

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
    int texture;
    bool moon;

public:
    void updatePosition(float speed);
    float getDistanceFromPlanet();
    float getRadius();
    float getOrbitSpeed();
    float getPosition();
    bool isMoon();
    void setRadius(float radius);
    void setDistanceFromPlanet(float distance);
};

#endif // SATILLITE_H
