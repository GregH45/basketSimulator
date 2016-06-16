#include "sphere.h"
#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>

#define SLICE 100
#define STACK 100

Sphere::Sphere(Point c, double r, Color cl)
{
    center = c;
    radius = r;
    col = cl;
}

const Point Sphere::getCenter()
{
    return center;
}

void Sphere::setCenter(Point c)
{
    center = c;
}

void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    glPushMatrix();
    glTranslated(center.x,center.y,center.z);
    glColor3f(col.r,col.g,col.b);
    gluSphere(quad,radius,SLICE,STACK);
    glPopMatrix();

    gluDeleteQuadric(quad);
}
