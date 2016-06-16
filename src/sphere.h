#ifndef SPHERE_H
#define SPHERE_H
#include "forms.h"

class Sphere : public Form
{
    private:
        Point center;
        double radius;

    public:
        Sphere(Point c = Point(), double r = 1.0, Color cl = Color());
        const Point getCenter();
        void setCenter(Point c);
        void render();
};

#endif // SPHERE_H
