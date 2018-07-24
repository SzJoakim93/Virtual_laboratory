#include "Object.h"
#include "Object.h"

float Object::cx = 0;
float Object::cy = 0;
float Object::cz = 0;
int Object::rCameraX = 0;
int Object::rCameraY = 0;
float Object::txcamera = 0;
float Object::tycamera = 0;
float Object::tzcamera = 0;

list<object> Object::global_mesh;
char_list Object::global_mesh_path;

list<Texture> Object::global_texture;
char_list Object::global_texture_path;

const float Object::cube_vertices[2][18] = {
                                    {    -0.5, 0, -0.5,
                                        0.5, 0, 0.5,
                                        0.5, 0, -0.5,

                                        -0.5, 0, -0.5,
                                        -0.5, 0, 0.5,
                                        0.5, 0, 0.5
                                    } ,

                                    {
                                        -0.5, 0.5, 0,
                                        0.5, -0.5, 0,
                                        -0.5, -0.5, 0,

                                        -0.5, 0.5, 0,
                                        0.5, 0.5, 0,
                                        0.5, -0.5, 0
                                    }
                              };

const float Object::cube_normals[2][18] = {
                                    {    -0.5, -0.5, 0,
                                        0.5, 0.5, 0,
                                        0.5, -0.5, 0,

                                        -0.5, -0.5, 0,
                                        -0.5, 0.5, 0,
                                        0.5, 0.5, 0
                                    } ,

                                    {
                                        -0.5, 0, 0,
                                        0.5, 0, 0,
                                        -0.5, 0, 0,

                                        -0.5, 0, 0,
                                        0.5, 0, 0,
                                        0.5, 0, 0
                                    }
                              };
Object::Object(float betx, float bety, float betz, int berx, int bery, int berz, float besx, float besy, float besz, bool fenyek, char* betexture, int bemozaik, char* beobjname, int beapp, int beflag)
{
    //ctor
    this->tx = betx;
    this->ty = bety;
    this->tz = betz;
    this->rx = berx;
    this->ry = bery;
    this->rz = berz;
    this->sx = besx;
    this->sy = besy;
    this->sz = besz;
    this->rabsolute = 0;
    this->appear = beapp;
    this->mozaik = bemozaik;
    this->gravity_range = 0.0;
    this->fenyek = fenyek;
    strcpy(texname, betexture);
    strcpy(objname, beobjname);

    /**loading texture(s)**/
    //checking, that this texture has been already loaded
    bool isExistTexture=false;
    list<Texture>::Iterator j=global_texture.begin();
    for (char_list::Iterator i=global_texture_path.begin(); i!=global_texture_path.end() && !isExistTexture; i++)
    {
        if (!strcmp(texname, *i))
        {
            isExistTexture = true;
            textureid = j;
            texPathIt = i;
            (*textureid).tex_numbers++;
        }

        j++;
    }

    //if texture not be loaded, it will be loaded
    Texture new_textureid;
    if (!isExistTexture && (appear == 4 || appear == 5))
    {
        char temp[32];
        new_textureid.texture = new GLuint[50];
        new_textureid.tex_num_per_obj = 50;
        glGenTextures(48, new_textureid.texture);
        for (int i=0; i<26; i++)
        {
            strcpy(temp, texname);
            strcat(temp, "/");
            char temp2[2] = {'A'+i, 0};
            strcat(temp, temp2);
            strcat(temp, ".bmp");
            eLoadBMPTexture(temp, new_textureid.texture[i]);
        }

        for (int i=0; i<10; i++)
        {
            strcpy(temp, texname);
            strcat(temp, "/");
            char temp2[2]= {'0'+i, 0};
            strcat(temp, temp2);
            strcat(temp, ".bmp");
            eLoadBMPTexture(temp, new_textureid.texture[26+i]);
        }

        for (int i=0; i<9; i++)
        {
            strcpy(temp, texname);
            strcat(temp, "/_");
            char temp2[2]= {'0'+i, 0};
            strcat(temp, temp2);
            strcat(temp, ".bmp");
            eLoadBMPTexture(temp, new_textureid.texture[36+i]);
        }

        strcpy(temp, texname);
        strcat(temp, "/per.bmp");
        eLoadBMPTexture(temp, new_textureid.texture[45]);

        strcpy(temp, texname);
        strcat(temp, "/point.bmp");
        eLoadBMPTexture(temp, new_textureid.texture[46]);

        strcpy(temp, texname);
        strcat(temp, "/question.bmp");
        eLoadBMPTexture(temp, new_textureid.texture[47]);

        strcpy(temp, texname);
        strcat(temp, "/percent.bmp");
        eLoadBMPTexture(temp, new_textureid.texture[48]);

        strcpy(temp, texname);
        strcat(temp, "/comma.bmp");
        eLoadBMPTexture(temp, new_textureid.texture[49]);

    }
    else if (!isExistTexture && strcmp(texname, "NULL"))
    {
        int i;
        int sum=1;
        char ** tex_splited;
        i = strlen(texname);
        if (texname[i-3] == 't' && texname[i-2] == 'x' && texname[i-1] == 't')
        {
            /*char temp[32];
            strcpy(temp, objname);
            strcat(temp, "/textures.txt");
            FILE * file = fopen(temp, "r");*/
            FILE * file = fopen(texname, "r");
            if (file == 0)
                strcpy(texname, "error.bmp");
            else
            {
                fscanf(file, "%d", &sum);
                tex_splited = new char* [sum];
                for (int i=0; i<sum; i++)
                    tex_splited[i] = new char [30];
                int i=0;
                while (!feof(file))
                {
                    fscanf(file, "%s", tex_splited[i]);
                    i++;
                }

                fclose(file);
            }

        }
        else
        {
            i=0;
            while (texname[i] != 0)
            {
                if (texname[i] == ';')
                    sum++;
                i++;
            }
            tex_splited = new char* [sum];
            if (sum > 1)
            {
                int j=0;

                for (i=0; i<sum; i++)
                {
                    tex_splited[i] = new char [30];
                    int k=0;
                    while (texname[j] != 0 && texname[j] != ';')
                    {
                        tex_splited[i][k] = texname[j];
                        j++;
                        k++;
                    }
                    tex_splited[i][k] = 0;
                    j++;
                }
            }
        }

        new_textureid.texture = new GLuint[sum];
        glGenTextures(sum, new_textureid.texture);

        if (sum > 1)
        {
            for (i=0; i<sum; i++)
            {
                eLoadBMPTexture(tex_splited[i], new_textureid.texture[i]);
                delete [] tex_splited[i];
            }
            delete [] tex_splited;
        }
        else
            eLoadBMPTexture(texname, new_textureid.texture[0]);

        new_textureid.tex_num_per_obj = sum;
    }

    if (!isExistTexture)
    {
        new_textureid.tex_numbers = 1;
        textureid = global_texture.insert(new_textureid);
        texPathIt = global_texture_path.insert(texname);
    }


    /**loading obj and texture coords**/
    //if (!strcmp(extension, "obj") || !strcmp(extension, "OBJ"))
    if (strncmp(objname, "negyzet", 7))
    {
        //checking if obj has been already loaded
        bool isExistObj=false;
        list<object>::Iterator j=global_mesh.begin();
        for (char_list::Iterator i=global_mesh_path.begin(); i!=global_mesh_path.end() && !isExistObj; i++)
        {
            if (!strcmp(objname, *i))
            {
                //set iterator if obj already exist
                isExistObj = true;
                mesh_id = j;
                meshPathIt = i;
                (*mesh_id).mesh_numbers++;
            }

            j++;
        }

        if (!isExistObj)
        {
            //loading new obj if not exist
            object newMesh;
            newMesh.animation_length=0;
            char_list objnames;
            if (is_dir(objname))
            {
                DIR *dir;
                struct dirent *ent;
                dir = opendir (objname);
                int i=-2;
                while ((ent = readdir (dir)) != NULL)
                {
                    if (i>-1)
                    {
                        char extension[4];
                        int j=0;
                        while (ent->d_name[j] != '.' && j < strlen(ent->d_name))
                            j++;
                        extension[0] = ent->d_name[j+1];
                        extension[1] = ent->d_name[j+2];
                        extension[2] = ent->d_name[j+3];
                        extension[3] = 0;

                        if (!strcmp(extension, "obj") || !strcmp(extension, "OBJ"))
                        {
                            char temp[32];
                            strcpy(temp, objname);
                            strcat(temp, "/");
                            strcat(temp, ent->d_name);
                            objnames.insert(temp);
                            newMesh.animation_length++;
                        }
                    }
                    i++;
                }

            }
            else
            {
                objnames.insert(objname);
                newMesh.animation_length=1;
            }

            //get mesh numbers in one object
            newMesh.mesh_num_per_obj = 0;
            FILE * file = fopen(*objnames.begin(), "r");
            while (!feof(file))
            {
                char str[256];
                fscanf(file, "%s", str);
                if (!strcmp(str, "o"))
                    newMesh.mesh_num_per_obj++;
            }
            fclose(file);
            newMesh.mesh = new eMesh[newMesh.mesh_num_per_obj*newMesh.animation_length];
            for (int i=0; i<newMesh.mesh_num_per_obj*newMesh.animation_length; i++)
                eInitMesh(&newMesh.mesh[i]);
            int j=0;
            for (char_list::Iterator i = objnames.begin(); i!=objnames.end(); i++)
            {
                eLoadMeshFromOBJ(newMesh.mesh, *i, j);
                j+=newMesh.mesh_num_per_obj;
            }
            /*for (int i=0; i<newMesh.mesh_num_per_obj*newMesh.animation_length; i++)
                eCalcMeshNormals(&newMesh.mesh[i]);*/

            newMesh.mesh_numbers = 1;
            meshPathIt = global_mesh_path.insert(objname);


            newMesh.texcoords = (float**)malloc(sizeof(float*) * newMesh.mesh_num_per_obj);
            newMesh.texcoord_numbers = (int*)malloc(sizeof(int) * newMesh.mesh_num_per_obj);
            for (int i=0; i<newMesh.mesh_num_per_obj; i++)
            {
                newMesh.texcoords[i] = (float*)malloc(sizeof(float) * newMesh.mesh[i].max_face_num * 12);
                newMesh.texcoord_numbers[i] = newMesh.mesh[i].max_face_num * 12;

                for (int j=0; j< newMesh.mesh[i].max_face_num*12; j+=12)
                {
                    newMesh.texcoords[i][j] = 0;
                    newMesh.texcoords[i][j+1] = 0;
                    newMesh.texcoords[i][j+2] = 1;
                    newMesh.texcoords[i][j+3] = 0;
                    newMesh.texcoords[i][j+4] = 1;
                    newMesh.texcoords[i][j+5] = 1;
                    newMesh.texcoords[i][j+6] = 0;
                    newMesh.texcoords[i][j+7] = 0;
                    newMesh.texcoords[i][j+8] = 1;
                    newMesh.texcoords[i][j+9] = 1;
                    newMesh.texcoords[i][j+10] = 0;
                    newMesh.texcoords[i][j+11] = 1;
                }
            }

            mesh_id = global_mesh.insert(newMesh);
        }
    }
    else/* if (!strncmp(objname, "negyzet", 7))*/
    {

        if (!strcmp(objname, "negyzet"))
            vertices_ptr = 0;
        else
            vertices_ptr = 1;

        cube_texcoords = new float [12];
        if (mozaik)
        {
            if (!strcmp(objname, "negyzet"))
            {
                for (int i=0; i<12; i++)
                    if (i==0 || i==1 || i ==4 || i==6 || i==7 || i==9)
                        cube_texcoords[i] = 0;
                    else if (mozaik != 2 && (i==2 || i==8 || i ==10))
                        cube_texcoords[i] = sz*50;
                    else if (mozaik != 3)
                        cube_texcoords[i] = sx*50;
            }
            else
            {
                for (int i=0; i<12; i++)
                    if (i==0 || i==1 || i ==4 || i==6 || i==7 || i==9)
                        cube_texcoords[i] = 0;
                    else if (mozaik != 2 && (i==2 || i==8 || i ==10))
                        cube_texcoords[i] = sx*50;
                    else if (mozaik != 3)
                        cube_texcoords[i] = sy*50;
            }
        }
        else
        {
            for (int i=0; i<12; i++)
                if (i==0 || i==1 || i ==4 || i==6 || i==7 || i==9)
                    cube_texcoords[i] = 0;
                else
                    cube_texcoords[i] = 1;
        }
    }
}

Object::~Object()
{
    if (strncmp(objname, "negyzet", 7))
    {
        (*mesh_id).mesh_numbers--;
        if ((*mesh_id).mesh_numbers == 0)
        {
            if ((*mesh_id).mesh->faces)
                free((*mesh_id).mesh->faces);
            delete (*mesh_id).mesh;
            delete [] (*mesh_id).texcoords;
            global_mesh.remove(mesh_id);
            global_mesh_path.remove(meshPathIt);
        }
    }
    else
        delete [] cube_texcoords;

    if (strcmp(texname, "NULL"))
    {
        (*textureid).tex_numbers--;
        if ((*textureid).tex_numbers == 0)
        {
            delete [] (*textureid).texture;
            global_texture.remove(textureid);
            global_texture_path.remove(texPathIt);
        }
    }
}

bool Object::is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

/*void Object::delete_objects()
{
    for (list<eMesh*>::Iterator i=global_mesh.begin(); i!=global_mesh.end(); i++)
        delete *i;

    while (global_mesh.begin() != global_mesh.end())
        global_mesh.remove(global_mesh.begin());

    while (global_mesh_path.begin() != global_mesh_path.end())
        global_mesh_path.remove(global_mesh_path.begin());
}*/

void Object::rendering(const int & i)
{
    glEnableClientState(GL_NORMAL_ARRAY);

    glPushMatrix();

    if (appear < 2 || appear == 6)
    {
        //glRotatef(10, 1, 0, 0); //alap elforgatas a kameranezetnek megfeleloen

        //az Object elforgatasa a kamerahoz kepest
        //glTranslatef(txcamera, -0.25, tzcamera); //a kulso nezet miatti eltolas (belso nezet eseten ez nem kell)
        if (appear != 6)
        {
            glRotatef(rCameraY, 1, 0, 0);
            glRotatef(rCameraX, 0, 1, 0);
        }


        //glTranslatef(txcamera, tycamera, tzcamera); //kamera eltolas

        glTranslatef(tx, ty, tz); //eltolas az abszolut helyre

        if (appear != 6)
            glTranslatef(cx, cy, cz);

        if (appear == 1)
            glRotatef(-rCameraX, 0, 1, 0);

        //az Object elforgatasa az abszolut helyzetetehez kepest
        glRotatef(rx, 1, 0, 0);
        glRotatef(ry, 0, 1, 0);
        glRotatef(rz, 0, 0, 1);

        if (sy == 0.0) //szamitasi egyszerusites miatt a 0 osszenyomast is 1-nek vesszuk
            glScalef(sx, 1.0, sz);
        else
            glScalef(sx, sy, sz); //nagyitas/kicsinyites
    }
    else if (appear == 2)
    {
        glTranslatef(0, 2, tz);
        glRotatef(90, 1, 0, 0);
        glScalef(sx, 1.0, sz);
    }
    else if (appear == 3)
    {
        glTranslatef(tx, ty, -0.005);
        glRotatef(rz, 0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        glScalef(sx, sy, sz);
    }


    if (!strncmp(objname, "negyzet", 7))
        square(i);
    else
        eRenderMesh((*mesh_id).mesh);


    glPopMatrix();
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Object::gprintf(char * title)
{
    int i=0;
    int j=0;

    while (title[i] != 0)
    {
        if (title[i] != ' ' && title[i] != '_')
        {
            glEnable(GL_TEXTURE_2D);

            if (title[i] == '/')
            {
                i++;
                j++;
                if (title[i] == 'p')
                    glBindTexture(GL_TEXTURE_2D, (*textureid).texture[45]);
                else
                    glBindTexture(GL_TEXTURE_2D, (*textureid).texture[36+title[i]-'0']);
            }
            else if (title[i] == '.')
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[46]);
            else if (title[i] == '?')
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[47]);
            else if (title[i] == '\%')
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[48]);
            else if (title[i] == ',')
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[49]);
            else if (title[i] < 'a')
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[26+title[i]-'0']);
            else
                glBindTexture(GL_TEXTURE_2D, (*textureid).texture[title[i]-'a']);


            glPushMatrix();

            if (appear == 5)
            {
                //glRotatef(10, 1, 0, 0); //alap elforgatas a kameranezetnek megfeleloen
                glRotatef(rCameraY, 1, 0, 0);
                glRotatef(rCameraX, 0, 1, 0);

                //glTranslatef(txcamera, tycamera, tzcamera); //kamera eltolas
                glTranslatef(cx, cy, cz);
                glTranslatef(tx+(i-j)*sx*1.0, ty, tz+i*(float)rz/10000.0); //eltolas az abszolut helyre

                /*if (appear == 1)
                    glRotatef(-rCameraX, 0, 1, 0);*/

                //az Object elforgatasa az abszolut helyzetetehez kepest
                glRotatef(rx, 1, 0, 0);
                glRotatef(ry, 0, 1, 0);
                glRotatef(rz, 0, 0, 1);

                glScalef(sx, 1.0, sz);
            }
            else
            {
                glTranslatef(tx+(i-j)*sx*0.9, ty, -0.005);
                glRotatef(-90, 1, 0, 0);
                glRotatef(90, 0, 1, 0);
                glScalef(sx, sy, sz);
            }


            //if (!strncmp(objname, "negyzet", 7))
                square(0);
            /*else
                eRenderMesh(*mesh_id).mesh;*/

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }
        i++;
    }

}

char Object::eCreateTextureFromSDLSurface(SDL_Surface *surf, GLuint & textureid)
{
    glGetError();

    glBindTexture(GL_TEXTURE_2D, textureid);

    int pixels = surf->w * surf->h * 4;
    unsigned char *surfacedata = (unsigned char*) surf->pixels;
    unsigned char *data = (unsigned char*) malloc(sizeof(unsigned char) * pixels);
    int i;

    for (i = 0; i < pixels; i += 4)
    {
        data[i + 0] = surfacedata[i + 2];
        data[i + 1] = surfacedata[i + 1];
        data[i + 2] = surfacedata[i + 0];
        data[i + 3] = surfacedata[i + 3];
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (pixels > 16)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ezt a ket sort rakd vissza kommentbe es probald ki, hogy mit csinal
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }



    free(data);

    return 0;
}


void Object::eLoadBMPTexture(char *filename, GLuint & textureid)
{
    char error = 1;

    if (textureid)
    {
        SDL_Surface *image = SDL_LoadBMP(filename);
        if (!image)
            image = SDL_LoadBMP("error.bmp");
        SDL_Surface *optimized = NULL;
        if (image)
        {
            optimized = SDL_DisplayFormat(image);

            //SDL_Flip (optimized);
            SDL_FreeSurface(image);

            if (optimized)
            {
                if (!eCreateTextureFromSDLSurface(optimized, textureid))
                {
                    error = 0;
                }
                SDL_FreeSurface(optimized);
            }
        }
    }

    if (error)
    {
        fprintf(stderr, "Error during loading texture: %s\n", filename);
    }
}

void Object::square(const int & i)
{
    if (strcmp(texname, "NULL") && appear != 4 && appear != 5)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (*textureid).texture[i]);
    }
    //glEnable(GL_LIGHTING);
    //glNormalPointer(GL_FLOAT, sizeof(eVertex), cube_normals[1]);
    glVertexPointer(3, GL_FLOAT, 0, cube_vertices[vertices_ptr]);
    glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);
    //glEnable(GL_NORMALIZE);
    //glNormalPointer(GL_FLOAT,0,cube_normals[1]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(cube_vertices[vertices_ptr]) / sizeof(float) / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
    //glDisable(GL_LIGHTING);

    if (strcmp(texname, "NULL") && appear != 4 && appear != 5)
        glDisable(GL_TEXTURE_2D);
}

void Object::eAddFaceToMesh(eMesh *mesh, eFace *face)
{
    if (mesh->current_face_num >= mesh->max_face_num)
    {
        int incsize = mesh->max_face_num * 2 + 1;
        eFace *tmp = (eFace*) malloc(sizeof(eFace) * incsize);

        memcpy(tmp, mesh->faces, mesh->max_face_num * sizeof(eFace));
        mesh->max_face_num = incsize;

        if (mesh->faces)
        {
            free(mesh->faces);
        }
        mesh->faces = tmp;
    }

    mesh->faces[mesh->current_face_num++] = *face;
}

void Object::eInitVertexList(eVertexList *vl)
{
    vl->vertices = 0;
    vl->max_vertex_num = 0;
    vl->current_vertex_num = 0;
}

void Object::eLoadMeshFromOBJ(eMesh *mesh, char *file, const int & begin)
{
    FILE *fd = fopen(file, "rb");
    if (file == 0)
    {
        fprintf(stderr, "Error during loading obj file: %s\n", file);
        return;
    }

    int mesh_ptr=begin-1;

    if (fd)
    {
        eVertexList vertexlist;
        eInitVertexList(&vertexlist);
        int maxfacesNum=0;
        int current_maxfacesNum=0;

        while (!feof(fd))
        {
            char str[256];
            fscanf(fd, "%s", str);
            if (feof(fd))
            {
                break;
            }

            if (!strcmp(str, "o"))
            {
                maxfacesNum = current_maxfacesNum+1;
                mesh_ptr++;
                if (vertexlist.vertices)
                {
                    free(vertexlist.vertices);
                    vertexlist.vertices = 0;
                    eInitVertexList(&vertexlist);
                }

            }
            else if (!strcmp(str, "f"))
            {
                int a, b, c;

                fscanf(fd, "%d %d %d", &a, &b, &c);
                if (a > current_maxfacesNum)
                    current_maxfacesNum = a;
                if (b > current_maxfacesNum)
                    current_maxfacesNum = b;
                if (c > current_maxfacesNum)
                    current_maxfacesNum = c;
                if (feof(fd))
                {
                    break;
                }
                a-=maxfacesNum;
                b-=maxfacesNum;
                c-=maxfacesNum;

                eFace face;

                face.a = vertexlist.vertices[a];
                face.b = vertexlist.vertices[b];
                face.c = vertexlist.vertices[c];
                eAddFaceToMesh(&mesh[mesh_ptr], &face);
                b = c;

                while (!feof(fd))
                {
                    char str[256];
                    fscanf(fd, "%s", str);
                    if (feof(fd))
                    {
                        break;
                    }

                    if (!strcmp(str, "f") || !strcmp(str, "o"))
                    {
                        int offset = -strlen(str);
                        fseek(fd, offset, SEEK_CUR);
                        break;
                    }
                    else
                    {
                        sscanf(str, "%d", &c);
                        c-=maxfacesNum;

                        face.a = vertexlist.vertices[a];
                        face.b = vertexlist.vertices[b];
                        face.c = vertexlist.vertices[c];
                        eAddFaceToMesh(&mesh[mesh_ptr], &face);
                        b = c;
                    }
                }
            }
            else if (!strcmp(str, "v"))
            {
                eVertex v;
                fscanf(fd, "%f %f %f", &v.coord.x, &v.coord.y, &v.coord.z);
                /*v.normal.x = v.coord.x;
                v.normal.y = v.coord.y;
                v.normal.z = v.coord.z;*/
                if (feof(fd))
                {
                    break;
                }

                eAddVertexToVertexList(&vertexlist, &v);
            }
        }

        if (vertexlist.vertices)
        {
            free(vertexlist.vertices);
            vertexlist.vertices = 0;
        }

        fclose(fd);
    }
}

void Object::eAddVertexToVertexList(eVertexList *vl, eVertex *vertex)
{
    if (vl->current_vertex_num >= vl->max_vertex_num)
    {
        int incsize = vl->max_vertex_num * 2 + 1;
        eVertex *tmp = (eVertex*) malloc(sizeof(eVertex) * incsize);

        memcpy(tmp, vl->vertices, vl->max_vertex_num * sizeof(eVertex));
        vl->max_vertex_num = incsize;

        if (vl->vertices)
        {
            free(vl->vertices);
        }
        vl->vertices = tmp;
    }

    vl->vertices[vl->current_vertex_num++] = *vertex;
}

void Object::eRenderMesh(eMesh *m)
{
    for (int i=0; i<(*mesh_id).mesh_num_per_obj && i<(*textureid).tex_num_per_obj; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (*textureid).texture[i]);

        //glEnable(GL_LIGHTING);
        glVertexPointer(3, GL_FLOAT, sizeof(eVertex), &m[i].faces->a.coord.x);
        //glNormalPointer(GL_FLOAT, sizeof(eVertex), &m->faces->a.normal.x);
        glTexCoordPointer(2, GL_FLOAT, 0, (*mesh_id).texcoords[i]);

        glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, m[i].current_face_num * 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
        /*if (fenyek)*/
        //glDisable(GL_LIGHTING);
    }

}

void Object::eInitMesh(eMesh *mesh)
{
    mesh->faces = 0;
    mesh->current_face_num = 0;
    mesh->max_face_num = 0;
}

void Object::settx(float bex)
{
    this->tx = bex;
}

void Object::setty(float bey)
{
    this->ty = bey;
}

void Object::settz(float bez)
{
    this->tz = bez;
}

void Object::setsx(float bex)
{
    this->sx = bex;
}

void Object::setsy(float bey)
{
    this->sy = bey;
}

void Object::setsz(float bez)
{
    this->sz = bez;
}

void Object::setcx(float bex)
{
    cx = bex;
}

void Object::setcy(float bey)
{
    cy = bey;
}

void Object::setcz(float bez)
{
    cz = bez;
}

void Object::setrabsolute(int be)
{
    this->rabsolute = be;
}

void Object::setrCameraX(int be)
{
    rCameraX = be;
}

void Object::setGravityRange(float be)
{
    this->gravity_range = be;
}

void Object::setrx(int bex)
{
    this->rx = bex;
}

void Object::setry(int bey)
{
    this->ry = bey;
}

void Object::setrz(int bez)
{
    this->rz = bez;
}

float Object::gettx()
{
    return tx;
}

float Object::getty()
{
    return ty;
}

float Object::gettz()
{
    return tz;
}

float Object::getcx()
{
    return cx;
}

float Object::getcy()
{
    return cy;
}

float Object::getcz()
{
    return cz;
}

float Object::getsx()
{
    return sx;
}

float Object::getsy()
{
    return sy;
}

float Object::getsz()
{
    return sz;
}

int Object::getrx()
{
    return rx;
}

int Object::getry()
{
    return ry;
}

int Object::getrz()
{
    return rz;
}

float Object::getTxcamera()
{
    return txcamera;
}

float Object::getTycamera()
{
    return tycamera;
}

float Object::getTzcamera()
{
    return tzcamera;
}

int Object::get_rCameraX()
{
    return rCameraX;
}

int Object::get_rCameraY()
{
    return rCameraY;
}

void Object::rotateX(const int & x)
{
    rx+=x;
    if (rx > 359)
        rx = 0;
}

void Object::rotateY(const int & x)
{
    ry+=x;
    if (ry > 359)
        ry = 0;
}

void Object::rotateZ(const int & x)
{
    rz+=x;
    if (rz > 359)
        rz = 0;
}

void Object::cVertical(const float & x)
{
    /*cz +=cos(rCameraX*3.1415/180)*x;
    cx -=sin(rCameraX*3.1415/180)*x;*/
    cz+=x;
}

void Object::cHorizontal(const float & x)
{
    cx+=x;
}

void Object::cLenghtical(const float & x)
{
    cy+=x;
}

void Object::aelore(const float & x)
{
    tz -=cos(rz*3.1415/180)*x;
    tx +=sin(rz*3.1415/180)*x;
}

void Object::ahatra(const float & x)
{
    tz +=cos(rabsolute*3.1415/180)*x;
    tx -=sin(rabsolute*3.1415/180)*x;
}

void Object::cbalra(const int & x)
{
    rCameraX-=x;
    if (rCameraX < 0)
        rCameraX = 358;
}

void Object::cjobbra(const int & x)
{
    rCameraX+=x;
    if (rCameraX > 358)
        rCameraX = 0;

}

void Object::cfel(const int & x)
{
    rCameraY-=x;
    if (rCameraY < 270 && rCameraY > 100)
        rCameraY = 270;
    if (rCameraY < 0)
        rCameraY = rCameraY+360;
}

void Object::cle(const int & x)
{
    rCameraY+=x;
    if (rCameraY < 260 && rCameraY > 90)
        rCameraY = 90;
    if (rCameraY > 360)
        rCameraY = rCameraY-360;
}

void Object::trans_horizontal(const float & x)
{
    tx+=x;
}
void Object::trans_lengthical(const float & y)
{
    ty+=y;
}

void Object::trans_vertical(const float & z)
{
    tz+=z;
}

void Object::trans_gravity(const float & x)
{
    gravity_range += x;
}

void Object::set_rCameraX(const float & x)
{
    rCameraX = x;
}

void Object::set_rCameraY(const float & y)
{
    rCameraY = y;
}

void Object::tavolsag(const float & x)
{
    tzcamera+=x;
}

void Object::doles(const int & x)
{
    ry+=x;
}

int Object::getrabsolute()
{
    return rabsolute;
}

float Object::getGravityRange()
{
    return gravity_range;
}

int Object::getAppear()
{
    return appear;
}

int Object::getMozaik()
{
    return mozaik;
}

eCoord3f Object::eCrossProduct(eCoord3f a, eCoord3f b) // vektorialis szorzas
{
    eCoord3f r;

    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;

    return r;
}

void Object::eCalcMeshNormals(eMesh *m)
{
    int i;
    for (i = 0; i < m->current_face_num; ++i)
    {
        eFace *f = &m->faces[i];

        eCoord3f *a = (eCoord3f*)&f->a;
        eCoord3f *b = (eCoord3f*)&f->b;
        eCoord3f *c = (eCoord3f*)&f->c;

        eCoord3f v1;
        v1.x = b->x - a->x;
        v1.y = b->y - a->y;
        v1.z = b->z - a->z;

        eCoord3f v2;
        v2.x = c->x - a->x;
        v2.y = c->y - a->y;
        v2.z = c->z - a->z;

        eCoord3f r = eCrossProduct(v1, v2);
        f->a.normal = r;
        f->b.normal = r;
        f->c.normal = r;
    }
}

char* Object::getTexture()
{
    return texname;
}

char* Object::getObjname()
{
    return objname;
}

void Object::operator = (Object & other)
{
    this->tx = other.tx;
    this->ty = other.ty;
    this->tz = other.tz;
    this->rx = other.rx;
    this->ry = other.ry;
    this->rz = other.rz;
    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
}

bool Object::operator ==(Object & other)
{
    if (other.getry() == 0 || other.getry() == 180)
    {
        if (this->gettx() + this->getsx()  > other.gettx() - (other.getsx()/* *(space/100.0)*/)  &&
        this->gettx() - this->getsx()  < other.gettx() + (other.getsx()/* *(space/100.0)*/)  &&
        this->gettz() + this->getsz()  > other.gettz() - (other.getsz()/* *(space/100.0)*/)  &&
        this->gettz() - this->getsz()  < other.gettz() + (other.getsz()/* *(space/100.0)*/) )
            return true;
        else
            return false;
    }
    else
    {
        if (this->gettx() + this->getsx()  > other.gettx() - (other.getsz()/* *(space/100.0)*/)  &&
        this->gettx() - this->getsx()  < other.gettx() + (other.getsz()/* *(space/100.0)*/)  &&
        this->gettz() + this->getsz()  > other.gettz() - (other.getsx()/* *(space/100.0)*/)  &&
        this->gettz() - this->getsz()  < other.gettz() + (other.getsx()/* *(space/100.0)*/) )
            return true;
        else
            return false;
    }

}
