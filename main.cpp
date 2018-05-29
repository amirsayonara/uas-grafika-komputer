#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

int screen_width=625;
int screen_height=625;

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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glFlush();
    glutSwapBuffers();
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
    init();
    glutMainLoop();
    return(0);
}
