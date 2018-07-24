#ifndef LABORATORY_H
#define LABORATORY_H

#include "Object.h"
#include <stdio.h>
#include <dirent.h>
#include <windows.h>
#define N 120

class Laboratory
{
    public:
        Laboratory(char * no_tutorial, int & area, int * s_width, int * s_height, char * browser_path);
        ~Laboratory();
        void load(char * path, const int & index);
        void lab_events(int & area);
        void back_to_view();
        void lab_rendering(int & area);
        void reset();
        void view_up(const int & x);
        void view_down(const int & x);
        void view_left(const int & x);
        void view_right(const int & x);
        void click(int & area, const int & x, const int & y);
        void writing(char letter);
        void unlock_cursor();
        void select_area();
        void delete_item();
        void set_Deleting(const bool & x);
    protected:
    private:
        Object *** objects;
        Object * arrow;
        Object *** titles;
        Object * tabs[40];
        Object * map1;
        Object * point_arrow;
        Object * tutorial;
        Object * tutorial2;
        Object * tutorial3;
        Object * question;
        int * obj_sum;
        int * title_sum;

        char browser_path[128];

        int * s_width;
        int * s_height;
        int & area;

        char * levelpath;
        float cameraX;
        float cameraY;
        float cameraZ;

        char ** chat_title;
        char ** const_titles;

        char ** patients;
        int patient_numbers;
        int patient_ptr;
        int patient_page;
        char ** basic;
        int basic_numbers;
        int basic_ptr;
        char ** blood_pressure;
        int blood_numbers;
        int blood_ptr;
        char ** diabetes;
        int diabetes_numbers;
        int diabetes_ptr;
        char ** blood;
        int bloodres_ptr;
        char ** medicines; //szedett gyogyszerek listaja
        int medicin_numbers; //maximalis szedett gyogyszerek
        int medicin_ptr; //kijelolt gyogyszer
        int medicin_page;
        char ** prev_illnes;
        int ill_numbers;
        int ill_ptr;
        char ** chron_illnes;
        int chron_numbers;
        int chron_ptr;
        char ** allergic;
        int allergic_numbers;
        int allergic_ptr;
        char ** base_medicines; //receptek listaja
        int bmedicine_numbers; //a lista maximalis merete
        int descreption_ptr; //kijeleolt recept
        int descreption_page;
        char ** reported;
        int reported_numbers;
        int reported_ptr;
        int reported_page;
        int blood_state;
        int ekg_state;
        char editing_string[32];
        char si[16];
        char ** private_descreption;
        int private_ptr;
        int private_number;
        bool isEditedPatient;
        bool isDeleting;

        int selected[6];
        int area_selected;
        bool isModyflied_database;
        bool isModyflied_patient;
        int tutorial_ptr;
        bool enableTutorial;

        void load_list(FILE * file, char ** destination, int & x);
        void save_list(FILE * file, char ** source, int & x);
        void malloc(char *** destination, int x, int y);
        void dealloc(char *** destination, int x);
        void edit_text(char * title, char & letter);
        void split(char * c1, char c2);
        void split(char * c1, char * c2, char c3);
        void split(char * c1, char * c2, char * c3, char c4);
        void select_patient(int i, int prev_ptr);
        void save_patients(int prev_ptr);
        void deleting(char ** data, int & ptr, int & number);
};

#endif // LABORATORY_H
