#ifndef SATILLITE_H
#define SATILLITE_H

#include <math.h>
#include <GL/glu.h>

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
    GLuint textureUnitIndex;
    bool texturesSet;
    bool lightingSet;
    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;
    GLfloat shininess;
    GLfloat emissive;
    bool moon;

public:
    void updatePosition(float speed);
    float getDistanceFromPlanet();
    float getRadius();
    float getOrbitSpeed();
    float getPosition();
    GLfloat* getAmbient();
    GLfloat* getDiffuse();
    GLfloat* getSpecular();
    GLfloat getShininess();
    GLfloat getEmissive();
    GLuint getTextureUnitIndex();
    bool isMoon();
    bool lightingIsSet();
    void setRadius(float radius);
    void setDistanceFromPlanet(float distance);
    void setLighting(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat emissive);
    void setTextureUnitIndex(GLuint index);
    bool getTexturesSet() const;
};

#endif // SATILLITE_H
