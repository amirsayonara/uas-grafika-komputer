#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

int screen_width=625;
int screen_height=625;

void cahaya(float r, float g, float b) {
    GLfloat light_position_diff[] = { 0, 0, 1, 0.0 };
    GLfloat diffuse_light[] = { r, g, b, 1.0 };

    GLfloat light_position_spec[] = { 0, 0, 1.0, 0.0 };
    GLfloat specular_light[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat posisi[] = {1.0,1.0,1.0,0.0};
    GLfloat cahaya[] = {r,g,b,1.0};
    GLfloat cahaya2[] = {1,1,1,1};

    glLightfv(GL_LIGHT2, GL_POSITION, posisi);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, cahaya);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT3, GL_POSITION, posisi);
    glLightfv(GL_LIGHT3, GL_SPECULAR, cahaya2);
    glEnable(GL_LIGHT3);

    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = { 20.0 };
    GLfloat mat_diffuse[] = { 1,1,1, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void init(void)
{
    glColor3f (1.0, 0.0, 1.0);
    glClearColor(0,0,0,0);//back color
    glShadeModel(GL_SMOOTH);
    glViewport(0,0,screen_width,screen_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    cahaya(0.4,0.4,0.4);
}

void resize(int w, int h)
{
    float skala = 10;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-skala, skala, -skala*(GLfloat)h/(GLfloat)w,
                 skala*(GLfloat)h/(GLfloat)w, -100.0, 100.0);
    else
        glOrtho (-skala*(GLfloat)w/(GLfloat)h, skala*(GLfloat)w/(GLfloat)h, -
                 skala, skala, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

void balok(float tinggi, int lebar, int panjang)
{
    glPushMatrix();
    for(float i=0; i<panjang; i++)
    {
        glTranslatef(-(lebar+1)*tinggi/2,0.0,0.0);
        for(float j=0; j<lebar; j++)
        {
            glTranslatef(tinggi,0.0,0.0);
            glutSolidCube(tinggi);
        }
        glTranslatef(-(lebar-1)*tinggi/2, 0.0,tinggi);
    }
    glPopMatrix();
}

void dasar() {
    glPushMatrix();
    glTranslated(0,-8,-1);
    balok(1,7,7);
    glTranslated(0,0.5,0);
    balok(1,5,5);
    glPopMatrix();
}

void tombol_kipas(int tekan, bool stop) {
    glPushMatrix();
    glTranslated(-1.5,-7,2);
    for (int x=0; x<4; x++) {
        if (tekan==x|(stop & x==3)) glTranslated(0,-0.2,0);
        glutSolidCube(0.5);
        if (tekan==x|(stop & x==3)) glTranslated(0,0.2,0);
        glTranslated(1,0,0);
    }
    glPopMatrix();
}

void tabung(float r_depan, float r_belakang, float panjang)
{
    float i;
    glPushMatrix();
    glTranslatef(0.0,0.0,-r_depan/4);
    glutSolidCone(r_depan,0,32,4);
    for(i=0; i<=panjang; i+=r_depan/8)
    {
        glTranslatef(0.0,0.0,r_depan/8);
        glutSolidTorus(r_depan/4,r_depan-((i*(r_depan-r_belakang))/panjang),16,16);
    }
    glTranslatef(0.0,0.0,r_depan/4);
    glutSolidCone(r_belakang,0,32,4);
    glPopMatrix();
}

void penyangga() {
    glPushMatrix();
    glTranslated(-0.05,-7,0);
    glRotated(-90,1,0,0);
    tabung(0.5,0.4,7);

    glRotated(90,1,0,0);
    glTranslated(-0.45, 7.1, 0); //engsel leher
    glRotated(90,0,1,0);
    tabung(0.3,0.3,1);
    glPopMatrix();
}

void kepala(bool panel_penggerak) {
    glPushMatrix();
    glTranslated(0,3,-1);
    tabung(1.5,1.5,2.5); //tempat dinamo
    glTranslated(-0.5,-3,1);
    glRotated(90,0,1,0);

    glTranslated(0,1.2,0);
    glRotated(90,0,0,1);
    glRotated(-90,0,1,0);
    glTranslated(0.45,0,0);
    tabung(0.5,0.5,1); //leher

    glTranslated(1,-0.5,-4.2);
    if (panel_penggerak) glTranslated(0,0,0.5); //lebih ke bawah jika true
    tabung(0.2,0.2,1); //tombol atas
    glPopMatrix();
}

void baling_dinamis(float jari_dalam,float jari_luar, float tebal, int banyak_baling) {
    float i;
    glPushMatrix();
    glTranslatef(0.0,0.0,-tebal/4);
    tabung(jari_dalam,jari_dalam,tebal);
    glTranslatef(0.0,0.0,tebal/2);
    glRotatef(90,0.0,1.0,0.0);
    for(i=0; i<banyak_baling; i++)
    {
        glTranslatef(0.0,0.0,jari_dalam);
        glRotatef(315,0.0,0.0,1.0);
        balok(0.5,jari_dalam*4.5,(jari_luar-jari_dalam+(jari_dalam/4))*2);
        glRotatef(45,0.0,0.0,1.0);
        glTranslatef(0.0,0.0,-jari_dalam);
        glRotatef(360/banyak_baling,1.0,0.0,0.0);
    }
    glPopMatrix();
}

void baling_baling(int rotasi) {
    glPushMatrix();
    glTranslated(0,3,2.8);
    glRotated(-rotasi, 0, 0, 1);
    baling_dinamis(1.2,4.5,1.2,5);
    glTranslated(0,0,-2);
    tabung(0.3,0.3,2); //as
    glPopMatrix();
}

void pembungkus() {
    glPushMatrix();
    glTranslated(0,3,3);
    glScaled(0.45,0.45,0.45);
    glutWireTorus(5,7,5,80);
    glutSolidTorus(0.5,12,10,80);
    glTranslated(0,0,4);
    glScaled(0.75,0.75,0.75);
    glutSolidTorus(0.1,12,10,80);
    //penutup depan
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    for (float x=0.1; x<=6.28; x+=0.1) {
        glVertex3f(sin(x)*5, cos(x)*5, 0);
    }
    glEnd();
    glPopMatrix();
}

void bagian_atas(int rotasi_baling, int rotasi_toleh, int rotasi_angguk, bool panel_penggerak) {
    //angguk maksimal 20
    glPushMatrix();
    glRotated(rotasi_angguk, 1, 0, 0);
    glRotated(rotasi_toleh, 0, 1, 0);
    kepala(panel_penggerak);
    baling_baling(rotasi_baling);
    pembungkus();
    glPopMatrix();
}

bool tekan_panel_atas = false, menoleh = false, tombol_stop,
menoleh_ke_kanan = true;
int tombol_level = -1, kecepatan_rotasi_baling = 0,
rotasi_baling = 0, rotasi_toleh = 0,
penambah_rotasi_toleh = 1, rotasi_angguk = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    dasar();
    tombol_kipas(tombol_level, tombol_stop);
    penyangga();
    bagian_atas(rotasi_baling, rotasi_toleh, rotasi_angguk, tekan_panel_atas);

    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
    case 'X':
        glRotated(1,1,0,0);
        break;
    case 'y':
    case 'Y':
        glRotated(1,0,1,0);
        break;
    case 'z':
    case 'Z':
        glRotated(1,0,0,1);
        break;
    case '1':
        tombol_level = 0;
        break;
    case '2':
        tombol_level = 1;
        break;
    case '3':
        tombol_level = 2;
        break;
    case '0':
        tombol_level = -1;
        tombol_stop = true;
        break;
    }
    glutPostRedisplay();
}

void keyUP(unsigned char key, int x, int y) {
    if (key=='0') tombol_stop = false;
    glutPostRedisplay();
}

void keyboard2(int key, int x, int y) {
    switch(key) {
    case GLUT_KEY_UP:
        glTranslated(0,-0.5,0);
        break;
    case GLUT_KEY_DOWN:
        glTranslated(0,0.5,0);
        break;
    case GLUT_KEY_RIGHT:
        glTranslated(-0.5,0,0);
        break;
    case GLUT_KEY_LEFT:
        glTranslated(0.5,0,0);
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case 3:
        glScaled(1.05,1.05,1.05);
        break;
    case 4:
        glScaled(0.95,0.95,0.95);
        break;
    }
    glutPostRedisplay();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("UAS Grafika Komputer (B) - MOCH. AMIR - 160411100153");
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard2);
    glutKeyboardUpFunc(keyUP);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return(0);
}
