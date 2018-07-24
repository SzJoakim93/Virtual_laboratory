#include "Laboratory.h"

Laboratory::Laboratory(char * level_path, int & area, int * s_width, int * s_height, char * browser_path) :area(area)
{
    //ctor
    this->s_width = s_width;
    this->s_height = s_height;
    strcpy(this->browser_path, browser_path);
    isText = false;
    isModify = false;
    bal = false;
    jobb = false;
    objects = new Object ** [2];
    titles = new Object ** [2];
    obj_sum = new int [2];
    title_sum = new int [2];
    objects[0] = new Object* [N];
    objects[1] = new Object* [N];
    titles[0] = new Object* [60];
    titles[1] = new Object* [60];
    area_selected = 0;
    descreption_ptr = -1;
    descreption_page = 0;
    basic_ptr = -1;
    patient_ptr = 0;
    patient_page = 0;
    blood_ptr = -1;
    diabetes_ptr = -1;

    medicin_ptr = -1;
    medicin_page = 0;

    reported_ptr = -1;
    reported_page = 0;
    bloodres_ptr = -1;
    ill_numbers = 0;
    ill_ptr = -1;

    chron_ptr = -1;
    allergic_ptr = -1;
    private_ptr = -1;
    basic_numbers = 6;

    bmedicine_numbers = 0;
    reported_numbers = 0;

    isModyflied_database = false;
    isModyflied_patient = false;
    isEditedPatient = false;
    tutorial_ptr = 0;
    enableTutorial = true;
    isDeleting = false;

    malloc(&const_titles, 3, 32);
    malloc(&chat_title, 9, 32);
    malloc(&patients, 32, 32);
    malloc(&basic, 10, 32);
    malloc(&diabetes, 10, 32);
    malloc(&blood_pressure, 10, 32);
    malloc(&blood, 8, 32);
    malloc(&medicines, 10, 32);
    malloc(&prev_illnes, 10, 32);
    malloc(&chron_illnes, 10, 32);
    malloc(&allergic, 10, 32);
    malloc(&base_medicines, 32, 32);
    malloc(&reported, 32, 32);
    malloc(&private_descreption, 10, 32);


    for (int i=0; i<6; i++)
        selected[i] = 0;

    for (int i=0; i<9; i++)
        chat_title[i][0] = 0;

    strcpy(const_titles[0], "chat");
    strcpy(const_titles[1], "list");
    strcpy(const_titles[2], "web");

    cameraX=0.0;
    cameraY=0.0;
    cameraZ=0.0;

    float place = 0.0;
    if ((float)(*s_width)/(float)(*s_height) < 1.3) //5:4
        place = 0.0001;
    else if ((float)(*s_width)/(float)(*s_height) < 1.4) //4:3
        place = 0.0;
    else if ((float)(*s_width)/(float)(*s_height) < 1.7) //16:10
        place = -0.0006;
    else if ((float)(*s_width)/(float)(*s_height) < 1.8) //16:9
        place = -0.0009;

    arrow = new Object(-0.0024+place, -0.0018, 0.0, //koordinatak
                       0, 0, 0, //elforgatas
                       0.00028, 1.0, 0.00056, //atmeretezes
                       true, "Textures/arrow.bmp", 0, "negyzet", 3, 0);

    map1 = new Object(0.0008, 0.0001, 0.0, //koordinatak
                      0, 0, 0, //elforgatas
                      0.006, 1.0, 0.009, //atmeretezes
                      true, "Textures/map1.bmp", 0, "negyzet", 3, 0);

    point_arrow = new Object(0.00012, 0.0006, 0.0, //koordinatak
                             0, 0, 30, //elforgatas
                             0.00014, 1.0, 0.00028, //atmeretezes
                             true, "Textures/arrow.bmp", 0, "negyzet", 3, 0);

    tutorial = new Object(-0.002, -0.002, 0.0,
                          0, 0, 0,
                          0.00013, 1.0, 0.0001,
                          true, "Letters", 0, "negyzet", 4, 0);

    tutorial2 = new Object(-0.002, -0.0018, 0.0,
                           0, 0, 0,
                           0.00015, 1.0, 0.0001,
                           true, "Letters", 0, "negyzet", 4, 0);

    tutorial3 = new Object(-0.002, -0.0016, 0.0,
                           0, 0, 0,
                           0.00015, 1.0, 0.0001,
                           true, "Letters", 0, "negyzet", 4, 0);

    question = new Object(0.0, 0.0, 0.0,
                          0, 0, 0,
                          0.0015, 1.0, 0.002,
                          true, "Textures/question.bmp", 0, "negyzet", 3, 0);

    /*title = new Object(-0.017, -0.002, -0.027, //koordinatak
                             106, 3, 20, //elforgatas
                             0.0013, 0.0, 0.001, //atmeretezes
                             true, "Letters", 0, "negyzet", 5, 0);*/
    if (level_path[0] == 0)
    {
        editor = false;
        load("Areas/area1.txt", 0);
        load("Areas/area2.txt", 1);
    }

    else
    {
        signal = new Object(0.0, 0.0, -0.06, //koordinatak
                            0, 0, 0, //elforgatas
                            0.01, 0.01, 0.01, //atmeretezes
                            true, "Textures/yellow.bmp", 0, "Objects/frame.obj", 0, 0);

        s1=0;
        s2=0;
        editor = true;
        levelpath = new char [30];
        strcpy(this->levelpath, level_path);

        load(this->levelpath, 0);

        s1=obj_sum[0];
        s2=title_sum[0];
        obj_sum[0]++;
        title_sum[0]++;

        obj_pointer = 2;
        tex_pointer = 2;
        DIR *dir;
        struct dirent *ent;
        dir = opendir ("Objects");
        int i=0;
        while ((ent = readdir (dir)) != NULL)
        {
            strcpy(objpath[i], "Objects/");
            strcat(objpath[i], ent->d_name);
            i++;
        }
        strcpy(objpath[i], "negyzet");
        strcpy(objpath[i+1], "negyzet90");
        i+=2;
        maxobjs = i;

        dir = opendir ("Textures");
        i=0;
        while ((ent = readdir (dir)) != NULL)
        {
            strcpy(texpath[i], "Textures/");
            strcat(texpath[i], ent->d_name);
            i++;
        }

        maxtex = i;
        objects[0][s1] = new Object(0.0, 0.0, -0.06, //koordinatak
                                    0, 0, 0, //elforgatas
                                    0.01, 0.01, 0.01, //atmeretezes
                                    true, texpath[tex_pointer], 0, objpath[obj_pointer], 0, 0);

        titles[0][s2] = new Object(0.0, 0.0, -0.06, //koordinatak
                                   0, 0, 0, //elforgatas
                                   0.01, 0.01, 0.01, //atmeretezes
                                   true, "Letters", 0, "negyzet", 5, 0);
    }

    DIR *dir;
    struct dirent *ent;
    dir = opendir ("Patients");
    int i=-2;
    while ((ent = readdir (dir)) != NULL)
    {
        if (i>-1)
        {
            split(ent->d_name, '.');
            strcpy(patients[i], ent->d_name);
        }
        i++;
    }

    patient_numbers = i;

    select_patient(0, 0);

    FILE * file = fopen("database.txt", "r");
    load_list(file, base_medicines, bmedicine_numbers);
    load_list(file, reported, reported_numbers);
    fclose(file);
}

Laboratory::~Laboratory()
{
    save_patients(patient_ptr);
    if (isModyflied_database)
    {
        FILE * file = fopen("database.txt", "w");
        save_list(file, base_medicines, bmedicine_numbers);
        save_list(file, reported, reported_numbers);
        fclose(file);
    }

    delete [] objects;
    delete [] titles;
    delete arrow;
    if (editor)
        delete signal;


    dealloc(&const_titles, 3);
    dealloc(&chat_title, 9);
    dealloc(&patients, 32);
    dealloc(&basic, 10);
    dealloc(&diabetes, 10);
    dealloc(&blood_pressure, 10);
    dealloc(&blood, 8);
    dealloc(&medicines, 10);
    dealloc(&prev_illnes, 10);
    dealloc(&chron_illnes, 10);
    dealloc(&allergic, 10);
    dealloc(&base_medicines, 32);
    dealloc(&reported, 10);
    dealloc(&private_descreption, 10);
}

void Laboratory::malloc(char *** destination, int x, int y)
{
    (*destination) = new char* [x];
    for (int i=0; i<x; i++)
    {
        (*destination)[i] = new char [y];
        (*destination)[i][0] = 0;
    }

}

void Laboratory::dealloc(char *** destination, int x)
{
    for (int i=0; i<x; i++)
        delete [] (*destination)[i];
    delete [] *destination;
    *destination=0;
}

void Laboratory::load(char * path, const int & index)
{
    FILE * file = fopen(path, "r");

    int i=0;
    int j=0;
    float tx;
    float ty;
    float tz;
    float sx;
    float sy;
    float sz;
    char texture[64];
    char obj[32];
    int rx;
    int ry;
    int rz;
    int appear;
    int textype;

    while(!feof(file))
    {
        fscanf(file, "%s %s %f %f %f %f %f %f %d %d %d %d %d", obj, texture, &tx, &ty, &tz, &sx, &sy, &sz, &rx, &ry, &rz, &appear, &textype);
        if (obj[0] != '-' || obj[1] != '-')
        {
            if (appear == 4 || appear == 5)
            {
                titles[index][j] = new Object(tx, ty, tz, //koordinatak
                                              rx, ry, rz, //elforgatas
                                              sx, sy, sz, //atmeretezes
                                              true, texture, 0, obj, appear, 0);

                j++;
            }
            else
            {
                objects[index][i] = new Object(tx, ty, tz, //koordinatak
                                               rx, ry, rz, //elforgatas
                                               sx, sy, sz, //atmeretezes
                                               true, texture, textype, obj, appear, 0);
                i++;
            }
        }



    }

    fclose(file);

    obj_sum[index] = i;
    title_sum[index] = j;

    if (index == 0)
    {
        file = fopen("Areas/tabs.txt", "r");

        i=0;
        while(!feof(file))
        {
            fscanf(file, "%s %s %f %f %f %f %f %f %d %d %d %d %d", obj, texture, &tx, &ty, &tz, &sx, &sy, &sz, &rx, &ry, &rz, &appear, &textype);
            tabs[i] = new Object(tx, ty, tz, //koordinatak
                                 rx, ry, rz, //elforgatas
                                 sx, sy, sz, //atmeretezes
                                 true, texture, textype, obj, appear, 0);
            i++;
        }

        fclose(file);
    }

}

void Laboratory::save()
{
    FILE * file = fopen(levelpath, "w");

    for (int i=0; i<obj_sum[0]-1; i++)
    {
        fprintf(file, "%s %s %f %f %f %f %f %f %d %d %d %d %d", objects[0][i]->getObjname(), objects[0][i]->getTexture(), objects[0][i]->gettx(),  objects[0][i]->getty(), objects[0][i]->gettz(), objects[0][i]->getsx(), objects[0][i]->getsy(), objects[0][i]->getsz(), objects[0][i]->getrx(), objects[0][i]->getry(), objects[0][i]->getrz(), objects[0][i]->getAppear(), objects[0][i]->getMozaik());
        if (i<obj_sum[0]-2 || title_sum[0] > 1)
            fprintf(file, "\n");
    }

    for (int i=0; i<title_sum[0]-1; i++)
    {
        fprintf(file, "%s %s %f %f %f %f %f %f %d %d %d %d %d", titles[0][i]->getObjname(), titles[0][i]->getTexture(), titles[0][i]->gettx(),  titles[0][i]->getty(), titles[0][i]->gettz(), titles[0][i]->getsx(), titles[0][i]->getsy(), titles[0][i]->getsz(), titles[0][i]->getrx(), titles[0][i]->getry(), titles[0][i]->getrz(), titles[0][i]->getAppear(), objects[0][i]->getMozaik());
        if (i<title_sum[0]-2)
            fprintf(file, "\n");
    }

    fclose(file);
}

void Laboratory::reload_object()
{
    float tx = objects[0][s1]->gettx();
    float ty = objects[0][s1]->getty();
    float tz = objects[0][s1]->gettz();
    float sx = objects[0][s1]->getsx();
    float sy = objects[0][s1]->getsy();
    float sz = objects[0][s1]->getsz();
    float r = objects[0][s1]->getry();
    delete objects[0][s1];

    /*if (isText)
        titles[s2] = new Object(tx, ty, tz, //koordinatak
                            0, r, 0, //elforgatas
                            sx, sy, sz, //atmeretezes
                            true, "Letters", 0, "negyzet", 5, 0);
    else*/
    objects[0][s1] = new Object(tx, ty, tz, //koordinatak
                                0, r, 0, //elforgatas
                                sx, sy, sz, //atmeretezes
                                true, texpath[tex_pointer], 0, objpath[obj_pointer], 0, 0);
}

void Laboratory::esemenyek(int & area)
{
    if (Object::getcz() != cameraZ)
    {
        if (cameraZ > Object::getcz() - 0.002 && cameraZ < Object::getcz() + 0.002)
            Object::setcz(cameraZ);
        else if (cameraZ >= Object::getcz())
            Object::cVertical(0.001);
        else if (cameraZ <= Object::getcz())
            Object::cVertical(-0.001);
    }

    if (Object::getcy() != cameraY)
    {
        if (cameraY > Object::getcy() - 0.002 && cameraY < Object::getcy() + 0.002)
            Object::setcy(cameraY);
        else if (cameraY >= Object::getcy())
            Object::cLenghtical(0.001);
        else if (cameraY <= Object::getcy())
            Object::cLenghtical(-0.001);
    }

    if (Object::getcx() != cameraX)
    {
        if (cameraX > Object::getcx() - 0.002 && cameraX < Object::getcx() + 0.002)
            Object::setcx(cameraX);
        else if (cameraX >= Object::getcx())
            Object::cHorizontal(0.001);
        else if (cameraX <= Object::getcx())
            Object::cHorizontal(-0.001);
    }

    if (area == 9)
    {
        if (point_arrow->gettx() > -0.001)
        {
            point_arrow->trans_horizontal(-0.000014);
            point_arrow->trans_lengthical(-0.000007);
        }
        else
        {
            area = 1;
            area_selected = 1;
        }
    }
    else if (area == 10)
    {
        if (point_arrow->gettx() < 0.00012)
        {
            point_arrow->trans_horizontal(0.000014);
            point_arrow->trans_lengthical(0.000007);
        }
        else
        {
            area = 1;
            area_selected = 0;
        }
    }


}

void Laboratory::key_n()
{
    if (editor)
    {
        if (isModify)
        {
            isModify = false;
            s1=obj_sum[0]-1;
            s2=title_sum[0]-1;
        }
        else
        {
            isModify = true;
            s1=0;
            s2=0;
            *signal= *(objects)[0][s1];
        }
    }
}

void Laboratory::key_y()
{
    if (editor)
    {
        if (isText)
        {
            s2--;
            if (s2<0)
                s2=title_sum[0]-2;
        }
        else
        {
            s1--;
            if (s1<0)
                s1=obj_sum[0]-2;

            *signal= *(objects)[0][s1];
        }
    }
}

void Laboratory::key_x()
{
    if (editor)
    {
        if (isText)
        {
            s2++;
            if (s2>title_sum[0]-2)
                s2=0;
        }
        else
        {
            s1++;
            if (s1>obj_sum[0]-2)
                s1=0;

            *signal= *(objects)[0][s1];
        }
    }
}

void Laboratory::key_text()
{
    if (editor)
    {
        if (!isText)
            isText = true;
        else
            isText = false;

        //reload_object();
    }

}

void Laboratory::shift_keyQ()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateZ(1);
        else
            objects[0][s1]->rotateZ(1);
        //set_height();
    }

}

void Laboratory::shift_keyE()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateZ(-1);
        else
            objects[0][s1]->rotateZ(-1);
        //set_height();
    }

}

void Laboratory::shift_keyA()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateY(-1);
        else
            objects[0][s1]->rotateY(-1);
        //set_height();
    }

}

void Laboratory::shift_keyD()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateY(1);
        else
            objects[0][s1]->rotateY(1);
        //set_height();
    }

}

void Laboratory::shift_keyW()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateX(-1);
        else
            objects[0][s1]->rotateX(-1);
        //set_height();
    }
}

void Laboratory::shift_keyS()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->rotateX(1);
        else
            objects[0][s1]->rotateX(1);
        //set_height();
    }
}

void Laboratory::keyE(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_lengthical(x);
        else
            objects[0][s1]->trans_lengthical(x);
    }

}

void Laboratory::keyQ(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_lengthical(-x);
        else
            objects[0][s1]->trans_lengthical(-x);
    }

}

void Laboratory::keyW(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_vertical(-x);
        else
            objects[0][s1]->trans_vertical(-x);
        //set_height();
    }

}

void Laboratory::keyS(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_vertical(x);
        else
            objects[0][s1]->trans_vertical(x);
        //set_height();
    }

}

void Laboratory::keyA(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_horizontal(-x);
        else
            objects[0][s1]->trans_horizontal(-x);
        //set_height();
    }

}

void Laboratory::keyD(const float & x)
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->trans_horizontal(x);
        else
            objects[0][s1]->trans_horizontal(x);
        //set_height();
    }

}

void Laboratory::keyUp()
{
    if (editor)
    {
        tex_pointer--;
        if (tex_pointer == 1)
            tex_pointer = maxtex-1;
        reload_object();
    }

}

void Laboratory::keyDown()
{
    if (editor)
    {
        tex_pointer++;
        if (tex_pointer == maxtex)
            tex_pointer = 2;
        reload_object();
    }
}

void Laboratory::keyLeft()
{
    if (editor)
    {
        obj_pointer--;
        if (obj_pointer == 1)
            obj_pointer = maxobjs-1;
        reload_object();
    }

}

void Laboratory::keyRight()
{
    if (editor)
    {
        obj_pointer++;
        if (obj_pointer == maxobjs)
            obj_pointer = 2;
        reload_object();
    }
}

void Laboratory::key_4()
{
    if (editor)
    {
        if (isText)
        {
            if (titles[0][s2]->getsx() > 0.0005)
                titles[0][s2]->setsx(titles[0][s2]->getsx()-0.0005);
        }
        else
        {
            if (objects[0][s1]->getsx() > 0.0005)
                objects[0][s1]->setsx(objects[0][s1]->getsx()-0.0005);
        }
    }
}

void Laboratory::key_6()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->setsx(titles[0][s2]->getsx()+0.0005);
        else
            objects[0][s1]->setsx(objects[0][s1]->getsx()+0.0005);
    }

}

void Laboratory::key_2()
{
    if (editor)
    {
        if (isText)
        {
            if (titles[0][s2]->getsz() > 0.0005)
                titles[0][s2]->setsz(titles[0][s2]->getsz()-0.0005);
        }
        else
        {
            if (objects[0][s1]->getsz() > 0.0005)
                objects[0][s1]->setsz(objects[0][s1]->getsz()-0.0005);
        }

    }

}

void Laboratory::key_8()
{
    if (editor)
    {
        if (isText)
            titles[0][s2]->setsz(titles[0][s2]->getsz()+0.0005);
        else
            objects[0][s1]->setsz(objects[0][s1]->getsz()+0.0005);
    }

}

void Laboratory::key_7()
{
    if (editor && !isText)
    {
        if (objects[0][s1]->getsy() > 0.0005)
        {
            objects[0][s1]->trans_lengthical(-0.0005);
            objects[0][s1]->setsy(objects[0][s1]->getsy()-0.0005);
        }
    }


}

void Laboratory::key_9()
{
    if (editor && !isText)
    {
        objects[0][s1]->trans_lengthical(0.0005);
        objects[0][s1]->setsy(objects[0][s1]->getsy()+0.0005);
    }

}

void Laboratory::key_space()
{
    if (editor && !isModify)
    {
        if (isText)
        {
            s2++;
            title_sum[0]++;

            titles[0][s2] = new Object(titles[0][s2-1]->gettx(), titles[0][s2-1]->getty(), titles[0][s2-1]->gettz(), //koordinatak
                                       0, titles[0][s2-1]->getry(), 0, //elforgatas
                                       titles[0][s2-1]->getsx(), titles[0][s2-1]->getsy(), titles[0][s2-1]->getsz(), //atmeretezes
                                       true, "Letters", 0, "negyzet", 5, 0);
        }
        else
        {
            s1++;
            obj_sum[0]++;

            objects[0][s1] = new Object(objects[0][s1-1]->gettx(), objects[0][s1-1]->getty(), objects[0][s1-1]->gettz(), //koordinatak
                                        0, objects[0][s1-1]->getry(), 0, //elforgatas
                                        objects[0][s1-1]->getsx(), objects[0][s1-1]->getsy(), objects[0][s1-1]->getsz(), //atmeretezes
                                        true, texpath[tex_pointer], 0, objpath[obj_pointer], 0, 0);
        }

    }
}

void Laboratory::megjelenit(int & area)
{
    for (int i=0; i<6; i++)
    {
        if (selected[i] == 0)
            tabs[3*i]->rendering(1);
        else
            tabs[3*i]->rendering(0);

        if (selected[i] == 1)
            tabs[3*i+1]->rendering(1);
        else
            tabs[3*i+1]->rendering(0);

        if ((i!= 0 && i!= 2) || area_selected != 1)
        {
            if (selected[i] == 2)
                tabs[3*i+2]->rendering(1);
            else
                tabs[3*i+2]->rendering(0);
        }
    }

    if (selected[4] == 3)
        tabs[18]->rendering(1);
    else
        tabs[18]->rendering(0);

    if (selected[3] == 3)
        tabs[19]->rendering(1);
    else
        tabs[19]->rendering(0);

    if (selected[0] == 0)
    {
        tabs[20]->rendering(0);
        tabs[27]->rendering(0);
        tabs[28]->rendering(0);
    }
    else if (patient_ptr >= patient_page*7 && patient_ptr < (patient_page+1)*7 && selected[0] == 2)
    {
        if (isEditedPatient)
            tabs[29]->rendering(1);
        else
            tabs[29]->rendering(0);
    }

    else if (selected[0] == 1)
        tabs[35]->rendering(0);

    if (selected[4] == 0)
        tabs[21]->rendering(ekg_state);
    else if (selected[4] == 1)
        tabs[21]->rendering(blood_state+3);

    if (selected[4] == 3)
    {
        tabs[22]->rendering(0);
        tabs[23]->rendering(0);
    }

    int temp = obj_sum[area_selected];
    if (editor && (isText || isModify))
        temp--;

    for (int i=0; i<temp; i++)
        if (i!=37 || area_selected != 1)
            objects[area_selected][i]->rendering(0);

    if (selected[3] == 0)
        tabs[24]->rendering(0);
    else if (selected[3] == 3)
        tabs[24]->rendering(1);
    else if (selected[3] == 2)
        tabs[24]->rendering(2);
    else if (selected[3] == 1)
        tabs[24]->rendering(3);

    if (selected[1] == 0)
        tabs[25]->rendering(0);
    else if (selected[1] == 2)
        tabs[25]->rendering(2);

    if (selected[4] == 2)
        tabs[26]->rendering(0);

    if (descreption_ptr == bmedicine_numbers && selected[2] == 0 || reported_ptr >= reported_page*9 && reported_ptr < (reported_page+1)*9 && selected[2] == 2  || medicin_ptr >= medicin_page*9 && medicin_ptr < (medicin_page+1)*9 && selected[2] == 1)
        tabs[30]->rendering(0);

    if (basic_ptr != -1 && selected[1] == 0 || blood_ptr != -1 && selected[1] == 1  || diabetes_ptr != -1 && selected[1] == 2)
        tabs[31]->rendering(0);

    if (ill_ptr != -1 && selected[5] == 0 || chron_ptr != -1 && selected[5] == 1  || allergic_ptr != -1 && selected[5] == 2)
        tabs[32]->rendering(0);

    if (bloodres_ptr != -1 && selected[4] == 2)
        tabs[33]->rendering(0);

    if (selected[2] == 3)
        tabs[34]->rendering(0);

    if (area == 9 || area == 10)
    {
        point_arrow->rendering(0);
        map1->rendering(0);
    }


    if (editor)
        objects[0][s1]->rendering(0);

    if (isModify && !isText)
        signal->rendering(0);

    temp = title_sum[area_selected];
    if (editor && (!isText || isModify))
        temp--;

    if (editor)
    {
        for (int i=0; i<title_sum[area_selected]; i++)
            if (s2 == i)
                titles[0][i]->gprintf("selected");
            else
                titles[0][i]->gprintf("aaaaaaaaaaaaaa");
    }
    else
    {
        if (selected[0] == 0)
        {
            for (int i=0; i<8; i++)
                titles[area_selected][i]->gprintf(chat_title[i]);
        }
        else if (selected[0] == 2)
        {
            for (int i=0; i<7; i++)
                if (patient_page*7+i < patient_numbers)
                    titles[area_selected][i]->gprintf(patients[patient_page*7+i]);
                else if (patient_page*7+i == patient_numbers)
                    titles[area_selected][i]->gprintf("new");
        }

        for (int i=9; i<17; i++)
        {
            if (selected[1] == 0)
            {
                if (i!=basic_ptr+9)
                    titles[area_selected][i]->gprintf(basic[i-9]);
                else
                    titles[area_selected][i]->gprintf(editing_string);
            }
            else if (selected[1] == 1)
            {
                if (i < 9+blood_numbers)
                    titles[area_selected][i]->gprintf(blood_pressure[i-9]);
                else if (i == 9+blood_numbers)
                    titles[area_selected][i]->gprintf("new");

            }
            else
            {
                if (i < 9+diabetes_numbers)
                    titles[area_selected][i]->gprintf(diabetes[i-9]);
                else if (i == 9+diabetes_numbers)
                    titles[area_selected][i]->gprintf("new");
            }

        }

        for (int i=18; i<21; i++)
            if (i!=19 || area_selected != 1)
                titles[area_selected][i]->gprintf(const_titles[i-18]);

        for (int i=21; i<29; i++)
            if (selected[4] == 2)
            {
                if (i != bloodres_ptr+21)
                    titles[area_selected][i]->gprintf(blood[i-21]);
                else
                    titles[area_selected][i]->gprintf(editing_string);
            }

        for (int i=29; i<38; i++)
            if (selected[5] == 0 && prev_illnes[i-29][0] != '*')
            {
                if (i < 29+ill_numbers)
                    titles[area_selected][i]->gprintf(prev_illnes[i-29]);
                if (area_selected == 0 && ill_numbers < 10)
                    titles[area_selected][29+ill_numbers]->gprintf("new");
            }
            else if (selected[5] == 1)
            {
                if (i < 29+chron_numbers)
                    titles[area_selected][i]->gprintf(chron_illnes[i-29]);
                if (area_selected == 0 && chron_numbers < 10)
                    titles[area_selected][29+chron_numbers]->gprintf("new");
            }
            else if (allergic[i-29][0] != '*')
            {
                if (i < 29+allergic_numbers)
                    titles[area_selected][i]->gprintf(allergic[i-29]);
                if (area_selected == 0 && allergic_numbers < 10)
                    titles[area_selected][29+allergic_numbers]->gprintf("new");
            }


        if (selected[0] == 2 && patient_numbers > 6)
        {
            if ((patient_page+1)*7 <= patient_numbers)
                tabs[38]->rendering(0);
            if (patient_page > 0)
                tabs[39]->rendering(0);
            char page_tile[8];
            sprintf(page_tile, "page %d", patient_page+1);
            titles[area_selected][7]->gprintf(page_tile);
        }

        if (selected[2] == 0 || selected[2] == 1 || selected[2] == 2)
        {
            for (int i=38; i<47; i++)
                if (selected[2] == 0 /*&& base_medicines[i-38][0] != '*'*/)
                {
                    if (area_selected == 0 && (((descreption_page+1)*9 <= bmedicine_numbers && i < 47) || (i < 38+(bmedicine_numbers%9))))
                        titles[area_selected][i]->gprintf(base_medicines[descreption_page*9+(i-38)]);
                    else if (i < 38+private_number)
                        titles[area_selected][i]->gprintf(private_descreption[i-38]);
                }
                else if (selected[2] == 1 && (((medicin_page+1)*9 <= medicin_numbers && i < 47) || (i < 38+(medicin_numbers%9))))
                    titles[area_selected][i]->gprintf(medicines[medicin_page*9+(i-38)]);
                else if (selected[2] == 2 && (((reported_page+1)*9 <= reported_numbers && i < 47) || (i < 38+(reported_numbers%9))))
                    titles[area_selected][i]->gprintf(reported[reported_page*9+(i-38)]);

            if (selected[2] == 0)
            {
                if (area_selected == 0 && descreption_page*9 <= bmedicine_numbers)
                    titles[area_selected][38+bmedicine_numbers%9]->gprintf("new");
                if (bmedicine_numbers > 9)
                {
                    if ((descreption_page+1)*9 <= bmedicine_numbers)
                        tabs[36]->rendering(0);
                    if (descreption_page > 0)
                        tabs[37]->rendering(0);
                    char page_tile[8];
                    sprintf(page_tile, "page %d", descreption_page+1);
                    titles[area_selected][47]->gprintf(page_tile);
                }
            }
            else if (selected[2] == 1)
            {
                if (area_selected == 0 && medicin_page*9 <= medicin_numbers)
                    titles[area_selected][38+medicin_numbers%9]->gprintf("new");
                if (medicin_numbers >= 9)
                {
                    if ((medicin_page+1)*9 <= medicin_numbers)
                        tabs[36]->rendering(0);
                    if (medicin_page > 0)
                        tabs[37]->rendering(0);
                    char page_tile[8];
                    sprintf(page_tile, "page %d", medicin_page+1);
                    titles[area_selected][47]->gprintf(page_tile);
                }
            }
            else if (selected[2] == 2)
            {
                if (area_selected == 0 && reported_page*9 <= reported_numbers)
                    titles[area_selected][38+reported_numbers%9]->gprintf("new");
                if (reported_numbers >= 9)
                {
                    if ((reported_page+1)*9 <= reported_numbers)
                        tabs[36]->rendering(0);
                    if (reported_page > 0)
                        tabs[37]->rendering(0);
                    char page_tile[8];
                    sprintf(page_tile, "page %d", reported_page+1);
                    titles[area_selected][47]->gprintf(page_tile);
                }
            }
        }
        else if (selected[2] == 3)
        {
            titles[area_selected][38]->gprintf("dr james wolf");
            titles[area_selected][40]->gprintf(patients[patient_ptr]);
            if (area_selected == 0)
            {
                tabs[30]->rendering(0);
                titles[area_selected][43]->gprintf(base_medicines[descreption_ptr]);
                titles[area_selected][46]->gprintf("send");
            }
            else
                titles[area_selected][43]->gprintf(private_descreption[private_ptr]);

            /*titles[area_selected][6]
            titles[area_selected][7]*/
        }

    }

    if (area > 1 && area < 8)
        arrow->rendering(0);

    if (isDeleting)
        question->rendering(0);

    if (enableTutorial) //tutorial appiarance
        switch(tutorial_ptr)
        {

        case 0:
        {
            tutorial3->gprintf("click to a display to manage it");
            tutorial2->gprintf("or press shift to switch area");
            tutorial->gprintf("or press esc to quit");
            break;
        }
        case 1:
        {
            tutorial2->gprintf("press enter to accept");
            tutorial->gprintf("or press ctrl del to delete");
            break;
        }
        case 2:
        {
            if (area_selected == 0)
                tutorial->gprintf("click to an item to edit it");
            break;
        }
        case 3:
        {
            tutorial->gprintf("press enter to accept");
            break;
        }
        case 4:
        {
            tutorial->gprintf("click to an item to select it");
            break;
        }
        case 5:
        {
            tutorial->gprintf("write a message");
            break;
        }
        case 6:
        {
            tutorial->gprintf("it demonstrate internet service");
            break;
        }
        case 7:
        {
            tutorial2->gprintf("click to send button to send it");
            tutorial->gprintf("or click a tab to return");
            break;
        }
        case 8:
        {

            tutorial3->gprintf("after writing the patients name");
            tutorial2->gprintf("click to the next line and add a date");
            tutorial->gprintf("finaly press enter to accept");
            break;
        }
        case 9:
        {
            tutorial->gprintf("now all data changed in the other displays");
            break;
        }
        case 10:
        {
            tutorial2->gprintf("this is a sended priscription");
            tutorial->gprintf("click a tab to return");
            break;
        }

        }

}

void Laboratory::view_up(const int & x)
{
    Object::cfel(x);
}

void Laboratory::view_down(const int & x)
{
    Object::cle(x);
}

void Laboratory::view_left(const int & x)
{
    Object::cbalra(x);
}


void Laboratory::view_right(const int & x)
{
    Object::cjobbra(x);
}

void Laboratory::click(int & area, const int & x, const int & y)
{
    int width = *s_height * 1.5;
    width += (*s_width - width) / 2;

    if (!isDeleting)
    {
        if (area == 1)
        {
            if ((Object::get_rCameraX() < 15 || Object::get_rCameraX() > 350) && (Object::get_rCameraY() > 350 || Object::get_rCameraY() < 10))
            {
                //kozepso fo monitor
                area = 2;
                cameraX = 0.00;
                cameraZ = 0.0175;
                cameraY = 0.00;
                Object::set_rCameraX(3);
                Object::set_rCameraY(0);

                if (enableTutorial)
                {
                    if (selected[0] == 0)
                        tutorial_ptr = 5;
                    else if (selected[0] == 2)
                        tutorial_ptr = 4;
                    else if (selected[0] == 1)
                        tutorial_ptr = 6;
                }

            }
            else if ((Object::get_rCameraX() < 15 || Object::get_rCameraX() > 350) && (Object::get_rCameraY() < 350 && Object::get_rCameraY() > 320))
            {
                //kozepso nagy
                area = 3;
                cameraX = -0.0005;
                cameraZ = 0.014;
                cameraY = -0.0085;
                Object::set_rCameraX(0);
                Object::set_rCameraY(-15);

                if (enableTutorial)
                {
                    if (selected[4] == 2 && area_selected == 0)
                        tutorial_ptr = 2;
                    else
                        tutorial_ptr = -1;
                }
            }
            else if ((Object::get_rCameraX() < 350 && Object::get_rCameraX() > 320) && (Object::get_rCameraY() < 350 && Object::get_rCameraY() > 330))
            {
                //bal felso
                area = 4;
                cameraX = 0.0095;
                cameraZ = 0.014;
                cameraY = -0.0104;
                Object::set_rCameraX(-25);
                Object::set_rCameraY(-12);

                if (enableTutorial)
                    tutorial_ptr = -1;
            }
            else if ((Object::get_rCameraX() < 350 && Object::get_rCameraX() > 320) && (Object::get_rCameraY() > 350 || Object::get_rCameraY() < 10))
            {
                //bal also
                area = 5;
                cameraX = 0.0065;
                cameraY = 0.0;
                cameraZ = 0.015;
                Object::set_rCameraX(-30);
                Object::set_rCameraY(-2);

                if (enableTutorial)
                {
                    if (selected[2] == 0)
                        tutorial_ptr = 4;
                    else
                    {
                        if (area_selected == 0)
                            tutorial_ptr = 2;
                        else
                            tutorial_ptr = -1;
                    }
                }
            }
            else if (Object::get_rCameraX() < 40 && (Object::get_rCameraY() > 350 || Object::get_rCameraY() < 10))
            {
                //jobb also
                area = 6;
                cameraY = 0.0;
                cameraX = -0.0083;
                cameraZ = 0.015;
                Object::set_rCameraX(30);
                Object::set_rCameraY(-2);

                if (enableTutorial)
                {
                    if (area_selected == 0)
                        tutorial_ptr = 2;
                    else
                        tutorial_ptr = -1;
                }

            }
            else if (Object::get_rCameraX() < 50 && Object::get_rCameraY() > 320 && Object::get_rCameraY() < 350)
            {
                //jobb felso
                area = 7;
                cameraY = -0.008;
                cameraX = -0.0095;
                cameraZ = 0.014;
                Object::set_rCameraX(30);
                Object::set_rCameraY(-20);

                if (enableTutorial)
                {
                    if (area_selected == 0)
                        tutorial_ptr = 2;
                    else
                        tutorial_ptr = -1;
                }
            }
        }


        if (area > 1 && x < 100/800.0* width && y > 500/600.0*(*s_height)) //nezo mod
            back_to_view();

        if (Object::getcz() > 0.01)
        {
            if (area == 2) //kozepso fo monitor
            {
                if (y < 100/600.0*(*s_height))
                {
                    writing(1);
                    if (x > 60/800.0* width && x < 250/800.0* width)
                    {
                        selected[0] = 0;
                        if (enableTutorial)
                            tutorial_ptr = 5;
                    }
                    else if (area_selected == 0 && x > 300/800.0* width && x < 550/800.0* width)
                    {
                        selected[0] = 2;
                        if (enableTutorial)
                            tutorial_ptr = 4;
                    }

                    else if (x > 550/800.0* width && x < 700/800.0* width)
                    {
                        selected[0] = 1;
                        if (enableTutorial)
                            tutorial_ptr = 6;
                        if (browser_path[0] != '0')
                        {
                            HINSTANCE result = ShellExecute(NULL, "open", browser_path, NULL, NULL, SW_SHOWDEFAULT);
                            if ((int)result < 33)
                                MessageBoxA(NULL, "Cannot open the specified program!", "An error occoured!", MB_OK);
                        }
                    }
                }
                else if (selected[0] == 2 && y > 150/600.0*(*s_height) && y < 500/600.0*(*s_height))
                {
                    if (enableTutorial)
                        tutorial_ptr = 9;
                    int temp = patient_ptr;
                    patient_ptr = patient_page*7 + ((int)(-150/600.0*(*s_height))+y)/(int)(50/600.0*(*s_height));
                    if (patient_ptr == patient_numbers)
                    {
                        save_patients(temp);
                        patient_numbers++;
                        isEditedPatient = true;
                    }
                    else
                        select_patient(patient_ptr, temp);
                    tabs[29]->setty((((int)(-150/600.0*(*s_height))+y)/(int)(50/600.0*(*s_height)))*(-0.00075)+0.00196);
                }
                else if (y > 550/600.0*(*s_height) && y < 600/600.0*(*s_height) && x > 350/800.0*width &&  x < 500/800.0*width && selected[0] == 2 && (patient_page+1)*7 <= patient_numbers && patient_numbers >= 7)
                    patient_page++;
                else if (y > 100/600.0*(*s_height) && y < 150/600.0*(*s_height) && x > 350/800.0*width &&  x < 500/800.0*width && selected[0] == 2 && patient_page > 0 && patient_numbers >= 7)
                    patient_page--;
            }
            else if (area == 3) //kozepso nagy
            {
                if (y < 140/600.0*(*s_height))
                {
                    writing(1);
                    if (x > 40/800.0* width && x < 250/800.0* width)
                        selected[4] = 0;
                    else if (x > 250/800.0* width && x < 410/800.0* width)
                        selected[4] = 1;
                    else if (x > 410/800.0* width && x < 560/800.0* width)
                        selected[4] = 2;
                    else if (x > 560/800.0* width)
                        selected[4] = 3;

                    if (enableTutorial && area_selected == 0)
                    {
                        if (selected[4] == 2)
                            tutorial_ptr = 2;
                        else
                            tutorial_ptr = -1;
                    }

                }
                else if (area_selected == 0 && y < 480/600.0*(*s_height) && selected[4] == 2)
                {
                    if (enableTutorial)
                        tutorial_ptr = 3;
                    if (bloodres_ptr != -1)
                    {
                        strcat(blood[bloodres_ptr], "_");
                        strcat(blood[bloodres_ptr], editing_string);
                        strcat(blood[bloodres_ptr], "_");
                        strcat(blood[bloodres_ptr], si);
                    }

                    bloodres_ptr = (int)(-3.0/600.0*(*s_height))+y/(int)(44/600.0*(*s_height));
                    split(blood[bloodres_ptr], editing_string, si, '_');

                    tabs[33]->setty((((int)(-3.0/600.0*(*s_height))+y)/(int)(44/600.0*(*s_height)))*(-0.00082)+0.0175);
                    tabs[33]->settz((((int)(-3.0/600.0*(*s_height))+y)/(int)(44/600.0*(*s_height)))*(-0.000015)-0.027672);
                }
            }
            else if (area == 4 && y < 150/600.0*(*s_height)) //bal felso
            {
                if (x > 40/800.0* width && x < 250/800.0* width)
                    selected[3] = 0;
                else if (x > 250/800.0* width && x < 410/800.0* width)
                    selected[3] = 3;
                else if (x > 410/800.0* width && x < 560/800.0* width)
                    selected[3] = 2;
                else if (x > 560/800.0* width)
                    selected[3] = 1;
            }
            else if (area == 5) //bal also
            {
                if (y < 75/600.0*(*s_height)) //tab select
                {
                    writing(1);
                    if (x > 50/800.0* width && x < 280/800.0* width)
                        selected[2] = 0;
                    else if (area_selected == 0 && x > 250/800.0* width && x < 480/800.0* width)
                        selected[2] = 2;
                    else if (x > 480/800.0* width && x < 700/800.0* width)
                        selected[2] = 1;

                    if (enableTutorial)
                    {
                        if (selected[2] == 0)
                            tutorial_ptr = 4;
                        else if (area_selected == 0)
                            tutorial_ptr = 2;
                    }

                }
                else if (y > 120/600.0*(*s_height) && y < 530/600.0*(*s_height)) //functions
                {
                    if (selected[2] == 0)
                    {
                        if (area_selected == 0)
                        {
                            descreption_ptr = descreption_page*9 + (int)(-2.0/600.0*(*s_height))+y/(int)(46/600.0*(*s_height));
                            if (enableTutorial)
                            {
                                if (descreption_ptr == bmedicine_numbers)
                                    tutorial_ptr = 3;
                                else
                                    tutorial_ptr = 7;
                            }
                        }
                        else
                        {
                            private_ptr = (int)(-2.0/600.0*(*s_height))+y/(int)(44/600.0*(*s_height));
                            if (enableTutorial)
                                tutorial_ptr = 10;
                        }

                        if (area_selected == 0 && descreption_ptr == bmedicine_numbers)
                        {
                            base_medicines[bmedicine_numbers][0] = 0;
                            bmedicine_numbers++;
                        }
                        else
                        {
                            selected[2] = 3;
                            tabs[30]->setty(-0.003);
                        }
                    }
                    else if (area_selected == 0 && selected[2] == 2)
                    {
                        if (enableTutorial)
                            tutorial_ptr = 8;
                        reported_ptr = reported_page*9 + (int)(-2.0/600.0*(*s_height))+y/(int)(46/600.0*(*s_height));
                        if (reported_ptr == reported_numbers)
                        {
                            reported_numbers+=2;
                            reported[reported_ptr][0] = 0;
                            reported[reported_ptr+1][0] = 0;
                        }
                    }
                    else if (area_selected == 0 && selected[2] == 1)
                    {
                        if (enableTutorial)
                            tutorial_ptr = 1;
                        medicin_ptr = medicin_page*9 + (int)(-2.0/600.0*(*s_height))+y/(int)(46/600.0*(*s_height));
                        if (medicin_ptr == medicin_numbers)
                        {
                            medicin_numbers++;
                            medicines[medicin_ptr][0] = 0;
                        }
                    }
                    else if (area_selected == 0 && selected[2] == 3 && x < (int)200/800.0*width && y > (int)465/600.0*(*s_height) && y < (int)525/600.0*(*s_height))
                    {
                        if (enableTutorial)
                            tutorial_ptr = 1;
                        strcpy(private_descreption[private_number], base_medicines[descreption_ptr]);
                        private_number++;
                        selected[2] = 0;
                    }

                    if (area_selected == 0 && selected[2] != 3)
                        tabs[30]->setty((((int)(-2.0/600.0*(*s_height))+y)/(int)(46/600.0*(*s_height)))*(-0.0008)+0.0052);
                }
                else if (y > 550/600.0*(*s_height) && x > 320/800.0*width &&  x < 430/800.0*width)
                {
                    if (selected[2] == 0 && (descreption_page+1)*9 <= bmedicine_numbers && bmedicine_numbers >= 9)
                        descreption_page++;
                    else if (selected[2] == 2 && (reported_page+1)*9 <= reported_numbers && reported_numbers >=9)
                        reported_page++;
                    else if (selected[2] == 1 && (medicin_page+1)*9 <= medicin_numbers && medicin_numbers >=9)
                        medicin_page++;
                }
                else if (y > 75/600.0*(*s_height) && y < 120/600.0*(*s_height) && x > 320/800.0*width &&  x < 430/800.0*width)
                {
                    if (selected[2] == 0 && descreption_page > 0 && bmedicine_numbers >= 9)
                        descreption_page--;
                    else if (selected[2] == 2 && reported_page > 0 && reported_numbers >=9)
                        reported_page--;
                    else if (selected[2] == 1 && medicin_page > 0 && medicin_numbers >=9)
                        medicin_page--;
                }
            }
            else if (area == 6) //jobb also
            {
                if (y < 120/600.0*(*s_height))
                {

                    writing(1);
                    if (x > 60/800.0* width && x < 300/800.0* width)
                        selected[1] = 0;
                    else if (x > 300/800.0* width && x < 550/800.0* width)
                        selected[1] = 1;
                    else if (x > 550/800.0* width && x < 750/800.0* width)
                        selected[1] = 2;

                    if (enableTutorial && area_selected == 0)
                        tutorial_ptr = 2;
                }
                else if (area_selected == 0 && y > 180/600.0*(*s_height) && y < 530/600.0*(*s_height))
                {
                    if (selected[1] == 0 && y < 435/600.0*(*s_height))
                    {
                        if (enableTutorial && area_selected == 0)
                            tutorial_ptr = 3;
                        if (basic_ptr != -1)
                        {
                            strcat(basic[basic_ptr], "_");
                            strcat(basic[basic_ptr], editing_string);
                            if (basic_ptr == 0 || basic_ptr == 1)
                            {
                                float height;
                                int weight;
                                float bmi;
                                sscanf(basic[0], "height_%f", &height);
                                sscanf(basic[1], "weight_%d", &weight);
                                bmi = weight/((height/100)*(height/100));
                                sprintf(basic[2], "bmi_%f", bmi);
                            }
                            else if (basic_ptr == 2)
                            {
                                float height;
                                int weight;
                                float bmi;
                                sscanf(basic[2], "bmi_%f", &bmi);
                                sscanf(basic[0], "height_%f", &height);
                                weight = bmi * ((height/100)*(height/100));
                                sprintf(basic[1], "weight_%d", weight);
                            }
                        }

                        basic_ptr = (int)(-3.5/600.0*(*s_height))+y/(int)(45/600.0*(*s_height));
                        split(basic[basic_ptr], editing_string, '_');
                    }
                    else if (selected[1] == 1)
                    {
                        if (enableTutorial && area_selected == 0)
                            tutorial_ptr = 1;
                        blood_ptr = (int)(-3.5/600.0*(*s_height))+y/(int)(45/600.0*(*s_height));
                        if (blood_ptr == blood_numbers)
                        {
                            blood_numbers++;
                            blood_pressure[blood_ptr][0] = 0;
                        }
                    }
                    else if (selected[1] == 2)
                    {
                        if (enableTutorial && area_selected == 0)
                            tutorial_ptr = 1;
                        diabetes_ptr = (int)(-3.5/600.0*(*s_height))+y/(int)(45/600.0*(*s_height));
                        if (diabetes_ptr == diabetes_numbers)
                        {
                            diabetes_numbers++;
                            diabetes[diabetes_ptr][0] = 0;
                        }
                    }

                    tabs[31]->setty((((int)(-4.0/600.0*(*s_height))+y)/(int)(45/600.0*(*s_height)))*(-0.00082)+0.0056);
                }
            }
            else if (area == 7)
            {
                //jobb felso
                if (x < 340/800.0* width && y < 115/600.0*(*s_height) || x >= 340/800.0* width && y < 160/600.0*(*s_height))
                {
                    writing(1);
                    if (x > 125/800.0* width && x < 340/800.0* width)
                        selected[5] = 0;
                    else if (x > 340/800.0* width && x < 550/800.0* width)
                        selected[5] = 1;
                    else if (x > 550/800.0* width && x < 740/800.0* width)
                        selected[5] = 2;
                }
                else if ((area_selected == 0 && x < 340/800.0* width && y > 120/600.0*(*s_height) || x >= 340/800.0* width && y > 170/600.0*(*s_height)) && y < 500/600.0*(*s_height))
                {
                    if (enableTutorial && area_selected == 0)
                        tutorial_ptr = 1;
                    if (selected[5] == 0)
                    {
                        ill_ptr = (int)(-2.0/600.0*(*s_height))+y/(int)(47/600.0*(*s_height));
                        if (ill_ptr == ill_numbers)
                        {
                            ill_numbers++;
                            prev_illnes[ill_ptr][0] = 0;
                        }
                    }
                    else if (selected[5] == 1)
                    {
                        chron_ptr = (int)(-2.0/600.0*(*s_height))+y/(int)(47/600.0*(*s_height));
                        if (chron_ptr == chron_numbers)
                        {
                            chron_numbers++;
                            chron_illnes[chron_ptr][0] = 0;
                        }
                    }
                    else if (selected[5] == 2)
                    {
                        allergic_ptr = (int)(-2.0/600.0*(*s_height))+y/(int)(47/600.0*(*s_height));
                        if (allergic_ptr == allergic_numbers)
                        {
                            allergic_numbers++;
                            allergic[allergic_ptr][0] = 0;
                        }
                    }

                    tabs[32]->setty((((int)(-2.0/600.0*(*s_height))+y)/(int)(47/600.0*(*s_height)))*(-0.0007)+0.0165);
                    tabs[32]->settz((((int)(-2.0/600.0*(*s_height))+y)/(int)(48/600.0*(*s_height)))*(-0.000213)-0.02397);
                }
            }
        }

        if (area == 8)
            area = 1;
    }
    else
    {
        if (x > 298.0/800.0* width && x < 396/800.0* width && y > 323/600.0*(*s_height) && y < 366/600.0*(*s_height))
        {
            isDeleting = false;
            delete_item();
        }
        else if (x > 410.0/800.0* width && x < 507.0/800.0* width && y > 323.0/600.0*(*s_height) && y < 366.0/600.0*(*s_height))
            isDeleting = false;
    }
}

void Laboratory::writing(char letter)
{
    if (area == 2)
    {
        if (selected[0] == 0)
            edit_text(chat_title[7], letter);
        else if (isEditedPatient && selected[0] == 2)
            edit_text(patients[patient_ptr], letter);
    }
    else if (area == 3)
    {
        if (selected[4] == 2 && bloodres_ptr != -1)
        {
            edit_text(editing_string, letter);
            isModyflied_patient = true;
            if (enableTutorial && letter == 1)
                tutorial_ptr = 2;
        }
        else if (selected[4] == 0 && letter > '0' && letter < '4')
            ekg_state = letter-49;
        else if (selected[4] == 1 && letter > '0' && letter < '3')
            blood_state = letter-49;

    }
    else if (area == 5)
    {
        if ((selected[2] == 0 || selected[2] == 3) && descreption_ptr != -1 && descreption_ptr < bmedicine_numbers)
        {
            edit_text(base_medicines[descreption_ptr], letter);
            isModyflied_database = true;
        }
        else if (selected[2] == 2 && reported_ptr != -1 && reported_numbers)
        {
            edit_text(reported[reported_ptr], letter);
            isModyflied_database = true;
        }
        else if (selected[2] == 1 && medicin_ptr != -1 && medicin_numbers)
        {
            edit_text(medicines[medicin_ptr], letter);
            isModyflied_patient = true;
        }
        if (enableTutorial && letter == 1)
        {
            if (selected[2] == 0)
                tutorial_ptr = 4;
            else
                tutorial_ptr = 2;
        }


    }
    else if (area == 6)
    {
        if (enableTutorial && letter == 1)
            tutorial_ptr = 2;
        if (selected[1] == 0 && basic_ptr != -1 && basic_ptr < basic_numbers)
        {
            edit_text(editing_string, letter);
            isModyflied_patient = true;

        }
        else if (selected[1] == 1 && blood_ptr != -1 && blood_ptr < blood_numbers)
        {
            edit_text(blood_pressure[blood_ptr], letter);
            isModyflied_patient = true;
        }
        else if (selected[1] == 2 && diabetes_ptr != -1 && diabetes_ptr < diabetes_numbers)
        {
            edit_text(diabetes[diabetes_ptr], letter);
            isModyflied_patient = true;
        }
    }
    else if (area == 7)
    {
        if (enableTutorial && letter == 1)
            tutorial_ptr = 2;
        if (selected[5] == 0 && ill_ptr != -1 && ill_ptr < ill_numbers)
        {
            edit_text(prev_illnes[ill_ptr], letter);
            isModyflied_patient = true;
        }
        else if (selected[5] == 1 && chron_ptr != -1 && chron_ptr < chron_numbers)
        {
            edit_text(chron_illnes[chron_ptr], letter);
            isModyflied_patient = true;
        }
        else if (selected[5] == 2 && allergic_ptr != -1 && allergic_ptr < allergic_numbers)
        {
            edit_text(allergic[allergic_ptr], letter);
            isModyflied_patient = true;
        }
    }
}

void Laboratory::edit_text(char * title, char & letter)
{
    int len = strlen(title);
    if (letter == 1) //letter is an enter
    {
        if (len > 0)
        {
            if (area == 2)
            {
                if (selected[0] == 0)
                {
                    for (int i=0; i<8; i++)
                        strcpy(chat_title[i], chat_title[i+1]);
                    title[0] = 0;
                }
                else if (selected[0] == 2)
                {
                    strcpy(basic[0], "height_0");
                    strcpy(basic[1], "weight_0");
                    strcpy(basic[2], "bmi_0");
                    strcpy(basic[3], "blood_pressure_0/p0");
                    strcpy(basic[4], "pulse_0");
                    strcpy(basic[5], "bloodsugar_0");
                    blood_pressure[0][0] = '*';
                    diabetes[0][0] = '*';
                    prev_illnes[0][0] = '*';
                    chron_illnes[0][0] = '*';
                    allergic[0][0] = '*';
                    medicines[0][0] = '*';
                    for (int i=1; i<10; i++)
                    {
                        blood_pressure[i][0] = 0;
                        diabetes[i][0] = 0;
                    }
                    for (int i=1; i<9; i++)
                    {
                        prev_illnes[i][0] = 0;
                        chron_illnes[i][0] = 0;
                        allergic[i][0] = 0;
                    }
                    for (int i=1; i<9; i++)
                        medicines[i][0] = 0;

                    ekg_state = 0;
                    blood_state = 0;
                    strcpy(blood[0], "hemoglobin_0_g/pl");
                    strcpy(blood[1], "hematokrit_0.0_%");
                    strcpy(blood[2], "mcv_0_fl");
                    strcpy(blood[3], "mch_0_pg");
                    strcpy(blood[4], "mchc_0_g/pl");
                    strcpy(blood[5], "leukocyte_0.0_g/pl");
                    strcpy(blood[6], "platelet_0_g/pl");
                    blood_numbers = 0;
                    diabetes_numbers = 0;
                    ill_numbers = 0;
                    chron_numbers = 0;
                    allergic_numbers = 0;
                    medicin_numbers = 0;

                    isEditedPatient = false;
                    isModyflied_patient = true;
                    area = 6;
                    selected[1] == 0;
                    cameraY = 0.0;
                    cameraX = -0.0083;
                    cameraZ = 0.015;
                    Object::set_rCameraX(30);
                    Object::set_rCameraY(-2);
                }
            }
            else if (area == 3)
            {
                strcat(blood[bloodres_ptr], "_");
                strcat(blood[bloodres_ptr], editing_string);
                strcat(blood[bloodres_ptr], "_");
                strcat(blood[bloodres_ptr], si);
                bloodres_ptr = -1;
            }
            else if (area == 5)
            {
                if (selected[2] == 1)
                    medicin_ptr = -1;
                else if (selected[2] == 2)
                    reported_ptr = -1;
            }
            else if (area == 6)
            {
                if (selected[1] == 0)
                {
                    strcat(basic[basic_ptr], "_");
                    strcat(basic[basic_ptr], editing_string);
                    if (basic_ptr == 0 || basic_ptr == 1)
                    {
                        float height;
                        int weight;
                        float bmi;
                        sscanf(basic[0], "height_%f", &height);
                        sscanf(basic[1], "weight_%d", &weight);
                        bmi = weight/((height/100)*(height/100));
                        sprintf(basic[2], "bmi_%f", bmi);
                    }
                    else if (basic_ptr == 2)
                    {
                        float height;
                        int weight;
                        float bmi;
                        sscanf(basic[2], "bmi_%f", &bmi);
                        sscanf(basic[0], "height_%f", &height);
                        weight = bmi * ((height/100)*(height/100));
                        sprintf(basic[1], "weight_%d", weight);
                    }
                    basic_ptr = -1;
                }
                else if (selected[1] == 1)
                    blood_ptr = -1;
                else if (selected[1] == 2)
                    diabetes_ptr = -1;
            }
            else if (area == 7)
            {
                if (selected[5] == 0)
                    ill_ptr = -1;
                else if (selected[5] == 1)
                    chron_ptr = -1;
                else if (selected[5] == 2)
                    allergic_ptr = -1;
            }
        }
    }
    else
    {
        if (len > 0 && letter == 0) //backspace
        {
            if (len > 1 && title[len-1] == 'p' && title[len-2] == '/')
                title[len-2] = 0;
            else
                title[len-1] = 0;
        }
        else if (len < 19)
        {
            title[len] = letter;
            title[len+1] = 0;
        }
    }
}

void Laboratory::split(char * c1, char c2)
{
    int i=0;
    while (c1[i] != c2)
        i++;
    c1[i] = 0;
}

void Laboratory::split(char * c1, char * c2, char c3)
{
    int i=0;
    while (c1[i] != c3)
        i++;
    c1[i] = 0;
    i++;
    int j=0;
    while (c1[i] != 0)
    {
        c2[j] = c1[i];
        i++;
        j++;
    }
    c2[j] = 0;

}

void Laboratory::split(char * c1, char * c2, char * c3, char c4)
{
    int i=0;
    while (c1[i] != c4)
        i++;
    c1[i] = 0;
    i++;
    int j=0;
    while (c1[i] != c4)
    {
        c2[j] = c1[i];
        i++;
        j++;
    }
    c2[j] = 0;
    i++;
    j=0;
    while (c1[i] != 0)
    {
        c3[j] = c1[i];
        i++;
        j++;
    }
    c3[j] = 0;

}

void Laboratory::select_patient(int i, int prev_ptr)
{
    if (i >= patient_numbers)
        return;

    char temp[20];
    int j;
    FILE * file;

    if (isModyflied_patient)
        save_patients(prev_ptr);

    strcpy(temp, "Patients/");
    strcat(temp, patients[i]);
    strcat(temp, ".txt");
    file = fopen(temp, "r");
    j=0;
    while(j<6)
    {
        fscanf(file, "%s", basic[j]);
        j++;
    }

    medicin_numbers = 0;

    ill_numbers = 0;
    chron_numbers = 0;
    allergic_numbers = 0;

    blood_numbers = 0;
    diabetes_numbers = 0;

    load_list(file, blood_pressure, blood_numbers);
    load_list(file, diabetes, diabetes_numbers);
    load_list(file, prev_illnes, ill_numbers);
    load_list(file, chron_illnes, chron_numbers);
    load_list(file, allergic, allergic_numbers);
    load_list(file, medicines, medicin_numbers);
    load_list(file, private_descreption, private_number);
    fscanf(file, "%d %d", &ekg_state, &blood_state);
    j=0;
    while(j<8)
    {
        fscanf(file, "%s", blood[j]);
        j++;
    }

    fclose(file);

    for (int i=0; i<8; i++)
        chat_title[i][0] = 0;
}

void Laboratory::save_patients(int prev_ptr)
{
    if (basic_ptr != -1)
    {
        strcat(basic[basic_ptr], "_");
        strcat(basic[basic_ptr],editing_string);
    }
    char temp[20];
    int j;
    FILE * file;

    strcpy(temp, "Patients/");
    strcat(temp, patients[prev_ptr]);
    strcat(temp, ".txt");
    file = fopen(temp, "w");
    j=0;
    while(j<6)
    {
        fprintf(file, "%s\n", basic[j]);
        j++;
    }
    save_list(file, blood_pressure, blood_numbers);
    save_list(file, diabetes, diabetes_numbers);
    save_list(file, prev_illnes, ill_numbers);
    save_list(file, chron_illnes, chron_numbers);
    save_list(file, allergic, allergic_numbers);
    save_list(file, medicines, medicin_numbers);
    save_list(file, private_descreption, private_number);
    fprintf(file, "%d %d\n", ekg_state, blood_state);
    j=0;
    while(j<8)
    {
        fprintf(file, "%s\n", blood[j]);
        j++;
    }

    fclose(file);
    isModyflied_patient = false;
}

void Laboratory::load_list(FILE * file, char ** destination, int & x)
{
    int j=0;
    fscanf(file, "%s", destination[j]);
    while(destination[j][0] != '*' && !feof(file))
    {
        j++;
        fscanf(file, "%s", destination[j]);
    }
    x=j;
}

void Laboratory::save_list(FILE * file, char ** source, int & x)
{
    for (int i=0; i<x; i++)
        fprintf(file, "%s\n", source[i]);
    fprintf(file, "*\n");
}

void Laboratory::zene(char * eleres)
{

}

void Laboratory::zene_stop()
{

}

void Laboratory::reset()
{

}

void Laboratory::sethangok(bool * behang)
{

}

void Laboratory::start()
{

}

void Laboratory::select_area()
{
    if (area == 1)
    {
        selected[2] = 0;
        selected[0] = 0;
        if (area_selected == 0)
        {
            area = 9;
            point_arrow->setrz(30);
            descreption_ptr = -1;
            basic_ptr = -1;
            patient_ptr = 0;
            blood_ptr = -1;
            diabetes_ptr = -1;
            medicin_ptr = -1;
            reported_ptr = -1;
            bloodres_ptr = -1;
            ill_ptr = -1;
            chron_ptr = -1;
            allergic_ptr = -1;
            private_ptr = -1;
        }
        else
        {
            area = 10;
            point_arrow->setrz(210);
        }
    }


}

void Laboratory::unlock_cursor()
{
    if (area == 1)
        area = 8;
}

void Laboratory::deleting(char ** data, int & ptr, int & number)
{
    if (number > 1)
    {
        for (int i=ptr; i<number-1; i++)
            strcpy(data[i], data[i+1]);
        data[number-1][0] = 0;
    }
    else
        data[0][0] = 0;
    number--;
    ptr = -1;
}

void Laboratory::delete_item()
{
    if (enableTutorial)
        tutorial_ptr = 2;
    if (area == 6)
    {
        if (selected[1] == 1 && blood_ptr != -1 && blood_numbers)
        {
            deleting(blood_pressure, blood_ptr, blood_numbers);
            isModyflied_patient = true;
        }
        else if (selected[1] == 2 && diabetes_ptr != -1 && diabetes_numbers)
        {
            deleting(diabetes, diabetes_ptr, diabetes_numbers);
            isModyflied_patient = true;
        }
    }
    else if (area == 5)
    {
        if ((selected[2] == 0 || selected[2] == 3) && descreption_ptr != -1 && descreption_ptr < bmedicine_numbers)
        {
            deleting(base_medicines, descreption_ptr, bmedicine_numbers);
            isModyflied_database = true;
            selected[2] = 0;
        }
        else if (selected[2] == 2 && reported_ptr != -1 && reported_numbers)
        {
            deleting(reported, reported_ptr, reported_numbers);
            isModyflied_database = true;
        }
        else if (selected[2] == 1 && medicin_ptr != -1 && medicin_numbers)
        {
            deleting(medicines, medicin_ptr, medicin_numbers);
            isModyflied_patient = true;
        }
    }
    else if (area == 7)
    {
        if (selected[5] == 0 && ill_ptr != -1 && ill_ptr < ill_numbers)
            deleting(prev_illnes, ill_ptr, ill_numbers);
        else if (selected[5] == 1 && chron_ptr != -1 && chron_ptr < chron_numbers)
            deleting(chron_illnes, chron_ptr, chron_numbers);
        else if (selected[5] == 2 && allergic_ptr != -1 && allergic_ptr < allergic_numbers)
            deleting(allergic, allergic_ptr, allergic_numbers);
        isModyflied_patient = true;
    }
}

void Laboratory::back_to_view()
{
    writing(1);
    area = 1;
    cameraZ = 0.0;
    cameraY = 0.0;
    cameraX = 0.0;
    Object::set_rCameraX(0);
    Object::set_rCameraY(0);
    SDL_WarpMouse(400, 300);

    if (enableTutorial)
        tutorial_ptr = 0;
}

void Laboratory::set_Deleting(const bool & x)
{
    if (area > 1)
        isDeleting = x;
}
