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
    char no_tutorial[32];

    if (argc > 1 && !strcmp(argv[1], "-no_tutorial"))
        strcpy(no_tutorial, argv[1]);

    bool quit;/* Az Application fo ciklusanak a futasat jelzi.
        Ha az erteke igazra allitodik, akkor az Application a
        kovetkezo iteracio elejen kilep.*/

    srand(time(0));
    Application Application("Virtual Laboratory v1.0", no_tutorial); //kepernyo inicializalasa
    quit = false; //kilepes feltetele

    while (!quit) //a fo ciklus kezdete
    {
        Application.handleSDLEvents(quit); //az esemenyvezerlo megnyitasa (pl billentyuzetkezeles)
        Application.handleSDLRender(); //kepernyo osszeallitasa
    }

    return 0;
}
