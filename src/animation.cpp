#include "animation.h"

Animation::Animation(double agl, Vector vect)
{
    angle = agl;
    rot_vect = vect;
}

const double Animation::getAngle()
{
    return angle;
}

void Animation::setAngle(double agl)
{
    angle = agl;
}

const Vector Animation::getRotVect()
{
    return rot_vect;
}

void Animation::setRotVect(Vector vect)
{
    rot_vect = vect;
}

void Animation::update()
{
    // TODO
}
