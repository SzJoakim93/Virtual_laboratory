#ifndef OBJECT_H
#define OBJECT_H

#include "GL/gl.h"
#include "SDL/SDL.h"
#include "gl/glu.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>

#include "list.h"
#include "char_list.h"

#define PI 3.141592

typedef struct eCoord3f
{
    float x;
    float y;
    float z;
} eCoord3f;

typedef struct eVertex
{
    eCoord3f coord;
    eCoord3f normal;
} eVertex;

typedef struct eFace
{
    eVertex a, b, c;
} eFace;

typedef struct eMesh
{
    int max_face_num;
    int current_face_num;
    eFace *faces;
} eMesh;

typedef struct eVertexList
{
    int max_vertex_num;
    int current_vertex_num;
    eVertex *vertices;
} eVertexList;

typedef struct object
{
    eMesh * mesh;
    int mesh_num_per_obj;
    int mesh_numbers;
    int animation_length;
    float ** texcoords;
    int * texcoord_numbers;
} object;

typedef struct texture
{
    GLuint* texture;
    int tex_num_per_obj;
    int tex_numbers;
} Texture;

class Object
{
    public:
        Object();
        Object(const Object & masik);
        Object(float betx, float bety, float betz,
             int berx, int bery, int berz,
             float besx, float besy, float besz,
             bool fenyek, char* betexture, int bemozaik, char* betype, int beapp, int beflag);
        ~Object();
        //static void delete_objects();
        void rendering(const int & i); //Object parameter nelkuli renderingese (kep eseten)
        void gprintf(char * title); //Object renderingese szovegkent
        static void cVertical(const float & x); //kamera mozgasa elore
        static void cHorizontal(const float & x); //kamera mozgasa oldalra
        static void cLenghtical(const float & x); //kamera mozgasa fel
        void aelore(const float & x); //Object mozgasa elore
        void ahatra(const float & x); //Object mozgasa hatra
        static void cbalra(const int & x); //kamera mozgasa balra
        static void cjobbra(const int & x); //kamera mozgasa jobbra
        static void cfel(const int & x); //kamera mozgasa fel
        static void cle(const int & x); //kamera mozgasa le
        static int get_rCameraX();
        static int get_rCameraY();
        void trans_vertical(const float & x);
        void trans_lengthical(const float & y);
        void trans_horizontal(const float & z);
        void trans_gravity(const float & x);
        void tavolsag(const float & x);
        void doles(const int & x);
        void rotateX(const int & x);
        void rotateY(const int & x);
        void rotateZ(const int & x);
        //setterek:
        void settx(float bex);
        void setty(float bey);
        void settz(float bez);
        void setsx(float bex);
        void setsy(float bey);
        void setsz(float bez);
        void setrx(int bex);
        void setry(int bey);
        void setrz(int bez);
        static void setcx(float bex);
        static void setcy(float bey);
        static void setcz(float bez);
        void setrabsolute(int be);
        static void setrCameraX(int be);
        void setGravityRange(float be);
        static void set_rCameraX(const float & x);
        static void set_rCameraY(const float & y);
        //getterek:
        float gettx();
        float getty();
        float gettz();
        static float getcx();
        static float getcy();
        static float getcz();
        float getsx();
        float getsy();
        float getsz();
        int getrx();
        int getry();
        int getrz();
        int getrabsolute();
        float getGravityRange();
        static float getTxcamera();
        static float getTycamera();
        static float getTzcamera();
        char* getTexture();
        char* getObjname();
        int getMozaik();
        int getAppear();
        void operator = (Object & other);
        bool operator ==(Object & other);
        bool isCollision();
    protected:
    private:
    friend class Multi_Object;
        //Object koordinatai:
        float tx;
        float ty;
        float tz;
        //kamera eltolas:
        static float cx;
        static float cy;
        static float cz;
         //Object elforgatasa:
        int rx;
        int ry;
        int rz;
         //kamera koruli forgatas
        static int rCameraX;
        static int rCameraY;
        //Object iranya (jelen esetben az ellenfel merre forduljon)
        int rabsolute;
        static float txcamera;
        static float tycamera;
        static float tzcamera;
        //Object atmeretezese:
        float sx;
        float sy;
        float sz;
        bool fenyek; //hassanak-e ra a fenyek
        //blender file betoltese eseten az obj file elerese, negyzet eseten a "negyzet" szo
        char objname[32];
        //textura elerese, szoveg kiirasa eseten csak a mappa nevet kell megadni
        char texname[64];
        //megjelenes tipusa
        int appear;
        //mozaik texturazas: 0: nyujtja a texturat 1: a texturazas mozaikokkal torteneik 2: csak vizszintesen nyujtja 3: csak fuggolegesen nyujtja,
        int mozaik;
        //textura azonositoi
        //GLuint * textureid;
        //tetszoleges flag
        float gravity_range;
        //az objektumon megjeleno texturak szama
        //int maxtexture;

        list<Texture>::Iterator textureid;
        char_list::Iterator texPathIt;

        list<object>::Iterator mesh_id;
        char_list::Iterator meshPathIt;

        //objektumok texturakoordinatai
        float * cube_texcoords;
        const static float cube_vertices[2][18];
        const static float cube_normals[2][18];

        int vertices_ptr;
        int texcoord_number;

        static list<object> global_mesh;
        static char_list global_mesh_path;

        //objektumok texturakoordinatai

        static list<Texture> global_texture;
        static char_list global_texture_path; //texturak eleresenek listaja

        bool is_dir(const char* path);

        //ez a 3 mar ismeros :D
        char eCreateTextureFromSDLSurface(SDL_Surface *surf, GLuint & textureid);
        void eLoadBMPTexture(char *filename, GLuint & textureid);
        void square(const int & i); //beepitett negyzet kirajzolasa

        void eRenderMesh(eMesh *m);
        void eLoadMeshFromOBJ(eMesh *mesh, char *file, const int & begin);
        void eInitVertexList(eVertexList *vl);
        void eAddFaceToMesh(eMesh *mesh, eFace *face);
        void eAddVertexToVertexList(eVertexList *vl, eVertex *vertex);
        void eInitMesh(eMesh *mesh);
        eCoord3f eCrossProduct(eCoord3f a, eCoord3f b);
        void eCalcMeshNormals(eMesh *m);
};

#endif // Object_H
