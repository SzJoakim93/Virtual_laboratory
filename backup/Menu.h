#ifndef MENU_H
#define MENU_H

#include "Object.h"
#include "Laboratory.h"

class Menu
{
    public:
        Menu();
        void fel(); //kurzor elmozditasa felfele
        void le(); //kurzor elmozditasa lefele
        void balra(); //kurzor elmozditasa balra
        void jobbra(); //kurzor elmozditasa jobbra
        //void setelemek(Multi_elem * beelemek);
        void megjelenit(int & area); //menu elemeinek megjelenitese
        void megjelenit_res(int & area, int & setres); //menu elemeinek megjelenitese
        int getcursor();
        void setmaxcursor(int becursor);
        void setcursor(int becursor);
        void setcursor();
        void enter(int & area, bool & quit, bool & valtozas, int & width, int & height, int & setres, Laboratory & Laboratory);
    protected:
    private:
        int cursor; //kurzor hanyadik menuponton van 0-tol kezdve
        int maxcursor; //maximum hany menupont van
        //Multi_elem * elemek;
        int DB;
        bool * hang;
        bool * zene;
        bool * fullscreen;
        char zenelista[30][18];
        char palyalista[30][18];
        int maxpalya;
        Object * objects[20];
};

#endif // MENU_H
