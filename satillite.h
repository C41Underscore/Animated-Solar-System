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
    bool isMoon;

public:
    void updatePosition(float speed);
    float getDistanceFromPlanet();
    float getOrbitSpeed();
    float getPosition();
};

#endif // SATILLITE_H
