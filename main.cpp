#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok
//  Risna Anggita (672020237)
//  Tiara Syah Indra (672020242)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion{
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init(){
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}


    void pillar() {
    /* Pillar 1 */
    // Kotak Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 0, -50.25);
    glVertex3f(98, 0, -62.25);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(98, 11.875, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 0, -62.25);
    glVertex3f(86, 0, -62.25);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(98, 11.875, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 0, -62.25);
    glVertex3f(86, 0, -50.25);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(86, 11.875, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 0, -50.25);
    glVertex3f(98, 0, -50.25);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(86, 11.875, -50.25);
    glEnd();
    // Miring Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(97, 14.375, -51.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(97, 14.375, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(87, 14.375, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(87, 14.375, -51.25);
    glEnd();
    // Kotak Miring Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(87, 20.063, -61.25);
    glVertex3f(97, 20.063, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(87, 20.063, -51.25);
    glVertex3f(87, 20.063, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(97, 20.063, -51.25);
    glVertex3f(87, 20.063, -51.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(97, 20.063, -61.25);
    glVertex3f(97, 20.063, -51.25);
    glEnd();
    // Kotak Tengah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(98, 20.063, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 23.75, -62.25);
    glVertex3f(86, 23.75, -62.25);
    glVertex3f(86, 23.75, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 23.75, -62.25);
    glVertex3f(98, 23.75, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(86, 23.75, -50.25);
    glVertex3f(86, 23.75, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(98, 20.063, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glVertex3f(86, 23.75, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(98, 20.063, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glVertex3f(98, 23.75, -62.25);
    glEnd();
    // Miring Tengah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97, 23.75, -61.25);
    glVertex3f(87, 23.75, -61.25);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(95, 26.25, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(87, 23.75, -61.25);
    glVertex3f(87, 23.75, -51.25);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(89, 26.25, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(87, 23.75, -51.25);
    glVertex3f(97, 23.75, -51.25);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(89, 26.25, -53.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97, 23.75, -51.25);
    glVertex3f(97, 23.75, -61.25);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(95, 26.25, -53.25);
    glEnd();
    // Tiang Panjang
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(95, 84.375, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(89, 84.375, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(89, 84.375, -53.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(95, 84.375, -53.25);
    glEnd();
    // Miring Atas
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(88, 87.5, -60.25);
    glVertex3f(96, 87.5, -60.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(88, 87.5, -52.25);
    glVertex3f(88, 87.5, -60.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(96, 87.5, -52.25);
    glVertex3f(88, 87.5, -52.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(96, 87.5, -60.25);
    glVertex3f(96, 87.5, -52.25);
    glEnd();

    /* Pillar 2 */
    // Kotak Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 0, -105.718);
    glVertex3f(21.65, 0, -105.718);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(33.65, 11.875, -105.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(21.65, 0, -105.718);
    glVertex3f(21.65, 0, -93.718);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(21.65, 11.875, -105.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(21.65, 0, -93.718);
    glVertex3f(33.65, 0, -93.718);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(21.65, 11.875, -93.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 0, -93.718);
    glVertex3f(33.65, 0, -105.718);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(33.65, 11.875, -93.718);
    glEnd();
    // Miring Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(32.65, 14.375, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(22.65, 14.375, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(22.65, 14.375, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(32.65, 14.375, -94.718);
    glEnd();
    // Kotak Miring Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(22.65, 20.063, -104.718);
    glVertex3f(32.65, 20.063, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(22.65, 20.063, -94.718);
    glVertex3f(22.65, 20.063, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(32.65, 20.063, -94.718);
    glVertex3f(22.65, 20.063, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(32.65, 20.063, -104.718);
    glVertex3f(32.65, 20.063, -94.718);
    glEnd();
    // Kotak Tengah
    // --BOTTOM
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glEnd();
    // --TOP
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 23.75 ,-93.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glVertex3f(33.65, 23.75 ,-93.718);
    glEnd();
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glVertex3f(33.65, 23.75 ,-93.718);
    glEnd();
    // Miring Tengah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(32.65, 23.75, -104.718);
    glVertex3f(22.65, 23.75, -104.718);
    glVertex3f(24.65, 26.25, -102.25);
    glVertex3f(30.65, 26.25, -102.25);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(22.65, 23.75, -104.718);
    glVertex3f(22.65, 23.75, -94.718);
    glVertex3f(24.65, 26.25, -96.25);
    glVertex3f(24.65, 26.25, -102.25);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(22.65, 23.75, -94.718);
    glVertex3f(32.65, 23.75, -94.718);
    glVertex3f(30.65, 26.25, -96.25);
    glVertex3f(24.65, 26.25, -96.25);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(32.65, 23.75, -94.718);
    glVertex3f(32.65, 23.75, -104.718);
    glVertex3f(30.65, 26.25, -102.25);
    glVertex3f(30.65, 26.25, -96.25);
    glEnd();
    // Tiang Panjang
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(30.65, 26.25, -102.718);
    glVertex3f(24.65, 26.25, -102.718);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(30.65, 84.375, -102.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(24.65, 26.25, -102.718);
    glVertex3f(24.65, 26.25, -96.718);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(24.65, 84.375, -102.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(24.65, 26.25, -96.718);
    glVertex3f(30.65, 26.25, -96.718);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(24.65, 84.375, -96.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(30.65, 26.25, -96.718);
    glVertex3f(30.65, 26.25, -102.718);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(30.65, 84.375, -96.718);
    glEnd();
    // Miring Atas
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(23.65, 87.5, -103.718);
    glVertex3f(31.65, 87.5, -103.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(23.65, 87.5, -95.718);
    glVertex3f(23.65, 87.5, -103.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(31.65, 87.5, -95.718);
    glVertex3f(23.65, 87.5, -95.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(31.65, 87.5, -103.718);
    glVertex3f(31.65, 87.5, -95.718);
    glEnd();

    /* Pillar 3 */
    // Kotak Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 0, -105.718);
    glVertex3f(-21.65, 0, -105.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-21.65, 0, -105.718);
    glVertex3f(-21.65, 0, -93.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-21.65, 0, -93.718);
    glVertex3f(-33.65, 0, -93.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 0, -93.718);
    glVertex3f(-33.65, 0, -105.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glEnd();
    // Miring Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glEnd();
    // Kotak Miring Bawah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-22.65, 20.063, -104.718);
    glVertex3f(-32.65, 20.063, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-22.65, 20.063, -94.718);
    glVertex3f(-22.65, 20.063, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-32.65, 20.063, -94.718);
    glVertex3f(-22.65, 20.063, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-32.65, 20.063, -104.718);
    glVertex3f(-32.65, 20.063, -94.718);
    glEnd();
    // Kotak Tengah
    // --BOTTOM
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glEnd();
    // --TOP
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glEnd();
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glEnd();
    // Miring Tengah
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-32.65, 23.75, -104.718);
    glVertex3f(-22.65, 23.75, -104.718);
    glVertex3f(-24.65, 26.25, -102.25);
    glVertex3f(-30.65, 26.25, -102.25);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-22.65, 23.75, -104.718);
    glVertex3f(-22.65, 23.75, -94.718);
    glVertex3f(-24.65, 26.25, -96.25);
    glVertex3f(-24.65, 26.25, -102.25);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-22.65, 23.75, -94.718);
    glVertex3f(-32.65, 23.75, -94.718);
    glVertex3f(-30.65, 26.25, -96.25);
    glVertex3f(-24.65, 26.25, -96.25);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-32.65, 23.75, -94.718);
    glVertex3f(-32.65, 23.75, -104.718);
    glVertex3f(-30.65, 26.25, -102.25);
    glVertex3f(-30.65, 26.25, -96.25);
    glEnd();
    // Tiang Panjang
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-30.65, 26.25, -102.718);
    glVertex3f(-24.65, 26.25, -102.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-24.65, 26.25, -102.718);
    glVertex3f(-24.65, 26.25, -96.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-24.65, 26.25, -96.718);
    glVertex3f(-30.65, 26.25, -96.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-30.65, 26.25, -96.718);
    glVertex3f(-30.65, 26.25, -102.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glEnd();
    // Miring Atas
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-23.65, 87.5, -103.718);
    glVertex3f(-31.65, 87.5, -103.718);
    glEnd();
    // --LEFT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-23.65, 87.5, -95.718);
    glVertex3f(-23.65, 87.5, -103.718);
    glEnd();
    // --BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-31.65, 87.5, -95.718);
    glVertex3f(-23.65, 87.5, -95.718);
    glEnd();
    // --RIGHT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-31.65, 87.5, -103.718);
    glVertex3f(-31.65, 87.5, -95.718);
    glEnd();

    /* Pillar 4 */
    // Kotak Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 0, -50.25);
    glVertex3f(-98, 0, -62.25);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-98, 11.875, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 0, -62.25);
    glVertex3f(-86, 0, -62.25);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-98, 11.875, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 0, -62.25);
    glVertex3f(-86, 0, -50.25);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-86, 11.875, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 0, -50.25);
    glVertex3f(-98, 0, -50.25);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-86, 11.875, -50.25);
    glEnd();
    // Miring Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-97, 14.375, -51.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-97, 14.375, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-87, 14.375, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-87, 14.375, -51.25);
    glEnd();
    // Kotak Miring Bawah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-87, 20.063, -61.25);
    glVertex3f(-97, 20.063, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-87, 20.063, -51.25);
    glVertex3f(-87, 20.063, -61.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-97, 20.063, -51.25);
    glVertex3f(-87, 20.063, -51.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-97, 20.063, -61.25);
    glVertex3f(-97, 20.063, -51.25);
    glEnd();
    // Kotak Tengah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-98, 20.063, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 23.75, -62.25);
    glVertex3f(-86, 23.75, -62.25);
    glVertex3f(-86, 23.75, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 23.75, -62.25);
    glVertex3f(-98, 23.75, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-86, 23.75, -50.25);
    glVertex3f(-86, 23.75, -62.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-98, 20.063, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glVertex3f(-86, 23.75, -50.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-98, 20.063, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glVertex3f(-98, 23.75, -62.25);
    glEnd();
    // Miring Tengah
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97, 23.75, -61.25);
    glVertex3f(-87, 23.75, -61.25);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-95, 26.25, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-87, 23.75, -61.25);
    glVertex3f(-87, 23.75, -51.25);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-89, 26.25, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-87, 23.75, -51.25);
    glVertex3f(-97, 23.75, -51.25);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-89, 26.25, -53.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97, 23.75, -51.25);
    glVertex3f(-97, 23.75, -61.25);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-95, 26.25, -53.25);
    glEnd();
    // Tiang Panjang
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-95, 84.375, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-89, 84.375, -59.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-89, 84.375, -53.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-95, 84.375, -53.25);
    glEnd();
    // Miring Atas
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-88, 87.5, -60.25);
    glVertex3f(-96, 87.5, -60.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-88, 87.5, -52.25);
    glVertex3f(-88, 87.5, -60.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-96, 87.5, -52.25);
    glVertex3f(-88, 87.5, -52.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-96, 87.5, -60.25);
    glVertex3f(-96, 87.5, -52.25);
    glEnd();
}
void pillar_outline() {
    /* Pillar 1 Outline */
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 0, -50.25);
    glVertex3f(98, 0, -62.25);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(98, 11.875, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 0, -62.25);
    glVertex3f(86, 0, -62.25);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(98, 11.875, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 0, -62.25);
    glVertex3f(86, 0, -50.25);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(86, 11.875, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 0, -50.25);
    glVertex3f(98, 0, -50.25);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(86, 11.875, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(97, 14.375, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 11.875, -62.25);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(97, 14.375, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 11.875, -62.25);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(87, 14.375, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 11.875, -50.25);
    glVertex3f(98, 11.875, -50.25);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(87, 14.375, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(87, 20.063, -61.25);
    glVertex3f(97, 20.063, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(87, 14.375, -61.25);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(87, 20.063, -51.25);
    glVertex3f(87, 20.063, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(87, 14.375, -51.25);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(97, 20.063, -51.25);
    glVertex3f(87, 20.063, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(97, 14.375, -51.25);
    glVertex3f(97, 14.375, -61.25);
    glVertex3f(97, 20.063, -61.25);
    glVertex3f(97, 20.063, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(98, 20.063, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(98, 20.063, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 23.75, -62.25);
    glVertex3f(86, 23.75, -62.25);
    glVertex3f(86, 23.75, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 23.75, -62.25);
    glVertex3f(98, 23.75, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 20.063, -62.25);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(86, 23.75, -50.25);
    glVertex3f(86, 23.75, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(86, 20.063, -50.25);
    glVertex3f(98, 20.063, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glVertex3f(86, 23.75, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(98, 20.063, -62.25);
    glVertex3f(98, 20.063, -50.25);
    glVertex3f(98, 23.75, -50.25);
    glVertex3f(98, 23.75, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(97, 23.75, -61.25);
    glVertex3f(87, 23.75, -61.25);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(95, 26.25, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(87, 23.75, -61.25);
    glVertex3f(87, 23.75, -51.25);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(89, 26.25, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(87, 23.75, -51.25);
    glVertex3f(97, 23.75, -51.25);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(89, 26.25, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(97, 23.75, -51.25);
    glVertex3f(97, 23.75, -61.25);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(95, 26.25, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(95, 84.375, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(89, 26.25, -59.25);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(89, 84.375, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(89, 26.25, -53.25);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(89, 84.375, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95, 26.25, -53.25);
    glVertex3f(95, 26.25, -59.25);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(95, 84.375, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(88, 87.5, -60.25);
    glVertex3f(96, 87.5, -60.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(89, 84.375, -59.25);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(88, 87.5, -52.25);
    glVertex3f(88, 87.5, -60.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(89, 84.375, -53.25);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(96, 87.5, -52.25);
    glVertex3f(88, 87.5, -52.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95, 84.375, -53.25);
    glVertex3f(95, 84.375, -59.25);
    glVertex3f(96, 87.5, -60.25);
    glVertex3f(96, 87.5, -52.25);
    glEnd();
    /* Pillar 2 */
    // Kotak Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 0, -105.718);
    glVertex3f(21.65, 0, -105.718);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(33.65, 11.875, -105.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(21.65, 0, -105.718);
    glVertex3f(21.65, 0, -93.718);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(21.65, 11.875, -105.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(21.65, 0, -93.718);
    glVertex3f(33.65, 0, -93.718);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(21.65, 11.875, -93.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 0, -93.718);
    glVertex3f(33.65, 0, -105.718);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(33.65, 11.875, -93.718);
    glEnd();
    // Miring Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(32.65, 14.375, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(21.65, 11.875, -105.718);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(22.65, 14.375, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(21.65, 11.875, -93.718);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(22.65, 14.375, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 11.875, -93.718);
    glVertex3f(33.65, 11.875, -105.718);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(32.65, 14.375, -94.718);
    glEnd();
    // Kotak Miring Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(22.65, 20.063, -104.718);
    glVertex3f(32.65, 20.063, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(22.65, 14.375, -104.718);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(22.65, 20.063, -94.718);
    glVertex3f(22.65, 20.063, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(22.65, 14.375, -94.718);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(32.65, 20.063, -94.718);
    glVertex3f(22.65, 20.063, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(32.65, 14.375, -94.718);
    glVertex3f(32.65, 14.375, -104.718);
    glVertex3f(32.65, 20.063, -104.718);
    glVertex3f(32.65, 20.063, -94.718);
    glEnd();
    // Kotak Tengah
    // --BOTTOM
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glEnd();
    // --TOP
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 23.75 ,-93.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glVertex3f(33.65, 23.75 ,-93.718);
    glEnd();
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glVertex3f(33.65, 23.75 ,-105.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(21.65, 20.063 ,-105.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glVertex3f(21.65, 23.75 ,-105.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(33.65, 20.063 ,-93.718);
    glVertex3f(21.65, 20.063 ,-93.718);
    glVertex3f(21.65, 23.75 ,-93.718);
    glVertex3f(33.65, 23.75 ,-93.718);
    glEnd();
    // Miring Tengah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(32.65, 23.75, -104.718);
    glVertex3f(22.65, 23.75, -104.718);
    glVertex3f(24.65, 26.25, -102.25);
    glVertex3f(30.65, 26.25, -102.25);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(22.65, 23.75, -104.718);
    glVertex3f(22.65, 23.75, -94.718);
    glVertex3f(24.65, 26.25, -96.25);
    glVertex3f(24.65, 26.25, -102.25);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(22.65, 23.75, -94.718);
    glVertex3f(32.65, 23.75, -94.718);
    glVertex3f(30.65, 26.25, -96.25);
    glVertex3f(24.65, 26.25, -96.25);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(32.65, 23.75, -94.718);
    glVertex3f(32.65, 23.75, -104.718);
    glVertex3f(30.65, 26.25, -102.25);
    glVertex3f(30.65, 26.25, -96.25);
    glEnd();
    // Tiang Panjang
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(30.65, 26.25, -102.718);
    glVertex3f(24.65, 26.25, -102.718);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(30.65, 84.375, -102.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(24.65, 26.25, -102.718);
    glVertex3f(24.65, 26.25, -96.718);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(24.65, 84.375, -102.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(24.65, 26.25, -96.718);
    glVertex3f(30.65, 26.25, -96.718);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(24.65, 84.375, -96.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(30.65, 26.25, -96.718);
    glVertex3f(30.65, 26.25, -102.718);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(30.65, 84.375, -96.718);
    glEnd();
    // Miring Atas
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(23.65, 87.5, -103.718);
    glVertex3f(31.65, 87.5, -103.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(24.65, 84.375, -102.718);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(23.65, 87.5, -95.718);
    glVertex3f(23.65, 87.5, -103.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(24.65, 84.375, -96.718);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(31.65, 87.5, -95.718);
    glVertex3f(23.65, 87.5, -95.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(30.65, 84.375, -96.718);
    glVertex3f(30.65, 84.375, -102.718);
    glVertex3f(31.65, 87.5, -103.718);
    glVertex3f(31.65, 87.5, -95.718);
    glEnd();

    /* Pillar 3 */
    // Kotak Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 0, -105.718);
    glVertex3f(-21.65, 0, -105.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-21.65, 0, -105.718);
    glVertex3f(-21.65, 0, -93.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-21.65, 0, -93.718);
    glVertex3f(-33.65, 0, -93.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 0, -93.718);
    glVertex3f(-33.65, 0, -105.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glEnd();
    // Miring Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-21.65, 11.875, -105.718);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-21.65, 11.875, -93.718);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 11.875, -93.718);
    glVertex3f(-33.65, 11.875, -105.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glEnd();
    // Kotak Miring Bawah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-22.65, 20.063, -104.718);
    glVertex3f(-32.65, 20.063, -104.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-22.65, 14.375, -104.718);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-22.65, 20.063, -94.718);
    glVertex3f(-22.65, 20.063, -104.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-22.65, 14.375, -94.718);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-32.65, 20.063, -94.718);
    glVertex3f(-22.65, 20.063, -94.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-32.65, 14.375, -94.718);
    glVertex3f(-32.65, 14.375, -104.718);
    glVertex3f(-32.65, 20.063, -104.718);
    glVertex3f(-32.65, 20.063, -94.718);
    glEnd();
    // Kotak Tengah
    // --BOTTOM
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glEnd();
    // --TOP
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glEnd();
    // --FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-33.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glVertex3f(-33.65, 23.75 ,-105.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-21.65, 20.063 ,-105.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-105.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-33.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 20.063 ,-93.718);
    glVertex3f(-21.65, 23.75 ,-93.718);
    glVertex3f(-33.65, 23.75 ,-93.718);
    glEnd();
    // Miring Tengah
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-32.65, 23.75, -104.718);
    glVertex3f(-22.65, 23.75, -104.718);
    glVertex3f(-24.65, 26.25, -102.25);
    glVertex3f(-30.65, 26.25, -102.25);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-22.65, 23.75, -104.718);
    glVertex3f(-22.65, 23.75, -94.718);
    glVertex3f(-24.65, 26.25, -96.25);
    glVertex3f(-24.65, 26.25, -102.25);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-22.65, 23.75, -94.718);
    glVertex3f(-32.65, 23.75, -94.718);
    glVertex3f(-30.65, 26.25, -96.25);
    glVertex3f(-24.65, 26.25, -96.25);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-32.65, 23.75, -94.718);
    glVertex3f(-32.65, 23.75, -104.718);
    glVertex3f(-30.65, 26.25, -102.25);
    glVertex3f(-30.65, 26.25, -96.25);
    glEnd();
    // Tiang Panjang
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-30.65, 26.25, -102.718);
    glVertex3f(-24.65, 26.25, -102.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-24.65, 26.25, -102.718);
    glVertex3f(-24.65, 26.25, -96.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-24.65, 26.25, -96.718);
    glVertex3f(-30.65, 26.25, -96.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-30.65, 26.25, -96.718);
    glVertex3f(-30.65, 26.25, -102.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glEnd();
    // Miring Atas
    // --FRONT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-23.65, 87.5, -103.718);
    glVertex3f(-31.65, 87.5, -103.718);
    glEnd();
    // --LEFT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-24.65, 84.375, -102.718);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-23.65, 87.5, -95.718);
    glVertex3f(-23.65, 87.5, -103.718);
    glEnd();
    // --BACK
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-24.65, 84.375, -96.718);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-31.65, 87.5, -95.718);
    glVertex3f(-23.65, 87.5, -95.718);
    glEnd();
    // --RIGHT
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-30.65, 84.375, -96.718);
    glVertex3f(-30.65, 84.375, -102.718);
    glVertex3f(-31.65, 87.5, -103.718);
    glVertex3f(-31.65, 87.5, -95.718);
    glEnd();

        /* Pillar 4 */
    // Kotak Bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 0, -50.25);
    glVertex3f(-98, 0, -62.25);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-98, 11.875, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 0, -62.25);
    glVertex3f(-86, 0, -62.25);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-98, 11.875, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 0, -62.25);
    glVertex3f(-86, 0, -50.25);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-86, 11.875, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 0, -50.25);
    glVertex3f(-98, 0, -50.25);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-86, 11.875, -50.25);
    glEnd();
    // Miring Bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-97, 14.375, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 11.875, -62.25);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-97, 14.375, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 11.875, -62.25);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-87, 14.375, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 11.875, -50.25);
    glVertex3f(-98, 11.875, -50.25);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-87, 14.375, -51.25);
    glEnd();
    // Kotak Miring Bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-87, 20.063, -61.25);
    glVertex3f(-97, 20.063, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-87, 14.375, -61.25);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-87, 20.063, -51.25);
    glVertex3f(-87, 20.063, -61.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-87, 14.375, -51.25);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-97, 20.063, -51.25);
    glVertex3f(-87, 20.063, -51.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-97, 14.375, -51.25);
    glVertex3f(-97, 14.375, -61.25);
    glVertex3f(-97, 20.063, -61.25);
    glVertex3f(-97, 20.063, -51.25);
    glEnd();
    // Kotak Tengah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-98, 20.063, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 23.75, -62.25);
    glVertex3f(-86, 23.75, -62.25);
    glVertex3f(-86, 23.75, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 23.75, -62.25);
    glVertex3f(-98, 23.75, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 20.063, -62.25);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-86, 23.75, -50.25);
    glVertex3f(-86, 23.75, -62.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-86, 20.063, -50.25);
    glVertex3f(-98, 20.063, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glVertex3f(-86, 23.75, -50.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-98, 20.063, -62.25);
    glVertex3f(-98, 20.063, -50.25);
    glVertex3f(-98, 23.75, -50.25);
    glVertex3f(-98, 23.75, -62.25);
    glEnd();
    // Miring Tengah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-97, 23.75, -61.25);
    glVertex3f(-87, 23.75, -61.25);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-95, 26.25, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-87, 23.75, -61.25);
    glVertex3f(-87, 23.75, -51.25);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-89, 26.25, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-87, 23.75, -51.25);
    glVertex3f(-97, 23.75, -51.25);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-89, 26.25, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-97, 23.75, -51.25);
    glVertex3f(-97, 23.75, -61.25);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-95, 26.25, -53.25);
    glEnd();
    // Tiang Panjang
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-95, 84.375, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-89, 26.25, -59.25);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-89, 84.375, -59.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-89, 26.25, -53.25);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-89, 84.375, -53.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95, 26.25, -53.25);
    glVertex3f(-95, 26.25, -59.25);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-95, 84.375, -53.25);
    glEnd();
    // Miring Atas
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-88, 87.5, -60.25);
    glVertex3f(-96, 87.5, -60.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-89, 84.375, -59.25);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-88, 87.5, -52.25);
    glVertex3f(-88, 87.5, -60.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-89, 84.375, -53.25);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-96, 87.5, -52.25);
    glVertex3f(-88, 87.5, -52.25);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95, 84.375, -53.25);
    glVertex3f(-95, 84.375, -59.25);
    glVertex3f(-96, 87.5, -60.25);
    glVertex3f(-96, 87.5, -52.25);
    glEnd();
}
void draw() {
    pillar();
    pillar_outline();
    ground();

    //bangunan samping kanan
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(166.3,0,24.7);
    glVertex3f(166.3,0,6.2);
    glVertex3f(166.3,97.5,6.2);
    glVertex3f(166.3,97.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(166.3,0,6.2);
    glVertex3f(171.5,0,6.2);
    glVertex3f(171.5,97.5,6.2);
    glVertex3f(166.3,97.5,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(171.5,0,6.2);
    glVertex3f(171.5,0,-5.2);
    glVertex3f(171.5,97.5,-5.2);
    glVertex3f(171.5,97.5,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(171.5,0,-5.2);
    glVertex3f(160,0,-5.2);
    glVertex3f(160,97.5,-5.2);
    glVertex3f(171.5,97.5,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(160,0,-5.2);
    glVertex3f(160,0,0);
    glVertex3f(160,97.5,0);
    glVertex3f(160,97.5,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(160,0,0);
    glVertex3f(141.5,0,0);
    glVertex3f(141.5,97.5,0);
    glVertex3f(160,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(141.5,0,-6.2);
    glVertex3f(141.5,0,0);
    glVertex3f(141.5,97.5,0);
    glVertex3f(141.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(141.5,0,-6.2);
    glVertex3f(134.5,0,-6.2);
    glVertex3f(134.5,97.5,-6.2);
    glVertex3f(141.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(134.5,0,-6.2);
    glVertex3f(134.5,0,0);
    glVertex3f(134.5,97.5,0);
    glVertex3f(134.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(134.5,0,0);
    glVertex3f(104,0,0);
    glVertex3f(104,97.5,0);
    glVertex3f(134.5,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(104,0,-6.2);
    glVertex3f(104,0,0);
    glVertex3f(104,97.5,0);
    glVertex3f(104,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97,0,-6.2);
    glVertex3f(104,0,-6.2);
    glVertex3f(104,97.5,-6.2);
    glVertex3f(97,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(100,0,-6.2);
    glVertex3f(104,0,0);
    glVertex3f(104,97.5,0);
    glVertex3f(100,97.5,-6.2);
    glEnd();
    //sebelah jendela kanan
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97,0,0);
    glVertex3f(70,0,0);
    glVertex3f(70,97.5,0);
    glVertex3f(97,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(97,0,0);
    glVertex3f(97,97.5,0);
    glVertex3f(97,97.5,-6.2);
    glVertex3f(97,0,-6.2);
    glEnd();

     //bangunan samping kiri
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-166.3,0,24.7);
    glVertex3f(-166.3,0,6.2);
    glVertex3f(-166.3,97.5,6.2);
    glVertex3f(-166.3,97.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-166.3,0,6.2);
    glVertex3f(-171.5,0,6.2);
    glVertex3f(-171.5,97.5,6.2);
    glVertex3f(-166.3,97.5,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-171.5,0,6.2);
    glVertex3f(-171.5,0,-5.2);
    glVertex3f(-171.5,97.5,-5.2);
    glVertex3f(-171.5,97.5,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-171.5,0,-5.2);
    glVertex3f(-160,0,-5.2);
    glVertex3f(-160,97.5,-5.2);
    glVertex3f(-171.5,97.5,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-160,0,-5.2);
    glVertex3f(-160,0,0);
    glVertex3f(-160,97.5,0);
    glVertex3f(-160,97.5,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-160,0,0);
    glVertex3f(-141.5,0,0);
    glVertex3f(-141.5,97.5,0);
    glVertex3f(-160,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-141.5,0,-6.2);
    glVertex3f(-141.5,0,0);
    glVertex3f(-141.5,97.5,0);
    glVertex3f(-141.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-141.5,0,-6.2);
    glVertex3f(-134.5,0,-6.2);
    glVertex3f(-134.5,97.5,-6.2);
    glVertex3f(-141.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-134.5,0,-6.2);
    glVertex3f(-134.5,0,0);
    glVertex3f(-134.5,97.5,0);
    glVertex3f(-134.5,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-134.5,0,0);
    glVertex3f(-104,0,0);
    glVertex3f(-104,97.5,0);
    glVertex3f(-134.5,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-104,0,-6.2);
    glVertex3f(-104,0,0);
    glVertex3f(-104,97.5,0);
    glVertex3f(-104,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97,0,-6.2);
    glVertex3f(-104,0,-6.2);
    glVertex3f(-104,97.5,-6.2);
    glVertex3f(-97,97.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-100,0,-6.2);
    glVertex3f(-104,0,0);
    glVertex3f(-104,97.5,0);
    glVertex3f(-100,97.5,-6.2);
    glEnd();
    //sebelah jendela kiri
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97,0,0);
    glVertex3f(-70,0,0);
    glVertex3f(-70,97.5,0);
    glVertex3f(-97,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-97,0,0);
    glVertex3f(-97,97.5,0);
    glVertex3f(-97,97.5,-6.2);
    glVertex3f(-97,0,-6.2);
    glEnd();

    //atribute 1
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(169.4,82.5,24.7);
    glVertex3f(169.4,82.5,10.5);
    glVertex3f(169.4,87.5,10.5);
    glVertex3f(169.4,87.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(169.4, 87.5, 24.7);
    glVertex3f(169.4,87.5,10.5);
    glVertex3f(171.5,97.5,13.5);
    glVertex3f(171.5,97.5,24.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(171.5,97.5,24.7);
    glVertex3f(171.5,97.5,13.5);
    glVertex3f(166.6,97.5,13.5);
    glVertex3f(166.6,97.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(171.5,97.5,24.2);
    glVertex3f(171.5,97.5,13.5);
    glVertex3f(166.6,97.5,13.5);
    glVertex3f(166.6,97.5,24.7);
    glEnd();

    //atribute 2
    glBegin(GL_QUADS);
    glColor3f(0.86, 0.86, 0.86);
    glVertex3f(169.4,82.5,10.5);
    glVertex3f(172.5,82.5,10.5);
    glVertex3f(172.5,87.5,10.5);
    glVertex3f(169.4,87.5,10.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.88, 0.88, 0.88);
    glVertex3f(169.4,87.5,10.5);
    glVertex3f(172.5,87.5,10.5);
    glVertex3f(174.7,97.5,13.5);
    glVertex3f(171.5,97.5,13.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(172.5,87.5,10.5);
    glVertex3f(172.5,87.5,-6.2);
    glVertex3f(174.7,97.5,-8.4);
    glVertex3f(174.7,97.5,13.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(172.5,82.5,10.5);
    glVertex3f(172.5,82.5,-6.2);
    glVertex3f(172.5,87.5,-6.2);
    glVertex3f(172.5,87.5,10.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(174.7,97.5,13.5);
    glVertex3f(174.7,97.5,-8.4);
    glVertex3f(166.2,97.5,0);
    glVertex3f(166.2,97.5,13.5);
    glEnd();

    //atribute 3
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(172.5,87.5,-6.2);
    glVertex3f(155.7,87.5,-6.2);
    glVertex3f(152.7,97.5,-8.4);
    glVertex3f(174.7,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(172.5,82.5,-6.2);
    glVertex3f(155.7,82.5,-6.2);
    glVertex3f(155.7,87.5,-6.2);
    glVertex3f(172.7,87.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(174.7,97.5,-8.4);
    glVertex3f(152.7,97.5,-8.4);
    glVertex3f(152.7,97.5,0);
    glVertex3f(166.3,97.5,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.86, 0.86, 0.86);
    glVertex3f(155.7,87.5,-6.2);
    glVertex3f(155.7,87.5,-3.1);
    glVertex3f(152.7,97.5,-5.2);
    glVertex3f(152.7,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.88d, 0.88, 0.88);
    glVertex3f(155.7,82.5,-6.2);
    glVertex3f(155.7,82.5,-3.1);
    glVertex3f(155.7,87.5,-3.1);
    glVertex3f(155.7,87.5,-6.2);
    glEnd();

    //atribute 4
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(155.7,97.5,-5.2);
    glVertex3f(144.5,97.5,-5.2);
    glVertex3f(144.5,97.5,0);
    glVertex3f(155.7,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(155.7,87.5,-3.1);
    glVertex3f(141.5,87.5,-3.1);
    glVertex3f(144.5,97.5,-5.2);
    glVertex3f(152.7,97.5,-5.2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(144.5,97.5,-8.5);
    glVertex3f(104,97.5,-8.5);
    glVertex3f(104,97.5,0);
    glVertex3f(144.5,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(141.5,87.5,-6.2);
    glVertex3f(100,87.5,-6.2);
    glVertex3f(104,97.5,-8.4);
    glVertex3f(144.5,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(141.5,82.5,-6.2);
    glVertex3f(97,82.5,-6.2);
    glVertex3f(97,87.5,-6.2);
    glVertex3f(141.5,87.5,-6.2);
    glEnd();

    //kiri
    //atribute 1
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-169.4,82.5,24.7);
    glVertex3f(-169.4,82.5,10.5);
    glVertex3f(-169.4,87.5,10.5);
    glVertex3f(-169.4,87.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-169.4, 87.5, 24.7);
    glVertex3f(-169.4,87.5,10.5);
    glVertex3f(-171.5,97.5,13.5);
    glVertex3f(-171.5,97.5,24.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-171.5,97.5,24.7);
    glVertex3f(-171.5,97.5,13.5);
    glVertex3f(-166.6,97.5,13.5);
    glVertex3f(-166.6,97.5,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-171.5,97.5,24.2);
    glVertex3f(-171.5,97.5,13.5);
    glVertex3f(-166.6,97.5,13.5);
    glVertex3f(-166.6,97.5,24.7);
    glEnd();

    //atribute 2
    glBegin(GL_QUADS);
    glColor3f(0.86, 0.86, 0.86);
    glVertex3f(-169.4,82.5,10.5);
    glVertex3f(-172.5,82.5,10.5);
    glVertex3f(-172.5,87.5,10.5);
    glVertex3f(-169.4,87.5,10.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.88, 0.88, 0.88);
    glVertex3f(-169.4,87.5,10.5);
    glVertex3f(-172.5,87.5,10.5);
    glVertex3f(-174.7,97.5,13.5);
    glVertex3f(-171.5,97.5,13.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-172.5,87.5,10.5);
    glVertex3f(-172.5,87.5,-6.2);
    glVertex3f(-174.7,97.5,-8.4);
    glVertex3f(-174.7,97.5,13.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-172.5,82.5,10.5);
    glVertex3f(-172.5,82.5,-6.2);
    glVertex3f(-172.5,87.5,-6.2);
    glVertex3f(-172.5,87.5,10.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-174.7,97.5,13.5);
    glVertex3f(-174.7,97.5,-8.4);
    glVertex3f(-166.2,97.5,0);
    glVertex3f(-166.2,97.5,13.5);
    glEnd();

    //atribute 3
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-172.5,87.5,-6.2);
    glVertex3f(-155.7,87.5,-6.2);
    glVertex3f(-152.7,97.5,-8.4);
    glVertex3f(-174.7,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-172.5,82.5,-6.2);
    glVertex3f(-155.7,82.5,-6.2);
    glVertex3f(-155.7,87.5,-6.2);
    glVertex3f(-172.7,87.5,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-174.7,97.5,-8.4);
    glVertex3f(-152.7,97.5,-8.4);
    glVertex3f(-152.7,97.5,0);
    glVertex3f(-166.3,97.5,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.86, 0.86, 0.86);
    glVertex3f(-155.7,87.5,-6.2);
    glVertex3f(-155.7,87.5,-3.1);
    glVertex3f(-152.7,97.5,-5.2);
    glVertex3f(-152.7,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.88d, 0.88, 0.88);
    glVertex3f(-155.7,82.5,-6.2);
    glVertex3f(-155.7,82.5,-3.1);
    glVertex3f(-155.7,87.5,-3.1);
    glVertex3f(1-55.7,87.5,-6.2);
    glEnd();

    //atribute 4
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-155.7,97.5,-5.2);
    glVertex3f(-144.5,97.5,-5.2);
    glVertex3f(-144.5,97.5,0);
    glVertex3f(-155.7,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-155.7,87.5,-3.1);
    glVertex3f(-141.5,87.5,-3.1);
    glVertex3f(-144.5,97.5,-5.2);
    glVertex3f(-152.7,97.5,-5.2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-144.5,97.5,-8.4);
    glVertex3f(-104,97.5,-8.4);
    glVertex3f(-104,97.5,0);
    glVertex3f(-144.5,97.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-141.5,87.5,-6.2);
    glVertex3f(-100,87.5,-6.2);
    glVertex3f(-104,97.5,-8.4);
    glVertex3f(-144.5,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-141.5,82.5,-6.2);
    glVertex3f(-97,82.5,-6.2);
    glVertex3f(-97,87.5,-6.2);
    glVertex3f(-141.5,87.5,-6.2);
    glEnd();

    //depan kanan
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(70,0,0);
    glVertex3f(70,0,-50);
    glVertex3f(70,87.5,-50);
    glVertex3f(70,87.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(70,0,-50);
    glVertex3f(25,0,-80);
    glVertex3f(25,87.5,-80);
    glVertex3f(70,87.5,-50);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(25,0,-80);
    glVertex3f(0,0,-80);
    glVertex3f(0,87.5,-80);
    glVertex3f(25,87.5,-80);
    glEnd();

    //depan kiri
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-70,0,0);
    glVertex3f(-70,0,-50);
    glVertex3f(-70,87.5,-50);
    glVertex3f(-70,87.5,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-70,0,-50);
    glVertex3f(-25,0,-80);
    glVertex3f(-25,87.5,-80);
    glVertex3f(-70,87.5,-50);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-25,0,-80);
    glVertex3f(0,0,-80);
    glVertex3f(0,87.5,-80);
    glVertex3f(-25,87.5,-80);
    glEnd();

    //atribute atas kanan
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(72.8,92.5,0);
    glVertex3f(100,97.5,-4.2);
    glVertex3f(100,92.5,-61.8);
    glVertex3f(72.8,92.5,-49.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(72.8,92.5,-49.7);
    glVertex3f(100,92.5,-61.8);
    glVertex3f(33.9,92.5,-108.5);
    glVertex3f(26,92.5,-81.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(26,92.5,-81.9);
    glVertex3f(33.9,92.5,-108.5);
    glVertex3f(0,92.5,-108.5);
    glVertex3f(0,92.5,-81.9);
    glEnd();

     //atribute atas kiri
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-72.8,92.5,0);
    glVertex3f(-100,97.5,-4.2);
    glVertex3f(-100,92.5,-61.8);
    glVertex3f(-72.8,92.5,-49.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-72.8,92.5,-49.7);
    glVertex3f(-100,92.5,-61.8);
    glVertex3f(-33.9,92.5,-108.5);
    glVertex3f(-26,92.5,-81.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-26,92.5,-81.9);
    glVertex3f(-33.9,92.5,-108.5);
    glVertex3f(-0,92.5,-108.5);
    glVertex3f(-0,92.5,-81.9);
    glEnd();

    //garis 1 kanan
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(100,87.5,-6.2);
    glVertex3f(100,87.5,-62.5);
    glVertex3f(104,97.5,-63.1);
    glVertex3f(104,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(100,82.5,-6.2);
    glVertex3f(100,82.5,-62.5);
    glVertex3f(104,97.5,-63.1);
    glVertex3f(104,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(104,97.5,0);
    glVertex3f(104,97.5,-63.1);
    glVertex3f(100,97.5,-61.8);
    glVertex3f(100,97.5,-8.0);
    glEnd();
    //garis 2 kanan
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(100,87.5,-62.2);
    glVertex3f(33.5,87.5,-107.4);
    glVertex3f(34.8,97.5,-111.4);
    glVertex3f(104,97.5,-63.1);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(100,82.5,-62.2);
    glVertex3f(33.5,82.5,-107.4);
    glVertex3f(33.5,87.5,-107.4);
    glVertex3f(100,87.5,-62.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(104,97.5,-63.1);
    glVertex3f(34.8,97.5,-111.4);
    glVertex3f(33.9,97.5,-108.8);
    glVertex3f(100,97.5,-61.8);
    glEnd();
     //garis 3 kanan
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(33.5,87.5,-107.4);
    glVertex3f(0,87.5,-107.4);
    glVertex3f(0,97.5,-111.4);
    glVertex3f(34.8,97.5,-111.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(33.5,82.5,-107.4);
    glVertex3f(0,82.5,-107.4);
    glVertex3f(0,87.5,-107.4);
    glVertex3f(33.5,87.5,-107.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(34.8,97.5,-111.4);
    glVertex3f(0,97.5,-111.4);
    glVertex3f(0,97.5,-108.5);
    glVertex3f(33.9,97.5,-108.5);
    glEnd();

    //garis 1 kiri
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-100,87.5,-6.2);
    glVertex3f(-100,87.5,-62.5);
    glVertex3f(-104,97.5,-63.1);
    glVertex3f(-104,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-100,82.5,-6.2);
    glVertex3f(-100,82.5,-62.5);
    glVertex3f(-104,97.5,-63.1);
    glVertex3f(-104,97.5,-8.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-104,97.5,0);
    glVertex3f(-104,97.5,-63.1);
    glVertex3f(-100,97.5,-61.8);
    glVertex3f(-100,97.5,-8.0);
    glEnd();
    //garis 2 kiri
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-100,87.5,-62.2);
    glVertex3f(-33.5,87.5,-107.4);
    glVertex3f(-34.8,97.5,-111.4);
    glVertex3f(-104,97.5,-63.1);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-100,82.5,-62.2);
    glVertex3f(-33.5,82.5,-107.4);
    glVertex3f(-33.5,87.5,-107.4);
    glVertex3f(-100,87.5,-62.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-104,97.5,-63.1);
    glVertex3f(-34.8,97.5,-111.4);
    glVertex3f(-33.9,97.5,-108.8);
    glVertex3f(-100,97.5,-61.8);
    glEnd();
     //garis 3 kiri
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(-33.5,87.5,-107.4);
    glVertex3f(0,87.5,-107.4);
    glVertex3f(0,97.5,-111.4);
    glVertex3f(-34.8,97.5,-111.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-33.5,82.5,-107.4);
    glVertex3f(-0,82.5,-107.4);
    glVertex3f(-0,87.5,-107.4);
    glVertex3f(-33.5,87.5,-107.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-34.8,97.5,-111.4);
    glVertex3f(0,97.5,-111.4);
    glVertex3f(0,97.5,-108.5);
    glVertex3f(-33.9,97.5,-108.5);
    glEnd();

    //jendelakiri
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(131.5, 20.6, -0.5);
    glVertex3f(107, 20.6, -0.5);
    glVertex3f(107, 80, -0.5);
    glVertex3f(131.5, 80, -0.5);
    glEnd();
     //jendelakanan
    glBegin(GL_QUADS);
    glColor3f(0.14, 0.16, 0.55);
    glVertex3f(-131.5, 20.6, -0.5);
    glVertex3f(-107, 20.6, -0.5);
    glVertex3f(-107, 80, -0.5);
    glVertex3f(-131.5, 80, -0.5);
    glEnd();

    //pintukiri
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(15, 0, -80.5);
    glVertex3f(0, 0, -80.5);
    glVertex3f(0, 60, -80.5);
    glVertex3f(15, 60, -80.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(13, 20, -80.6);
    glVertex3f(0, 20, -80.6);
    glVertex3f(0, 55, -80.6);
    glVertex3f(13, 55, -80.6);
    glEnd();
    //pintukanan
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(-15, 0, -80.5);
    glVertex3f(2, 0, -80.5);
    glVertex3f(2, 60, -80.5);
    glVertex3f(-15, 60, -80.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(-13, 20, -80.6);
    glVertex3f(-2, 20, -80.6);
    glVertex3f(-2, 55, -80.6);
    glVertex3f(-13, 55, -80.6);
    glEnd();

    //jendela pintu kanan
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(32, 20, -80.5);
    glVertex3f(18, 20, -80.5);
    glVertex3f(18, 55, -80.5);
    glVertex3f(32, 55, -80.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(30, 22, -80.6);
    glVertex3f(20, 22, -80.6);
    glVertex3f(20, 53, -80.6);
    glVertex3f(30, 53, -80.6);
    glEnd();
    //jendela pintu kanan
    glBegin(GL_QUADS);
    glColor3f(00.14, 0.16, 0.55);
    glVertex3f(-32, 20, -80.5);
    glVertex3f(-18, 20, -80.5);
    glVertex3f(-18, 55, -80.5);
    glVertex3f(-32, 55, -80.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(-30, 22, -80.6);
    glVertex3f(-20, 22, -80.6);
    glVertex3f(-20, 53, -80.6);
    glVertex3f(-30, 53, -80.6);
    glEnd();

    //jendela kedua kanan
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(70, 20, -50.5);
    glVertex3f(35, 20, -80.5);
    glVertex3f(35, 40, -80.5);
    glVertex3f(70, 40, -50.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(68, 22, -50.8);
    glVertex3f(37, 22, -80.6);
    glVertex3f(37, 38, -80.6);
    glVertex3f(68, 38, -50.8);
    glEnd();
    //jendela kedua kiri
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(-70, 20, -50.5);
    glVertex3f(-35, 20, -80.5);
    glVertex3f(-35, 40, -80.5);
    glVertex3f(-70, 40, -50.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.78, 0.96, 0.96);
    glVertex3f(-68, 22, -50.8);
    glVertex3f(-37, 22, -80.6);
    glVertex3f(-37, 38, -80.6);
    glVertex3f(-68, 38, -50.8);
    glEnd();

    //atas kanan 1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(72.8, 92.5, 0);
    glVertex3f(72.8, 92.5, -49.7);
    glVertex3f(72.8, 112.5, -49.7);
    glVertex3f(72.8, 112.5, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(77.8, 112.5, -3.1);
    glVertex3f(77.8, 112.5, -52.9);
    glVertex3f(80.3, 125, -53.5);
    glVertex3f(80.3, 125, -4.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(80.3, 125, 0);
    glVertex3f(80.3, 125, -53.5);
    glVertex3f(72.8, 125, -52.5);
    glVertex3f(72.8, 125, 0);
    glEnd();
    //atas kanan 2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(72.8, 92.5, -49.7);
    glVertex3f(26, 92.5, -81.9);
    glVertex3f(26, 112.5, -81.9);
    glVertex3f(72.8, 112.5, -49.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(77.8, 112.5, -5.2);
    glVertex3f(27, 112.5, -86);
    glVertex3f(27.9, 125, -88.5);
    glVertex3f(80.3, 125, -53.5);
    glEnd();
    //atas kanan 3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(26, 92.5, -81.9);
    glVertex3f(0, 92.5, -81.9);
    glVertex3f(0, 112.5, -81.9);
    glVertex3f(26, 112.5, -81.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(27, 112.5, -86);
    glVertex3f(0, 112.5, -86);
    glVertex3f(0, 125, -88.5);
    glVertex3f(27.9, 125, -88.5);
    glEnd();

     //atas kiri 1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-72.8, 92.5, 0);
    glVertex3f(-72.8, 92.5, -49.7);
    glVertex3f(-72.8, 112.5, -49.7);
    glVertex3f(-72.8, 112.5, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-77.8, 112.5, -3.1);
    glVertex3f(-77.8, 112.5, -52.9);
    glVertex3f(-80.3, 125, -53.5);
    glVertex3f(-80.3, 125, -4.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-80.3, 125, 0);
    glVertex3f(-80.3, 125, -53.5);
    glVertex3f(-72.8, 125, -52.5);
    glVertex3f(-72.8, 125, 0);
    glEnd();
    //atas kiri 2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-72.8, 92.5, -49.7);
    glVertex3f(-26, 92.5, -81.9);
    glVertex3f(-26, 112.5, -81.9);
    glVertex3f(-72.8, 112.5, -49.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-77.8, 112.5, -5.2);
    glVertex3f(-27, 112.5, -86);
    glVertex3f(-27.9, 125, -88.5);
    glVertex3f(-80.3, 125, -53.5);
    glEnd();
    //atas kiri 3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-26, 92.5, -81.9);
    glVertex3f(0, 92.5, -81.9);
    glVertex3f(0, 112.5, -81.9);
    glVertex3f(-26, 112.5, -81.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-27, 112.5, -86);
    glVertex3f(0, 112.5, -86);
    glVertex3f(0, 125, -88.5);
    glVertex3f(-27.9, 125, -88.5);
    glEnd();

    //atastingkat kanan
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(72.8, 125, -4.4);
    glVertex3f(72.8, 125, -46.7);
    glVertex3f(72.8, 143.5, -46.7);
    glVertex3f(72.8, 143.5, -4.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(72.8, 125, -52.7);
    glVertex3f(29, 125, -81.9);
    glVertex3f(29, 143.5, -81.9);
    glVertex3f(72.8, 143.5, -52.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(23, 125, -81.9);
    glVertex3f(0, 125, -81.9);
    glVertex3f(0, 143.5, -81.9);
    glVertex3f(23, 143.5, -81.9);
    glEnd();

    //atastingkat kiri
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-72.8, 125, -4.4);
    glVertex3f(-72.8, 125, -46.7);
    glVertex3f(-72.8, 143.5, -46.7);
    glVertex3f(-72.8, 143.5, -4.4);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-72.8, 125, -52.7);
    glVertex3f(-29, 125, -81.9);
    glVertex3f(-29, 143.5, -81.9);
    glVertex3f(-72.8, 143.5, -52.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-23, 125, -81.9);
    glVertex3f(0, 125, -81.9);
    glVertex3f(0, 143.5, -81.9);
    glVertex3f(-23, 143.5, -81.9);
    glEnd();

    //bates atas tingkat kanan 1
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(75.8, 125, -46.7);
    glVertex3f(75.8, 125, -52.7);
    glVertex3f(75.8, 147, -52.7);
    glVertex3f(75.8, 147, -46.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(76.8, 147, -45.7);
    glVertex3f(76.8, 147, -53.7);
    glVertex3f(76.8, 151, -53.7);
    glVertex3f(76.8, 151, -45.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(75.8, 125, -52.7);
    glVertex3f(69.8, 125, -52.7);
    glVertex3f(69.8, 147, -52.7);
    glVertex3f(75.8, 147, -52.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(76.8, 147, -53.7);
    glVertex3f(68.8, 147, -53.7);
    glVertex3f(68.8, 151, -53.7);
    glVertex3f(76.8, 151, -53.7);
    glEnd();
    //bates atas tingkat kanan 2
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(29, 125, -84.9);
    glVertex3f(29, 125, -78.9);
    glVertex3f(29, 147, -78.9);
    glVertex3f(29, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(30, 147, -85.9);
    glVertex3f(30, 147, -77.9);
    glVertex3f(30, 151, -77.9);
    glVertex3f(30, 151, -85.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(29, 125, -84.9);
    glVertex3f(23, 125, -84.9);
    glVertex3f(23, 147, -84.9);
    glVertex3f(29, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(30, 147, -85.9);
    glVertex3f(22, 147, -85.9);
    glVertex3f(22, 151, -85.9);
    glVertex3f(30, 151, -85.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(23, 125, -84.9);
    glVertex3f(23, 125, -78.9);
    glVertex3f(23, 147, -78.9);
    glVertex3f(23, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(22, 147, -85.9);
    glVertex3f(22, 147, -77.9);
    glVertex3f(22, 151, -77.9);
    glVertex3f(22, 151, -85.9);
    glEnd();

    //bates atas tingkat kiri 1
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-75.8, 125, -46.7);
    glVertex3f(-75.8, 125, -52.7);
    glVertex3f(-75.8, 147, -52.7);
    glVertex3f(-75.8, 147, -46.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-76.8, 147, -45.7);
    glVertex3f(-76.8, 147, -53.7);
    glVertex3f(-76.8, 151, -53.7);
    glVertex3f(-76.8, 151, -45.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-75.8, 125, -52.7);
    glVertex3f(-69.8, 125, -52.7);
    glVertex3f(-69.8, 147, -52.7);
    glVertex3f(-75.8, 147, -52.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-76.8, 147, -53.7);
    glVertex3f(-68.8, 147, -53.7);
    glVertex3f(-68.8, 151, -53.7);
    glVertex3f(-76.8, 151, -53.7);
    glEnd();
    //bates atas tingkat kiri 2
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-29, 125, -84.9);
    glVertex3f(-29, 125, -78.9);
    glVertex3f(-29, 147, -78.9);
    glVertex3f(-29, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-30, 147, -85.9);
    glVertex3f(-30, 147, -77.9);
    glVertex3f(-30, 151, -77.9);
    glVertex3f(-30, 151, -85.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-29, 125, -84.9);
    glVertex3f(-23, 125, -84.9);
    glVertex3f(-23, 147, -84.9);
    glVertex3f(-29, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-30, 147, -85.9);
    glVertex3f(-22, 147, -85.9);
    glVertex3f(-22, 151, -85.9);
    glVertex3f(-30, 151, -85.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-23, 125, -84.9);
    glVertex3f(-23, 125, -78.9);
    glVertex3f(-23, 147, -78.9);
    glVertex3f(-23, 147, -84.9);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-22, 147, -85.9);
    glVertex3f(-22, 147, -77.9);
    glVertex3f(-22, 151, -77.9);
    glVertex3f(-22, 151, -85.9);
    glEnd();


    //bangunan samping tingkat
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(166.3,97.5,24.7);
    glVertex3f(166.3,97.5,6.2);
    glVertex3f(166.3,195,6.2);
    glVertex3f(166.3,195,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(166.3,97.5,6.2);
    glVertex3f(171.5,97.5,6.2);
    glVertex3f(171.5,195,6.2);
    glVertex3f(166.3,195,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(171.5,97.5,6.2);
    glVertex3f(171.5,97.5,-5.2);
    glVertex3f(171.5,195,-5.2);
    glVertex3f(171.5,195,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(171.5,97.5,-5.2);
    glVertex3f(160,97.5,-5.2);
    glVertex3f(160,195,-5.2);
    glVertex3f(171.5,195,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(160,97.5,-5.2);
    glVertex3f(160,97.5,0);
    glVertex3f(160,195,0);
    glVertex3f(160,195,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(160,97.5,0);
    glVertex3f(141.5,97.5,0);
    glVertex3f(141.5,195,0);
    glVertex3f(160,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(141.5,97.5,-6.2);
    glVertex3f(141.5,97.5,0);
    glVertex3f(141.5,195,0);
    glVertex3f(141.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(141.5,97.5,-6.2);
    glVertex3f(134.5,97.5,-6.2);
    glVertex3f(134.5,195,-6.2);
    glVertex3f(141.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(134.5,97.5,-6.2);
    glVertex3f(134.5,97.5,0);
    glVertex3f(134.5,195,0);
    glVertex3f(134.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(134.5,97.5,0);
    glVertex3f(104,97.5,0);
    glVertex3f(104,195,0);
    glVertex3f(134.5,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(104,97.5,-6.2);
    glVertex3f(104,97.5,0);
    glVertex3f(104,195,0);
    glVertex3f(104,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97,97.5,-6.2);
    glVertex3f(104,97.5,-6.2);
    glVertex3f(104,195,-6.2);
    glVertex3f(97,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(100,97.5,-6.2);
    glVertex3f(104,97.5,0);
    glVertex3f(104,195,0);
    glVertex3f(100,195,-6.2);
    glEnd();
    //sebelah jendela kanan tingkat
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(97,97.5,0);
    glVertex3f(70,97.5,0);
    glVertex3f(70,195,0);
    glVertex3f(97,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(97,97.5,0);
    glVertex3f(97,195,0);
    glVertex3f(97,195,-6.2);
    glVertex3f(97,97.5,-6.2);
    glEnd();

    //bangunan samping kiri tingkat
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-166.3,97.5,24.7);
    glVertex3f(-166.3,97.5,6.2);
    glVertex3f(-166.3,195,6.2);
    glVertex3f(-166.3,195,24.7);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-166.3,97.5,6.2);
    glVertex3f(-171.5,97.5,6.2);
    glVertex3f(-171.5,195,6.2);
    glVertex3f(-166.3,195,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-171.5,97.5,6.2);
    glVertex3f(-171.5,97.5,-5.2);
    glVertex3f(-171.5,195,-5.2);
    glVertex3f(-171.5,195,6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-171.5,97.5,-5.2);
    glVertex3f(-160,97.5,-5.2);
    glVertex3f(-160,195,-5.2);
    glVertex3f(-171.5,195,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-160,97.5,-5.2);
    glVertex3f(-160,97.5,0);
    glVertex3f(-160,195,0);
    glVertex3f(-160,195,-5.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-160,97.5,0);
    glVertex3f(-141.5,97.5,0);
    glVertex3f(-141.5,195,0);
    glVertex3f(-160,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-141.5,97.5,-6.2);
    glVertex3f(-141.5,97.5,0);
    glVertex3f(-141.5,195,0);
    glVertex3f(-141.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-141.5,97.5,-6.2);
    glVertex3f(-134.5,97.5,-6.2);
    glVertex3f(-134.5,195,-6.2);
    glVertex3f(-141.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-134.5,97.5,-6.2);
    glVertex3f(-134.5,97.5,0);
    glVertex3f(-134.5,195,0);
    glVertex3f(-134.5,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-134.5,97.5,0);
    glVertex3f(-104,97.5,0);
    glVertex3f(-104,195,0);
    glVertex3f(-134.5,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-104,97.5,-6.2);
    glVertex3f(-104,97.5,0);
    glVertex3f(-104,195,0);
    glVertex3f(-104,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97,97.5,-6.2);
    glVertex3f(-104,97.5,-6.2);
    glVertex3f(-104,195,-6.2);
    glVertex3f(-97,195,-6.2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-100,97.5,-6.2);
    glVertex3f(-104,97.5,0);
    glVertex3f(-104,195,0);
    glVertex3f(-100,195,-6.2);
    glEnd();
    //sebelah jendela kiri tingkat
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-97,97.5,0);
    glVertex3f(-70,97.5,0);
    glVertex3f(-70,195,0);
    glVertex3f(-97,195,0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-97,97.5,0);
    glVertex3f(-97,195,0);
    glVertex3f(-97,195,-6.2);
    glVertex3f(-97,97.5,-6.2);
    glEnd();

    //jendelakanantingkat
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(131.5, 117.5, -0.5);
    glVertex3f(107, 117.5, -0.5);
    glVertex3f(107, 177.5, -0.5);
    glVertex3f(131.5, 177.5, -0.5);
    glEnd();
    //jendelakiritingkat
    glBegin(GL_QUADS);
    glColor3f(0.08, 0.04, 0.01);
    glVertex3f(-131.5, 117.5, -0.5);
    glVertex3f(-107, 117.5, -0.5);
    glVertex3f(-107, 177.5, -0.5);
    glVertex3f(-131.5, 177.5, -0.5);
    glEnd();


    //belakangtembok
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(70,97.5,0);
    glVertex3f(70,195,0);
    glVertex3f(-70,195,0);
    glVertex3f(-70,97.5,0);
    glEnd();


    //KANAN
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(166.3, 0, 24.7);
    glVertex3f(166.3, 0, 200);
    glVertex3f(166.3, 195, 200);
    glVertex3f(166.3, 195, 24.7);
    glEnd();
     //KIRI
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-166.3, 0, 24.7);
    glVertex3f(-166.3, 0, 200);
    glVertex3f(-166.3, 195, 200);
    glVertex3f(-166.3, 195, 24.7);
    glEnd();
    //BELAKANG
    glBegin(GL_QUADS);
    glColor3f(0.90, 0.90, 0.90);
    glVertex3f(166.3, 0, 200);
    glVertex3f(166.3, 195, 200);
    glVertex3f(-166.3, 195, 200);
    glVertex3f(-166.3, 0, 200);
    glEnd();
    //TUTUP
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(166.3, 195, 200);
    glVertex3f(166.3, 195, 0);
    glVertex3f(-166.3, 195, 0);
    glVertex3f(-166.3, 195, 200);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(0, 125, 0);
    glVertex3f(0, 125, -50);
    glVertex3f(72.8, 125, -50);
    glVertex3f(72.8, 125, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(0, 125, -50);
    glVertex3f(0, 125, -81.9);
    glVertex3f(29, 125, -78.9);
    glVertex3f(72.8, 125, -50);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(0, 125, 0);
    glVertex3f(0, 125, -50);
    glVertex3f(-72.8, 125, -50);
    glVertex3f(-72.8, 125, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(0, 125, -50);
    glVertex3f(0, 125, -81.9);
    glVertex3f(-29, 125, -78.9);
    glVertex3f(-72.8, 125, -50);
    glEnd();

    //lantai depan atas
    glBegin(GL_POLYGON);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(100, 03.75,0);
    glVertex3f(100, 03.75,-62.5);
    glVertex3f(33.5, 03.75,-107.464);
    glVertex3f(0, 03.75,-107.464);
    glVertex3f(0, 03.75,0);
    glEnd();
    //tutupan lantai 1
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(100, 0,0);
    glVertex3f(100, 0,-62.5);
    glVertex3f(100, 03.75,-62.5);
    glVertex3f(100, 03.75,0);
    glEnd();
    //tutupan lantai 2
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(100, 0,-62.5);
    glVertex3f(33.5, 0,-107.464);
    glVertex3f(33.5, 03.75,-107.464);
    glVertex3f(100, 03.75,-62.5);
    glEnd();
    //tutupan lantai 3
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(33.5, 0,-107.464);
    glVertex3f(0, 0,-107.464);
    glVertex3f(0, 03.75,-107.464);
    glVertex3f(33.5, 03.75,-107.464);
    glEnd();

    //lantai depan atas
    glBegin(GL_POLYGON);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-100, 03.75,0);
    glVertex3f(-100, 03.75,-62.5);
    glVertex3f(-33.5, 03.75,-107.464);
    glVertex3f(0, 03.75,-107.464);
    glVertex3f(0, 03.75,0);
    glEnd();
    //tutupan lantai 1
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-100, 0,0);
    glVertex3f(-100, 0,-62.5);
    glVertex3f(-100, 03.75,-62.5);
    glVertex3f(-100, 03.75,0);
    glEnd();
    //tutupan lantai 2
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-100, 0,-62.5);
    glVertex3f(-33.5, 0,-107.464);
    glVertex3f(-33.5, 03.75,-107.464);
    glVertex3f(-100, 03.75,-62.5);
    glEnd();
    //tutupan lantai 3
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.98, 0.98);
    glVertex3f(-33.5, 0,-107.464);
    glVertex3f(0, 0,-107.464);
    glVertex3f(0, 03.75,-107.464);
    glVertex3f(-33.5, 03.75,-107.464);
    glEnd();

    //lantai dalam
    glBegin(GL_POLYGON);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(166.3, 3.75, 0);
    glVertex3f(-166.3, 3.75, 0);
    glVertex3f(-166.3, 3.75, 109.75);
    glVertex3f(166.3, 3.75, 109.75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.99, 0.99, 0.99);
    glVertex3f(-166.298, 03.75,109.75);
    glVertex3f(-166.298, 03.75,0);
    glVertex3f(0, 03.75,0);
    glVertex3f(0, 03.75,109.75);
    glEnd();



    ground();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y){
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera(){
    if (motion.Forward){
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward){
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left){
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right){
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik){
        terbang -= 2.0;
    }
    if (motion.Turun){
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 0.5;
        break;
    case '4':
        x_geser -= 0.5;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
        z_geser += 0.5;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM RUMAH WALIKOTA");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}
