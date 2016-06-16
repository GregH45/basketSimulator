#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "geometry.h"
#include "forms.h"
#include "sphere.h"

#define JUMP 0.2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_FORMS_NUMBER 10
#define ANIM_DELAY 10

using namespace std;

bool init(SDL_Window** window, SDL_GLContext* context);
bool initGL();
void update(Form* formlist[MAX_FORMS_NUMBER]);
const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos);
void close(SDL_Window** window);

bool init(SDL_Window** window, SDL_GLContext* context)
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        *window = SDL_CreateWindow( "TP intro OpenGL / SDL 2",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( *window == NULL ) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        } else {
            *context = SDL_GL_CreateContext(*window);
            if( *context == NULL ) {
                cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            } else {
                if(SDL_GL_SetSwapInterval(1) < 0)
                    cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
                if( !initGL() )
                {
                    cout << "Unable to initialize OpenGL!"  << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}


bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gluPerspective(40.0, (GLdouble)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    error = glGetError();
    if( error != GL_NO_ERROR ) {
        cout << "Error initializing OpenGL!  " << gluErrorString( error ) << endl;
        success = false;
    }
    glEnable(GL_DEPTH_TEST);

    return success;
}

void update(Form* formlist[MAX_FORMS_NUMBER])
{
    unsigned short i = 0;

    while(formlist[i] != NULL){
        formlist[i]->getAnim().update();
        i++;
    }
}

const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Positionnement de la caméra
    gluLookAt(cam_pos.x,cam_pos.y,cam_pos.z, 0.0,0.0,0.0, 0.0,1.0,0.0);

    // Création du repère
    glPushMatrix();
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();
    glPopMatrix();

    // Création de la sphère
    Point center(0.0,0.0,0.0);
    Sphere s1(center,2,YELLOW);
    formlist[0] = &s1;

    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        glPushMatrix();
        formlist[i]->render();
        glPopMatrix();
        i++;
    }
}

void close(SDL_Window** window)
{
    SDL_DestroyWindow(*window);
    *window = NULL;
    SDL_Quit();
}

int main(int argc, char* args[])
{
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;

    if( !init(&gWindow, &gContext)){
        cout << "Failed to initialize!" << endl;
    } else {
        bool quit = false;
        Uint32 current_time, previous_time;
        SDL_Event event;

        Point camera_position(0.0, 0.0, 5.0);

        Form* forms_list[MAX_FORMS_NUMBER];
        unsigned short number_of_forms = 0, i;
        forms_list[number_of_forms] = NULL;

        for (i=0; i<MAX_FORMS_NUMBER; i++)
        {
            forms_list[i] = NULL;
        }
        previous_time = SDL_GetTicks();

        while(!quit) {
            while(SDL_PollEvent(&event) != 0) {
                int x = 0, y = 0;
                SDL_Keycode key_pressed = event.key.keysym.sym;

                if (event.type == SDL_QUIT) {
                    quit = true;
                } else if (event.type == SDL_KEYDOWN) {
                    SDL_GetMouseState(&x, &y);
                    switch(key_pressed) {
                            case SDLK_q:
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_UP:
                                camera_position.y += JUMP;
                                break;
                            case SDLK_DOWN:
                                camera_position.y -= JUMP;
                                break;
                            case SDLK_LEFT:
                                camera_position.x += JUMP;
                                break;
                            case SDLK_RIGHT:
                                camera_position.x -= JUMP;
                                break;
                            case SDLK_KP_PLUS:
                                camera_position.z += JUMP;
                                break;
                            case SDLK_KP_MINUS:
                                camera_position.z -= JUMP;
                                break;
                            default:
                                break;
                    }
                }
            }

            current_time = SDL_GetTicks();
            if ((current_time - previous_time) > ANIM_DELAY) {
                previous_time = current_time;
                update(forms_list);
            }

            render(forms_list, camera_position);
            SDL_GL_SwapWindow(gWindow);
        }
    }
    close(&gWindow);

    return 0;
}
