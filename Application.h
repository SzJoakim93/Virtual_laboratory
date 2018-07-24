#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdio>

#include "GL/gl.h"
#include "SDL/SDL.h"
#include "gl/glu.h"

#include "Laboratory.h"


class Application
{
    public:

        Application(char *frame_title, char * no_tutorial);
        ~Application();
        void eLoadProjectionMatrix(int width, int height, float near, float far);
        void handleSDLEvents(bool & quit);
        void handleSDLRender();
    protected:
    private:
        Laboratory * laboratory;
        int width; // screen width.
        int height; // screen height
        int depth; // color depth
        bool fullscreen; // it is fullscreen
        char key_layout; //keyboard language layout (E: english, H: hungarian)
        char browser_path[128];
        float s_near; //begining of looking range
        float s_far; //looking range
        SDL_Event event;
        Uint8 *keystates;
        int area;
        bool valtozas;
        int setres;
};

#endif // APPLICATION_H
