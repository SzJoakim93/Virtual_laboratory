#include "GL/gl.h"
#include "SDL/SDL.h"
#include "gl/glu.h"

#include "Application.h"
#include "Object.h"

#include <ctime>
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    char levelpath[30] = {0};

    if (argc > 1 && !strcmp(argv[1], "-editor"))
        strcpy(levelpath, argv[2]);

    bool quit;/* Az Application fo ciklusanak a futasat jelzi.
        Ha az erteke igazra allitodik, akkor az Application a
        kovetkezo iteracio elejen kilep.*/

    srand(time(0));
    Application Application("Virtual Laboratory v0.95 Beta", levelpath); //kepernyo inicializalasa
    quit = false; //kilepes feltetele

    while (!quit) //a fo ciklus kezdete
    {
        Application.handleSDL2Events(quit); //az esemenyvezerlo megnyitasa (pl billentyuzetkezeles)
        Application.render(); //kepernyo osszeallitasa
    }

    return 0;
}
