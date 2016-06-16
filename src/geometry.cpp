#include "geometry.h"

Coordinates::Coordinates(double xx, double yy, double zz)
{
    x=xx; y=yy; z=zz;
}

Vector::Vector(Point p1, Point p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

Vector::Vector()
{
    x = 1.0;
    y = 0.0;
    z = 0.0;
}

double Vector::norm()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double distance(Point p1, Point p2)
{
    Vector vect(p1, p2);
    return vect.norm();
}
