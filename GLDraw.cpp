#define _USE_MATH_DEFINES
#include "Common.h"
#include <GL/glut.h>
#include <cmath>

GLfloat lightAmb[] = { 0.f, 0.f, 0.f, 1.f };
GLfloat lightDiff[] = { 1.f, 1.f, 1.f, 1.f };
GLfloat lightSpec[] = { 1.f, 1.f, 1.f, 1.f };
GLfloat lightPos[] = { 1.f, 1.f, 1.f, 0.f };

float ViewR = 10.0;
float ViewAng[2] = { (M_PI / 4),(M_PI / 4) };
float ViewPos[3] = { 0,0,0 };

void UpdateViewPos()
{
    float Projection = ViewR * cos(ViewAng[1]);
    ViewPos[0] = Projection * cos(ViewAng[0]);
    ViewPos[1] = Projection * sin(ViewAng[0]);
    ViewPos[2] = ViewR * sin(ViewAng[1]);
}

void DrawAxes(void)
{
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    //x-axis
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);
    //y-axis
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 1.f, 0.f);
    //z-axis
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 1.f);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void GlDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(ViewPos[0], ViewPos[1], ViewPos[2], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    DrawAxes();
    
    for (size_t i = 0; i < N; i++)
    {
        Particles[i].GlDrawFunc();
        Particles[i].Update();
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, double(w) / h, 0.1, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(20, timer, value);    // 25ミリ秒後にまたタイマー関数を呼ぶ
}

void specialkeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        ViewAng[0] += 0.087;
        UpdateViewPos();
        break;
    case GLUT_KEY_LEFT:
        ViewAng[0] -= 0.087;
        UpdateViewPos();
        break;
    case GLUT_KEY_UP:
        ViewAng[1] += 0.087;
        UpdateViewPos();
        break;
    case GLUT_KEY_DOWN:
        ViewAng[1] -= 0.087;
        UpdateViewPos();
        break;
    case GLUT_KEY_PAGE_UP:
        ViewR -= 0.5;
        UpdateViewPos();
        break;
    case GLUT_KEY_PAGE_DOWN:
        ViewR += 0.5;
        UpdateViewPos();
        break;
    default:
        break;
    }
}

void GlMain(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Simulation of a Chaotic System by Rakibul Islam");

    glutDisplayFunc(GlDisplay);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 15);
    glutSpecialFunc(specialkeyboard);
    
    //Initialize Lighting
    {
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClearDepth(1.f);
        glEnable(GL_DEPTH_TEST);

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    UpdateViewPos();

    glutMainLoop();
}