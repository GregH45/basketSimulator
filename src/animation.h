#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "geometry.h"

class Animation
{
    private:
        double angle;
        Vector rot_vect;

    public:
        Animation(double agl, Vector);
        const double getAngle();
        void setAngle(double agl);
        const Vector getRotVect();
        void setRotVect(Vector vect);
        void update();
};


#endif // ANIMATION_H_INCLUDED
