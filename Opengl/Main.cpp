#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 2
//  Aditya Rangga Kurnianto (672020134)
//  Syahreza Triadhana Marsudi (672020135)
//  Irvan Ardhi Hidayat (672020138)
//  Risky Artha Rama Putra (672020288)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 1500, terbang = -300;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
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

void tanah() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f);
    glVertex3f(-1000.0, 100.0, -1000.0);
    glVertex3f(1000.0, 100.0, -1000.0);
    glVertex3f(1000.0, 100.0, 1000.0);
    glVertex3f(-1000.0, 100.0, 1000.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.39, 0.24, 0.12);
    glVertex3f(-1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, 1000.0);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.39, 0.24, 0.12);
    glVertex3f(1000.0, 0, -1000.0);
    glVertex3f(1000.0, 100.0, -1000.0);
    glVertex3f(1000.0, 100.0, 1000.0);
    glVertex3f(1000.0, 0, 1000.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.39, 0.24, 0.12);
    glVertex3f(-1000.0, 0, -1000.0);
    glVertex3f(-1000.0, 100.0, -1000.0);
    glVertex3f(-1000.0, 100.0, 1000.0);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.39, 0.24, 0.12);
    glVertex3f(-1000.0, 0, -1000.0);
    glVertex3f(-1000.0, 100.0, -1000.0);
    glVertex3f(1000.0, 100.0, -1000.0);
    glVertex3f(1000.0, 0, -1000.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.39, 0.24, 0.12);
    glVertex3f(-1000.0, 0, 1000.0);
    glVertex3f(-1000.0, 100.0, 1000.0);
    glVertex3f(1000.0, 100.0, 1000.0);
    glVertex3f(1000.0, 0, 1000.0);
    glEnd();


}

void beton() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-850.0, 200.0, -850.0);
    glVertex3f(850.0, 200.0, -850.0);
    glVertex3f(850.0, 200.0, 850.0);
    glVertex3f(-850.0, 200.0, 850.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-850.0, 100.0, -850.0);
    glVertex3f(850.0, 100.0, -850.0);
    glVertex3f(850.0, 100.0, 850.0);
    glVertex3f(-850.0, 100.0, 850.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(850.0, 100.0, -850.0);
    glVertex3f(850.0, 200.0, -850.0);
    glVertex3f(850.0, 200.0, 850.0);
    glVertex3f(850.0, 100.0, 850.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-850.0, 100.0, -850.0);
    glVertex3f(-850.0, 200.0, -850.0);
    glVertex3f(-850.0, 200.0, 850.0);
    glVertex3f(-850.0, 100.0, 850.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-850.0, 100.0, -850.0);
    glVertex3f(-850.0, 200.0, -850.0);
    glVertex3f(850.0, 200.0, -850.0);
    glVertex3f(850.0, 100.0, -850.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-850.0, 100.0, 850.0);
    glVertex3f(-850.0, 200.0, 850.0);
    glVertex3f(850.0, 200.0, 850.0);
    glVertex3f(850.0, 100.0, 850.0);
}

void building() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-600.0, 400.0, -600.0);
    glVertex3f(600.0, 400.0, -600.0);
    glVertex3f(600.0, 400.0, 600.0);
    glVertex3f(-600.0, 400.0, 600.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-600.0, 200.0, -600.0);
    glVertex3f(600.0, 200.0, -600.0);
    glVertex3f(600.0, 200.0, 600.0);
    glVertex3f(-600.0, 200.0, 600.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(600.0, 200.0, -600.0);
    glVertex3f(600.0, 600.0, -600.0);
    glVertex3f(600.0, 600.0, 600.0);
    glVertex3f(600.0, 200.0, 600.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-600.0, 200.0, -600.0);
    glVertex3f(-600.0, 600.0, -600.0);
    glVertex3f(-600.0, 600.0, 600.0);
    glVertex3f(-600.0, 200.0, 600.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-600.0, 200.0, -600.0);
    glVertex3f(-600.0, 600.0, -600.0);
    glVertex3f(600.0, 600.0, -600.0);
    glVertex3f(600.0, 200.0, -600.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-600.0, 200.0, 600.0);
    glVertex3f(-600.0, 600.0, 600.0);
    glVertex3f(600.0, 600.0, 600.0);
    glVertex3f(600.0, 200.0, 600.0);
    glEnd();
}
void lantai2() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-700.0, 620.0, -700.0);
    glVertex3f(700.0, 620.0, -700.0);
    glVertex3f(700.0, 620.0, 700.0);
    glVertex3f(-700.0, 620.0, 700.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-700.0, 600.0, -700.0);
    glVertex3f(700.0, 600.0, -700.0);
    glVertex3f(700.0, 600.0, 700.0);
    glVertex3f(-700.0, 600.0, 700.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(700.0, 600.0, -700.0);
    glVertex3f(700.0, 620.0, -700.0);
    glVertex3f(700.0, 620.0, 700.0);
    glVertex3f(700.0, 600.0, 700.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-700.0, 600.0, -700.0);
    glVertex3f(-700.0, 620.0, -700.0);
    glVertex3f(-700.0, 620.0, 700.0);
    glVertex3f(-700.0, 600.0, 700.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-700.0, 600.0, -700.0);
    glVertex3f(-700.0, 620.0, -700.0);
    glVertex3f(700.0, 620.0, -700.0);
    glVertex3f(700.0, 600.0, -700.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-700.0, 600.0, 700.0);
    glVertex3f(-700.0, 620.0, 700.0);
    glVertex3f(700.0, 620.0, 700.0);
    glVertex3f(700.0, 600.0, 700.0);
    glEnd();
}
void bangunan2() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-500.0, 1000.0, -500.0);
    glVertex3f(500.0, 1000.0, -500.0);
    glVertex3f(500.0, 1000.0, 500.0);
    glVertex3f(-500.0, 1000.0, 500.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-500.0, 620.0, -500.0);
    glVertex3f(500.0, 620.0, -500.0);
    glVertex3f(500.0, 620.0, 500.0);
    glVertex3f(-500.0, 620.0, 500.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(500.0, 620.0, -500.0);
    glVertex3f(500.0, 1000.0, -500.0);
    glVertex3f(500.0, 1000.0, 500.0);
    glVertex3f(500.0, 620.0, 500.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-500.0, 620.0, -500.0);
    glVertex3f(-500.0, 1000.0, -500.0);
    glVertex3f(-500.0, 1000.0, 500.0);
    glVertex3f(-500.0, 620.0, 500.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-500.0, 620.0, -500.0);
    glVertex3f(-500.0, 1000.0, -500.0);
    glVertex3f(500.0, 1000.0, -500.0);
    glVertex3f(500.0, 620.0, -500.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-500.0, 620.0, 500.0);
    glVertex3f(-500.0, 1000.0, 500.0);
    glVertex3f(500.0, 1000.0, 500.0);
    glVertex3f(500.0, 620.0, 500.0);
    glEnd();
}
void atap1() {
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-450.0, 1100.0, -450.0);
    glVertex3f(450.0, 1100.0, -450.0);
    glVertex3f(450.0, 1100.0, 450.0);
    glVertex3f(-450.0, 1100.0, 450.0);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-700.0, 1000.0, -700.0);
    glVertex3f(700.0, 1000.0, -700.0);
    glVertex3f(700.0, 1000.0, 700.0);
    glVertex3f(-700.0, 1000.0, 700.0);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(700.0, 1000.0, -700.0);
    glVertex3f(450.0, 1100.0, -450.0);
    glVertex3f(450.0, 1100.0, 450.0);
    glVertex3f(700.0, 1000.0, 700.0);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-700.0, 1000.0, -700.0);
    glVertex3f(-450.0, 1100.0, -450.0);
    glVertex3f(-450.0, 1100.0, 450.0);
    glVertex3f(-700.0, 1000.0, 700.0);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-700.0, 1000.0, -700.0);
    glVertex3f(-450.0, 1100.0, -450.0);
    glVertex3f(450.0, 1100.0, -450.0);
    glVertex3f(700.0, 1000.0, -700.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-600.0, 1000.0, 600.0);
    glVertex3f(-450.0, 1100.0, 450.0);
    glVertex3f(450.0, 1100.0, 450.0);
    glVertex3f(600.0, 1000.0, 600.0);
    glEnd();
}

void lantai3() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-550.0, 1120.0, -550.0);
    glVertex3f(550.0, 1120.0, -550.0);
    glVertex3f(550.0, 1120.0, 550.0);
    glVertex3f(-550.0, 1120.0, 550.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-550.0, 1100.0, -550.0);
    glVertex3f(550.0, 1100.0, -550.0);
    glVertex3f(550.0, 1100.0, 550.0);
    glVertex3f(-550.0, 1100.0, 550.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(550.0, 1100.0, -550.0);
    glVertex3f(550.0, 1120.0, -550.0);
    glVertex3f(550.0, 1120.0, 550.0);
    glVertex3f(550.0, 1100.0, 550.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-550.0, 1100.0, -550.0);
    glVertex3f(-550.0, 1120.0, -550.0);
    glVertex3f(-550.0, 1120.0, 550.0);
    glVertex3f(-550.0, 1100.0, 550.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-550.0, 1100.0, -550.0);
    glVertex3f(-550.0, 1120.0, -550.0);
    glVertex3f(550.0, 1120.0, -550.0);
    glVertex3f(550.0, 1100.0, -550.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-550.0, 1100.0, 550.0);
    glVertex3f(-550.0, 1120.0, 550.0);
    glVertex3f(550.0, 1120.0, 550.0);
    glVertex3f(550.0, 1100.0, 550.0);
    glEnd();
}
void bangunan3() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-400.0, 1400.0, -400.0);
    glVertex3f(400.0, 1400.0, -400.0);
    glVertex3f(400.0, 1400.0, 400.0);
    glVertex3f(-400.0, 1400.0, 400.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-400.0, 1120.0, -400.0);
    glVertex3f(400.0, 1120.0, -400.0);
    glVertex3f(400.0, 1120.0, 400.0);
    glVertex3f(-400.0, 1120.0, 400.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(400.0, 1120.0, -400.0);
    glVertex3f(400.0, 1400.0, -400.0);
    glVertex3f(400.0, 1400.0, 400.0);
    glVertex3f(400.0, 1120.0, 400.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-400.0, 1120.0, -400.0);
    glVertex3f(-400.0, 1400.0, -400.0);
    glVertex3f(-400.0, 1400.0, 400.0);
    glVertex3f(-400.0, 1120.0, 400.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-400.0, 1120.0, -400.0);
    glVertex3f(-400.0, 1400.0, -400.0);
    glVertex3f(400.0, 1400.0, -400.0);
    glVertex3f(400.0, 1120.0, -400.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-400.0, 1120.0, 400.0);
    glVertex3f(-400.0, 1400.0, 400.0);
    glVertex3f(400.0, 1400.0, 400.0);
    glVertex3f(400.0, 1120.0, 400.0);
    glEnd();
}
void atap2() {
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-350.0, 1500.0, -350.0);
    glVertex3f(350.0, 1500.0, -350.0);
    glVertex3f(350.0, 1500.0, 350.0);
    glVertex3f(-350.0, 1500.0, 350.0);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-550.0, 1400.0, -550.0);
    glVertex3f(550.0, 1400.0, -550.0);
    glVertex3f(550.0, 1400.0, 550.0);
    glVertex3f(-550.0, 1400.0, 550.0);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(550.0, 1400.0, -550.0);
    glVertex3f(350.0, 1500.0, -350.0);
    glVertex3f(350.0, 1500.0, 350.0);
    glVertex3f(550.0, 1400.0, 550.0);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-550.0, 1400.0, -550.0);
    glVertex3f(-350.0, 1500.0, -350.0);
    glVertex3f(-350.0, 1500.0, 350.0);
    glVertex3f(-550.0, 1400.0, 550.0);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-550.0, 1400.0, -550.0);
    glVertex3f(-350.0, 1500.0, -350.0);
    glVertex3f(350.0, 1500.0, -350.0);
    glVertex3f(550.0, 1400.0, -550.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-550.0, 1400.0, 550.0);
    glVertex3f(-350.0, 1500.0, 350.0);
    glVertex3f(350.0, 1500.0, 350.0);
    glVertex3f(550.0, 1400.0, 550.0);
    glEnd();
}
void lantai4() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-450.0, 1520.0, -450.0);
    glVertex3f(450.0, 1520.0, -450.0);
    glVertex3f(450.0, 1520.0, 450.0);
    glVertex3f(-450.0, 1520.0, 450.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-450.0, 1500.0, -450.0);
    glVertex3f(450.0, 1500.0, -450.0);
    glVertex3f(450.0, 1500.0, 450.0);
    glVertex3f(-450.0, 1500.0, 450.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(450.0, 1500.0, -450.0);
    glVertex3f(450.0, 1520.0, -450.0);
    glVertex3f(450.0, 1520.0, 450.0);
    glVertex3f(450.0, 1500.0, 450.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-450.0, 1500.0, -450.0);
    glVertex3f(-450.0, 1520.0, -450.0);
    glVertex3f(-450.0, 1520.0, 450.0);
    glVertex3f(-450.0, 1500.0, 450.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-450.0, 1500.0, -450.0);
    glVertex3f(-450.0, 1520.0, -450.0);
    glVertex3f(450.0, 1520.0, -450.0);
    glVertex3f(450.0, 1500.0, -450.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.40, 0.04);
    glVertex3f(-450.0, 1500.0, 450.0);
    glVertex3f(-450.0, 1520.0, 450.0);
    glVertex3f(450.0, 1520.0, 450.0);
    glVertex3f(450.0, 1500.0, 450.0);
    glEnd();
}
void bangunan4() {
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-300.0, 1800.0, -300.0);
    glVertex3f(300.0, 1800.0, -300.0);
    glVertex3f(300.0, 1800.0, 300.0);
    glVertex3f(-300.0, 1800.0, 300.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-300.0, 1520.0, -300.0);
    glVertex3f(300.0, 1520.0, -300.0);
    glVertex3f(300.0, 1520.0, 300.0);
    glVertex3f(-300.0, 1520.0, 300.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(300.0, 1520.0, -300.0);
    glVertex3f(300.0, 1800.0, -300.0);
    glVertex3f(300.0, 1800.0, 300.0);
    glVertex3f(300.0, 1520.0, 300.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-300.0, 1520.0, -300.0);
    glVertex3f(-300.0, 1800.0, -300.0);
    glVertex3f(-300.0, 1800.0, 300.0);
    glVertex3f(-300.0, 1520.0, 300.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-300.0, 1520.0, -300.0);
    glVertex3f(-300.0, 1800.0, -300.0);
    glVertex3f(300.0, 1800.0, -300.0);
    glVertex3f(300.0, 1520.0, -300.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.7, 0.71);
    glVertex3f(-300.0, 1520.0, 300.0);
    glVertex3f(-300.0, 1800.0, 300.0);
    glVertex3f(300.0, 1800.0, 300.0);
    glVertex3f(300.0, 1520.0, 300.0);
    glEnd();
}
void atap3() {
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-30.0, 2100.0, -30.0);
    glVertex3f(30.0, 2100.0, -30.0);
    glVertex3f(30.0, 2100.0, 30.0);
    glVertex3f(-30.0, 2100.0, 30.0);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-500.0, 1800.0, -500.0);
    glVertex3f(500.0, 1800.0, -500.0);
    glVertex3f(500.0, 1800.0, 500.0);
    glVertex3f(-500.0, 1800.0, 500.0);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(500.0, 1800.0, -500.0);
    glVertex3f(30.0, 2100.0, -30.0);
    glVertex3f(30.0, 2100.0, 30.0);
    glVertex3f(500.0, 1800.0, 500.0);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-500.0, 1800.0, -500.0);
    glVertex3f(-30.0, 2100.0, -30.0);
    glVertex3f(-30.0, 2100.0, 30.0);
    glVertex3f(-500.0, 1800.0, 500.0);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-500.0, 1800.0, -500.0);
    glVertex3f(-30.0, 2100.0, -30.0);
    glVertex3f(30.0, 2100.0, -30.0);
    glVertex3f(500.0, 1800.0, -500.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.27, 0.67, 0.89);
    glVertex3f(-500.0, 1800.0, 500.0);
    glVertex3f(-30.0, 2100.0, 30.0);
    glVertex3f(30.0, 2100.0, 30.0);
    glVertex3f(500.0, 1800.0, 500.0);
    glEnd();
}
void pucuk() {
    glPushMatrix();
    glTranslatef(0, 2120, 0);
    glColor3f(0.78, 0.74, 0.69);
    glutSolidCube(60.0);
    glPopMatrix();
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(-35.0, 2155.0, -35.0);
    glVertex3f(35.0, 2155.0, -35.0);
    glVertex3f(35.0, 2155.0, 35.0);
    glVertex3f(-35.0, 2155.0, 35.0);
    glEnd();
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(-35.0, 2150.0, -35.0);
    glVertex3f(35.0, 2150.0, -35.0);
    glVertex3f(35.0, 2150.0, 35.0);
    glVertex3f(-35.0, 2150.0, 35.0);
    glEnd();
    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(35.0, 2150.0, -35.0);
    glVertex3f(35.0, 2155.0, -35.0);
    glVertex3f(35.0, 2155.0, 35.0);
    glVertex3f(35.0, 2150.0, 35.0);
    glEnd();
    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(-35.0, 2150.0, -35.0);
    glVertex3f(-35.0, 2155.0, -35.0);
    glVertex3f(-35.0, 2155.0, 35.0);
    glVertex3f(-35.0, 2150.0, 35.0);
    glEnd();
    //depan
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(-35.0, 2150.0, -35.0);
    glVertex3f(-35.0, 2155.0, -35.0);
    glVertex3f(35.0, 2155.0, -35.0);
    glVertex3f(35.0, 2150.0, -35.0);
    glEnd();
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.70, 0.30, 0.05);
    glVertex3f(-35.0, 2150.0, 35.0);
    glVertex3f(-35.0, 2155.0, 35.0);
    glVertex3f(35.0, 2155.0, 35.0);
    glVertex3f(35.0, 2150.0, 35.0);
    glEnd();
    //bulat atas pertama
    glPushMatrix();
    glTranslatef(0, 2156.5, 0);
    glColor3f(1.0, 0.87, 0.12);
    glutSolidSphere(30.0, 30, 30);
    glPopMatrix();
    glEnd();
    //bulat atas kedua
    glPushMatrix();
    glTranslatef(0, 2203, 0);
    glColor3f(1.0, 0.87, 0.12);;
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //bulat atas ketiga
    glPushMatrix();
    glTranslatef(0, 2242, 0);
    glColor3f(1.0, 0.87, 0.12);
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //bulat atas keempat
    glPushMatrix();
    glTranslatef(0, 2281, 0);
    glColor3f(1.0, 0.87, 0.12);
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //bulat atas kelima
    glPushMatrix();
    glTranslatef(0, 2320, 0);
    glColor3f(1.0, 0.87, 0.12);;
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //bulat atas keenam
    glPushMatrix();
    glTranslatef(0, 2359, 0);
    glColor3f(1.0, 0.87, 0.12);
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //bulat atas ketujuh
    glPushMatrix();
    glTranslatef(0, 2398, 0);
    glColor3f(1.0, 0.87, 0.12);
    glutSolidSphere(20.0, 20, 20);
    glPopMatrix();
    glEnd();
    //tiang
    glPushMatrix();
    glTranslatef(0, 2180, 0);
    glColor3f(0.95, 0.13, 0.13);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();
    glEnd();
    //kerucut 1
    glPushMatrix();
    glTranslatef(0, 2420.5, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 2
    glPushMatrix();
    glTranslatef(0, 2446, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 3
    glPushMatrix();
    glTranslatef(0, 2471.5, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 4
    glPushMatrix();
    glTranslatef(0, 2497, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 5
    glPushMatrix();
    glTranslatef(0, 2522.5, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 6
    glPushMatrix();
    glTranslatef(0, 2548, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 7
    glPushMatrix();
    glTranslatef(0, 2573.5, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 8
    glPushMatrix();
    glTranslatef(0, 2599, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut 9
    glPushMatrix();
    glTranslatef(0, 2624, 0);
    glColor3f(1.0, 0.87, 0.12);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut atas bola1
    glPushMatrix();
    glTranslatef(0, 2362, 0);
    glColor3f(0.95, 0.92, 0.87);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut atas bola2
    glPushMatrix();
    glTranslatef(0, 2327.5, 0);
    glColor3f(0.95, 0.92, 0.87);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut atas bola3
    glPushMatrix();
    glTranslatef(0, 2288.5, 0);
    glColor3f(0.95, 0.92, 0.87);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut atas bola4
    glPushMatrix();
    glTranslatef(0, 2249.5, 0);
    glColor3f(0.95, 0.92, 0.87);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();
    //kerucut atas bola5
    glPushMatrix();
    glTranslatef(0 + x_geser, 2215 + y_geser, 0 + z_geser);
    glColor3f(0.95, 0.92, 0.87);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutSolidCone(30.0, 30.0, 20, 20);
    glPopMatrix();
    glEnd();

}

void pilarlantai1() {
    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    // pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, -350.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, 350.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, 150.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    // pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-600.0, -150.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, 150.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, -150.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, -350.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(600.0, 350.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar13
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar14
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar15
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(150.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar16
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-150.0, 600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar17
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar18
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar19
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(150.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar20
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-150.0, -600.0, 200.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();
}

void ornamenlantai1() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 300.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 300.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 300.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 300.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 500.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 500.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 500.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 500.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 600.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 600.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(600.0, 200.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-600.0, 200.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 600.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 600.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 200.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 200.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1200, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 300.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 300.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 300.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 300.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 500.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(600.0, 500.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 500.0, 150);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-600.0, 500.0, -600);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 450.0f, 32, 32);
    glPopMatrix();

    //pintu 1
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 220.0, -120.0);
    glVertex3f(601.0, 500.0, -120.0);
    glVertex3f(601.0, 500.0, 120.0);
    glVertex3f(601.0, 220.0, 120.0);
    glEnd();

    //pintu 2
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 220.0, -120.0);
    glVertex3f(-601.0, 500.0, -120.0);
    glVertex3f(-601.0, 500.0, 120.0);
    glVertex3f(-601.0, 220.0, 120.0);
    glEnd();

    //pintu 3
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 220.0, -120.0);
    glVertex3f(-601.0, 500.0, -120.0);
    glVertex3f(-601.0, 500.0, 120.0);
    glVertex3f(-601.0, 220.0, 120.0);
    glEnd();
    glPopMatrix();

    //pintu 4
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 220.0, -120.0);
    glVertex3f(601.0, 500.0, -120.0);
    glVertex3f(601.0, 500.0, 120.0);
    glVertex3f(601.0, 220.0, 120.0);
    glEnd();
    glPopMatrix();

    //jendela 1
    glPushMatrix();
    glTranslatef(-250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -70.0);
    glVertex3f(601.0, 450.0, -70.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 70.0);
    glVertex3f(601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 1
    glPushMatrix();
    glTranslatef(-250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -60.0);
    glVertex3f(602.0, 445.0, -60.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 60.0);
    glVertex3f(602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 2
    glPushMatrix();
    glTranslatef(250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -70.0);
    glVertex3f(601.0, 450.0, -70.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 70.0);
    glVertex3f(601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 2
    glPushMatrix();
    glTranslatef(250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -60.0);
    glVertex3f(602.0, 445.0, -60.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 60.0);
    glVertex3f(602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 3
    glPushMatrix();
    glTranslatef(-475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -95.0);
    glVertex3f(601.0, 450.0, -95.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 95.0);
    glVertex3f(601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 3
    glPushMatrix();
    glTranslatef(-475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -85.0);
    glVertex3f(602.0, 445.0, -85.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 85.0);
    glVertex3f(602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 4
    glPushMatrix();
    glTranslatef(475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -95.0);
    glVertex3f(601.0, 450.0, -95.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 95.0);
    glVertex3f(601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 4
    glPushMatrix();
    glTranslatef(475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -85.0);
    glVertex3f(602.0, 445.0, -85.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 85.0);
    glVertex3f(602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 5
    glPushMatrix();
    glTranslatef(-250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -70.0);
    glVertex3f(-601.0, 450.0, -70.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 70.0);
    glVertex3f(-601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 5
    glPushMatrix();
    glTranslatef(-250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -60.0);
    glVertex3f(-602.0, 445.0, -60.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 60.0);
    glVertex3f(-602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 6
    glPushMatrix();
    glTranslatef(250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -70.0);
    glVertex3f(-601.0, 450.0, -70.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 70.0);
    glVertex3f(-601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 6
    glPushMatrix();
    glTranslatef(250, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -60.0);
    glVertex3f(-602.0, 445.0, -60.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 60.0);
    glVertex3f(-602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 7
    glPushMatrix();
    glTranslatef(-475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -95.0);
    glVertex3f(-601.0, 450.0, -95.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 95.0);
    glVertex3f(-601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 7
    glPushMatrix();
    glTranslatef(-475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -85.0);
    glVertex3f(-602.0, 445.0, -85.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 85.0);
    glVertex3f(-602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 8
    glPushMatrix();
    glTranslatef(475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -95.0);
    glVertex3f(-601.0, 450.0, -95.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 95.0);
    glVertex3f(-601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 8
    glPushMatrix();
    glTranslatef(475, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -85.0);
    glVertex3f(-602.0, 445.0, -85.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 85.0);
    glVertex3f(-602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 9
    glPushMatrix();
    glTranslatef(0, 0, -475);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -95.0);
    glVertex3f(-601.0, 450.0, -95.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 95.0);
    glVertex3f(-601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 9
    glPushMatrix();
    glTranslatef(0, 0, -475);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -85.0);
    glVertex3f(-602.0, 445.0, -85.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 85.0);
    glVertex3f(-602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 10
    glPushMatrix();
    glTranslatef(0, 0, 475);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -95.0);
    glVertex3f(-601.0, 450.0, -95.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 95.0);
    glVertex3f(-601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 10
    glPushMatrix();
    glTranslatef(0, 0, 475);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -85.0);
    glVertex3f(-602.0, 445.0, -85.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 85.0);
    glVertex3f(-602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 11
    glPushMatrix();
    glTranslatef(0, 0, -250);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -70.0);
    glVertex3f(-601.0, 450.0, -70.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 70.0);
    glVertex3f(-601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 11
    glPushMatrix();
    glTranslatef(0, 0, -250);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -60.0);
    glVertex3f(-602.0, 445.0, -60.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 60.0);
    glVertex3f(-602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 12
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-601.0, 320.0, -70.0);
    glVertex3f(-601.0, 450.0, -70.0);
    glVertex3f(-601.0, 480.0, 0);
    glVertex3f(-601.0, 450.0, 70.0);
    glVertex3f(-601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 12
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-602.0, 330.0, -60.0);
    glVertex3f(-602.0, 445.0, -60.0);
    glVertex3f(-602.0, 470.0, 0);
    glVertex3f(-602.0, 445.0, 60.0);
    glVertex3f(-602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 13
    glPushMatrix();
    glTranslatef(0, 0, -475);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -95.0);
    glVertex3f(601.0, 450.0, -95.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 95.0);
    glVertex3f(601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 13
    glPushMatrix();
    glTranslatef(0, 0, -475);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -85.0);
    glVertex3f(602.0, 445.0, -85.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 85.0);
    glVertex3f(602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 14
    glPushMatrix();
    glTranslatef(0, 0, 475);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -95.0);
    glVertex3f(601.0, 450.0, -95.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 95.0);
    glVertex3f(601.0, 320.0, 95.0);
    glEnd();
    glPopMatrix();
    //kaca 14
    glPushMatrix();
    glTranslatef(0, 0, 475);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -85.0);
    glVertex3f(602.0, 445.0, -85.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 85.0);
    glVertex3f(602.0, 330.0, 85.0);
    glEnd();
    glPopMatrix();

    //jendela 15
    glPushMatrix();
    glTranslatef(0, 0, -250);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -70.0);
    glVertex3f(601.0, 450.0, -70.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 70.0);
    glVertex3f(601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 15
    glPushMatrix();
    glTranslatef(0, 0, -250);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -60.0);
    glVertex3f(602.0, 445.0, -60.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 60.0);
    glVertex3f(602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

    //jendela 16
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(601.0, 320.0, -70.0);
    glVertex3f(601.0, 450.0, -70.0);
    glVertex3f(601.0, 480.0, 0);
    glVertex3f(601.0, 450.0, 70.0);
    glVertex3f(601.0, 320.0, 70.0);
    glEnd();
    glPopMatrix();
    //kaca 16
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(602.0, 330.0, -60.0);
    glVertex3f(602.0, 445.0, -60.0);
    glVertex3f(602.0, 470.0, 0);
    glVertex3f(602.0, 445.0, 60.0);
    glVertex3f(602.0, 330.0, 60.0);
    glEnd();
    glPopMatrix();

}

void tangga() {
    //tangga 1 paling atas
    //atas
    glPushMatrix();
    glTranslatef(3, 60, 249);
    glBegin(GL_QUADS);
    glColor3f(0.43, 0.43, 0.43);
    glVertex3f(-150, 95, 600);
    glVertex3f(150, 95, 600);
    glVertex3f(150, 95, 625);
    glVertex3f(-150, 95, 625);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 625);
    glVertex3f(-150, 95, 625);
    glVertex3f(150, 95, 625);
    glVertex3f(150, 40, 625);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(150, 40, 600);
    glVertex3f(150, 95, 600);
    glVertex3f(150, 95, 625);
    glVertex3f(150, 40, 625);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 600);
    glVertex3f(-150, 95, 600);
    glVertex3f(-150, 95, 625);
    glVertex3f(-150, 40, 625);
    glEnd();

    //tangga 2
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.43, 0.43, 0.43);
    glVertex3f(-150, 80, 625);
    glVertex3f(150, 80, 625);
    glVertex3f(150, 80, 650);
    glVertex3f(-150, 80, 650);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 650);
    glVertex3f(-150, 80, 650);
    glVertex3f(150, 80, 650);
    glVertex3f(150, 40, 650);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(150, 40, 625);
    glVertex3f(150, 80, 625);
    glVertex3f(150, 80, 650);
    glVertex3f(150, 40, 650);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 625);
    glVertex3f(-150, 80, 625);
    glVertex3f(-150, 80, 650);
    glVertex3f(-150, 40, 650);
    glEnd();

    //tangga 3
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.43, 0.43, 0.43);
    glVertex3f(-150, 65, 650);
    glVertex3f(150, 65, 650);
    glVertex3f(150, 65, 675);
    glVertex3f(-150, 65, 675);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 675);
    glVertex3f(-150, 65, 675);
    glVertex3f(150, 65, 675);
    glVertex3f(150, 40, 675);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(150, 40, 650);
    glVertex3f(150, 65, 650);
    glVertex3f(150, 65, 675);
    glVertex3f(150, 40, 675);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 650);
    glVertex3f(-150, 65, 650);
    glVertex3f(-150, 65, 675);
    glVertex3f(-150, 40, 675);
    glEnd();

    //tangga 4 paling bawah
    //atas
    glBegin(GL_QUADS);
    glColor3f(0.43, 0.43, 0.43);
    glVertex3f(-150, 50, 675);
    glVertex3f(150, 50, 675);
    glVertex3f(150, 50, 700);
    glVertex3f(-150, 50, 700);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 700);
    glVertex3f(-150, 50, 700);
    glVertex3f(150, 50, 700);
    glVertex3f(150, 40, 700);
    glEnd();

    //kanan
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(150, 40, 675);
    glVertex3f(150, 50, 675);
    glVertex3f(150, 50, 700);
    glVertex3f(150, 40, 700);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.69, 0.69);
    glVertex3f(-150, 40, 675);
    glVertex3f(-150, 50, 675);
    glVertex3f(-150, 50, 700);
    glVertex3f(-150, 40, 700);
    glEnd();
    glPopMatrix();
}

void pagar_lantai1() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar13
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar14
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();
}

void pagar_lantai2() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar13
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar14
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();
}

void pagar_lantai3() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, -650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar13
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar14
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(450.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(250.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(125.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-350.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-550.0, 650, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 660.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-650.0, 700.0, -680.0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 1360.0f, 32, 32);
    glPopMatrix();

    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -0.0, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 250, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 450, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 80.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, 125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -125, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -350, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-650.0, -550, 620.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 50.0f, 32, 32);
    glPopMatrix();
}

void pilarlantai2() {
    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    // pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    // pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();
}

void ornamenlantai2() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    //pintu 1
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();

    //pintu 2
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();

    //pintu 3
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //pintu 4
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //jendela 1
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 2
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 3
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 4
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 5
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 6
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 7
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 8
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();
}

void pilarlantai3() {
    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    // pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    // pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();
}

void ornamenlantai3() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    //pintu 1
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();

    //pintu 2
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();

    //pintu 3
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //pintu 4
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //jendela 1
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 2
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 3
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 4
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 5
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 6
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 7
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 8
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();
}

void pilarlantai4() {
    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    // pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 380.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, 200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    // pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(500.0, -200.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, 500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();

    //pilar12
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, -500.0, 620.0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 400.0f, 32, 32);
    glPopMatrix();
}

void ornamenlantai4() {
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 720.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, 190);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90, 0.0, -1.0, 0.0);
    glTranslatef(-500.0, 900.0, -500);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 320.0f, 32, 32);
    glPopMatrix();

    //pintu 1
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();

    //pintu 2
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();

    //pintu 3
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 630.0, -120.0);
    glVertex3f(-501.0, 910.0, -120.0);
    glVertex3f(-501.0, 910.0, 120.0);
    glVertex3f(-501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //pintu 4
    glPushMatrix();
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_QUADS);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 630.0, -120.0);
    glVertex3f(501.0, 910.0, -120.0);
    glVertex3f(501.0, 910.0, 120.0);
    glVertex3f(501.0, 630.0, 120.0);
    glEnd();
    glPopMatrix();

    //jendela 1
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 2
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 3
    glPushMatrix();
    glTranslatef(-350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 4
    glPushMatrix();
    glTranslatef(350, 0, 0);
    glRotatef(90, 0, -1.0, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 5
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 6
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(501.0, 745.0, -70.0);
    glVertex3f(501.0, 875.0, -70.0);
    glVertex3f(501.0, 875.0, 70.0);
    glVertex3f(501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 7
    glPushMatrix();
    glTranslatef(0, 0, -350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();

    //jendela 8
    glPushMatrix();
    glTranslatef(0, 0, 350);
    glBegin(GL_POLYGON);
    glColor3f(0.71, 0.11, 0.11);
    glVertex3f(-501.0, 745.0, -70.0);
    glVertex3f(-501.0, 875.0, -70.0);
    glVertex3f(-501.0, 875.0, 70.0);
    glVertex3f(-501.0, 745.0, 70.0);
    glEnd();
    glPopMatrix();
}

void lampionlantai1() {
    //1 
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, 175);
    glVertex3f(175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, -175);
    glVertex3f(175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, -175);
    glVertex3f(-175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, 175);
    glVertex3f(-175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void lampionlantai2() {
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, 175);
    glVertex3f(175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, -175);
    glVertex3f(175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, -175);
    glVertex3f(-175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, 175);
    glVertex3f(-175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void lampionlantai3() {
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, 175);
    glVertex3f(175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, -175);
    glVertex3f(175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, -175);
    glVertex3f(-175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, 175);
    glVertex3f(-175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void pagar() {
    //pilar1
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-830.0, 0.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(-830.0, 300.0, -830.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1660.0f, 32, 32);
    glPopMatrix();

    //pilar2
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-830.0, 830.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 120.0f, 32, 32);
    glPopMatrix();

    //pilar3
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-830.0, -830.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar4
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 830.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(-830.0, 300.0, -830.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1660.0f, 32, 32);
    glPopMatrix();

    //pilar5
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(830.0, 830.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar6
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(830.0, -830.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glTranslatef(830.0, 300.0, -830.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 1660.0f, 32, 32);
    glPopMatrix();

    //pilar7
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(830.0, 0.0, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar8
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(415.0, -830, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar9
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(200.0, -830, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(830.0, 300.0, -830.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 650.0f, 32, 32);
    glPopMatrix();

    //pilar10
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-200.0, -830, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    //pilar11
    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glTranslatef(-415.0, -830, 200.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.71, 0.11, 0.11);
    glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
    glTranslatef(830.0, 300.0, 180.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 650.0f, 32, 32);
    glPopMatrix();
}

void draw() {
    // Mulai tuliskan isi pikiranmu disini
    tanah();
    beton();
    building();
    lantai2();
    bangunan2();
    atap1();
    lantai3();
    bangunan3();
    atap2();
    lantai4();
    bangunan4();
    atap3();
    pucuk();
    pilarlantai1();
    pilarlantai2();
    ornamenlantai1();
    ornamenlantai2();
    pagar_lantai1();
    tangga();

    glPushMatrix();
    glTranslatef(0.0, 490.0, 0.0);
    glScalef(0.78, 1.0, 0.78);
    pagar_lantai2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 1020.0, 0.0);
    glScalef(0.65, 0.8, 0.65);
    pagar_lantai3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 620.0, 0.0);
    glScalef(0.78, 0.8, 0.78);
    pilarlantai3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 625.0, 0.0);
    glScalef(0.78, 0.8, 0.8);
    ornamenlantai3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 1020.0, 0.0);
    glScalef(0.6, 0.8, 0.58);
    pilarlantai4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 1025.0, 0.0);
    glScalef(0.6, 0.8, 0.62);
    ornamenlantai4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, 190, 1.0);
    glScalef(3.8, 3.0, 3.8);
    lampionlantai1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, 860, 1.0);
    glScalef(3.0, 2.0, 3.0);
    lampionlantai2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, 1320, 1.0);
    glScalef(2.6, 1.8, 2.6);
    lampionlantai3();
    glPopMatrix();

    pagar();
    ground();
    cout << "X_GESER = " << x_geser << "    Y_GESER = " << y_geser << "    Z_GESER = " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(50 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
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

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 2");

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