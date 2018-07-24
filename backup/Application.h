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

        Application(char *frame_title, char * levelpath);
        ~Application();
        void eLoadProjectionMatrix(int width, int height, float near, float far);
        void handleSDL2Events(bool & quit);
        void render();
    protected:
    private:
        Laboratory * laboratory;
        //Menu * menu;
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
        bool hang;
        bool zene;
        bool valtozas;
        int setres;

        float ms[4];
        float md[4];
        float direction[4];
        float ld[4];
        float ls[4];
};

#endif // APPLICATION_H
