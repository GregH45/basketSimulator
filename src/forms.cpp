#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"

Animation& Form::getAnim()
{
    return anim;
}

void Form::setAnim(Animation ani)
{
    anim = ani;
}
