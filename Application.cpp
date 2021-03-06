#include "Application.h"

Application::Application(char *frame_title, char * no_tutorial)
{
    area = 1;

    //ctor
    this->depth = 32;
    this->s_near=0.001;
    this->s_far=30.0;
    this->valtozas=false;
    this->setres=0;
    keystates = SDL_GetKeyState(NULL);
    SDL_Init(SDL_INIT_EVERYTHING);

    FILE * file = fopen("settings.ini", "r");

    fscanf(file, "screen_width=%d\n", &width);
    fscanf(file, "screen_height=%d\n", &height);
    fscanf(file, "fullscreen=%d\n", &fullscreen);
    fscanf(file, "key_layout=%c\n", &key_layout);
    fscanf(file, "browser_path=\"%s\"", browser_path);

    fclose(file);
    //a kepernyo beallitasa
    if (fullscreen)
    {
        SDL_SetVideoMode(width, height, depth,
                         SDL_OPENGL | SDL_FULLSCREEN);
    }
    else
    {
        SDL_SetVideoMode(width, height, depth,
                         SDL_OPENGL);
    }

    SDL_WM_SetCaption(frame_title, 0);

    laboratory = new Laboratory(no_tutorial, area, &width, &height, browser_path);

    //glClearColor(1.0, 1.0, 1.0, 0.0);

}

Application::~Application()
{
    if (valtozas)
    {
        FILE * file = fopen("settings.ini", "w");

        fprintf(file, "screen_width=%d\n", width);
        fprintf(file, "screen_height=%d\n", height);
        fprintf(file, "fullscreen=%d\n", fullscreen);
        fprintf(file, "key_layout=%c\n", key_layout);
        fprintf(file, "browser_path=\"%s\"", browser_path);

        fclose(file);
    }

    delete laboratory;

}

//a lataotavolsag megadasa
void Application::eLoadProjectionMatrix(int width, int height, float s_near, float s_far)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / (float) height, s_near, s_far);
}

void Application::handleSDLEvents(bool & quit)
{
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quit = true;
        else if (event.type == SDL_MOUSEMOTION && area == 1)
        {
            if (event.motion.x < width >> 1)
                laboratory->view_left(1+((width>>1) - event.motion.x)>>2);

            if (event.motion.x > width >> 1)
                 laboratory->view_right(1+(event.motion.x - (width>>1))>>2);

            if (event.motion.y < height >> 1)
                laboratory->view_up(1+((height >>1) - event.motion.y)>>2);

            if (event.motion.y > height >> 1)
                laboratory->view_down(1+(event.motion.y - (height>>1))>>2);

            SDL_WarpMouse(width / 2, height / 2);
        }
        else if (event.button.state == SDL_BUTTON_LEFT)
        {
            laboratory->click(area, event.motion.x, event.motion.y);
        }
        else if (keystates[SDLK_ESCAPE])
        {
            if (area > 1)
                laboratory->back_to_view();
            else
                quit = true;
        }
        else if (keystates[SDLK_LCTRL] && keystates[SDLK_DELETE])
            laboratory->set_Deleting(true);
        else if (key_layout == 'E' && keystates[SDLK_SLASH] || (keystates[SDLK_KP_DIVIDE] || keystates[SDLK_RALT] && keystates[SDLK_q] || (keystates[SDLK_RSHIFT] || keystates[SDLK_LSHIFT]) && keystates[SDLK_6]))
        {
            laboratory->writing('/');
            laboratory->writing('p');
        }
        else if (keystates[SDLK_5] && (keystates[SDLK_RSHIFT] || keystates[SDLK_LSHIFT]))
            laboratory->writing('%');
        else if ((keystates[SDLK_SLASH] || keystates[SDLK_COMMA]) && (keystates[SDLK_RSHIFT] || keystates[SDLK_LSHIFT]))
            laboratory->writing('?');
        else if (keystates[SDLK_COMMA])
            laboratory->writing(',');
        else if (keystates[SDLK_q])
            laboratory->writing('q');
        else if (keystates[SDLK_w])
            laboratory->writing('w');
        else if (keystates[SDLK_e])
            laboratory->writing('e');
        else if (keystates[SDLK_r])
            laboratory->writing('r');
        else if (keystates[SDLK_t])
            laboratory->writing('t');
        else if (key_layout == 'E' && keystates[SDLK_z] || key_layout == 'H' && keystates[SDLK_y])
            laboratory->writing('z');
        else if (keystates[SDLK_u])
            laboratory->writing('u');
        else if (keystates[SDLK_i])
            laboratory->writing('i');
        else if (keystates[SDLK_o])
            laboratory->writing('o');
        else if (keystates[SDLK_p])
            laboratory->writing('p');
        else if (keystates[SDLK_a])
            laboratory->writing('a');
        else if (keystates[SDLK_s])
            laboratory->writing('s');
        else if (keystates[SDLK_d])
            laboratory->writing('d');
        else if (keystates[SDLK_f])
            laboratory->writing('f');
        else if (keystates[SDLK_g])
            laboratory->writing('g');
        else if (keystates[SDLK_h])
            laboratory->writing('h');
        else if (keystates[SDLK_j])
            laboratory->writing('j');
        else if (keystates[SDLK_k])
            laboratory->writing('k');
        else if (keystates[SDLK_l])
            laboratory->writing('l');
        else if (key_layout == 'E' && keystates[SDLK_y] || key_layout == 'H' && keystates[SDLK_z])
            laboratory->writing('y');
        else if (keystates[SDLK_x])
            laboratory->writing('x');
        else if (keystates[SDLK_c])
            laboratory->writing('c');
        else if (keystates[SDLK_v])
            laboratory->writing('v');
        else if (keystates[SDLK_b])
            laboratory->writing('b');
        else if (keystates[SDLK_n])
            laboratory->writing('n');
        else if (keystates[SDLK_m])
            laboratory->writing('m');
        else if (keystates[SDLK_SPACE])
            laboratory->writing('_');
        else if (keystates[SDLK_0] || keystates[SDLK_BACKQUOTE] || keystates[SDLK_KP0])
            laboratory->writing('0');
        else if (keystates[SDLK_1] || keystates[SDLK_KP1])
            laboratory->writing('1');
        else if (keystates[SDLK_2] || keystates[SDLK_KP2])
            laboratory->writing('2');
        else if (keystates[SDLK_3] || keystates[SDLK_KP3])
            laboratory->writing('3');
        else if (keystates[SDLK_4] || keystates[SDLK_KP4])
            laboratory->writing('4');
        else if (keystates[SDLK_5] || keystates[SDLK_KP5])
            laboratory->writing('5');
        else if (keystates[SDLK_6] || keystates[SDLK_KP6])
            laboratory->writing('6');
        else if (keystates[SDLK_7] || keystates[SDLK_KP7])
            laboratory->writing('7');
        else if (keystates[SDLK_8] || keystates[SDLK_KP8])
            laboratory->writing('8');
        else if (keystates[SDLK_9] || keystates[SDLK_KP9])
            laboratory->writing('9');
        else if (keystates[SDLK_PERIOD])
            laboratory->writing('.');
        else if (keystates[SDLK_BACKSPACE] || keystates[SDLK_DELETE])
            laboratory->writing(0);
        else if (keystates[SDLK_RETURN] || keystates[SDLK_KP_ENTER])
            laboratory->writing(1);
        else if (keystates[SDLK_RSHIFT] || keystates[SDLK_LSHIFT])
            laboratory->select_area();
        else if (keystates[SDLK_LALT])
            laboratory->unlock_cursor();
    }

    laboratory->lab_events(area);
}

void Application::handleSDLRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    eLoadProjectionMatrix(width, height, s_near, s_far);
    //glEnable(GL_NORMALIZE);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );


    //glEnable(GL_LIGHT0);

    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 8);



    /*glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, md);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ld);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);*/

    /*if (area == 0 || area == 5 || area == 6 || area == 7)
        menu->megjelenit(area);*/
    laboratory->lab_rendering(area);

    /*if (area == 8 || area == 9)
        menu->megjelenit_res(area, setres);*/

    glDisable(GL_BLEND);
    glDisable( GL_LINE_SMOOTH );
    glDisable( GL_POLYGON_SMOOTH );
    //glDisable(GL_LIGHTING);
    //glDisable(GL_NORMALIZE);
    SDL_GL_SwapBuffers();

    SDL_Delay(30);
}
