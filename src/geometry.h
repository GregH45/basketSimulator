#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <cmath>

class Coordinates
{
    public:
        double x, y, z;
        Coordinates(double xx=0, double yy=0, double zz=0);
};

class Point : public Coordinates
{
    public:
        Point(double xx=0, double yy=0, double zz=0) : Coordinates(xx, yy, zz) {};
};

class Vector : public Coordinates
{
    public:
        Vector(double xx, double yy, double zz) : Coordinates(xx, yy, zz) {};
        Vector(Point, Point);
        Vector();
        double norm();
};

double distance(Point p1, Point p2);

#endif // GEOMETRY_H_INCLUDED
