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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    dasar(); //test

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
    case GLUT_KEY_UP:
        cout << 1;
        break;
    }
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
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return(0);
}
