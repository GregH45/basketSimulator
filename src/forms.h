#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"
#include "utils.h"

class Form
{
    protected:
        Color col;
        Animation anim;

    public:
        Animation& getAnim();
        void setAnim(Animation ani);
        virtual void render() = 0;
};

#endif // FORMS_H_INCLUDED
