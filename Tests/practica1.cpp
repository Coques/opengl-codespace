#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(250,250);
glutInitWindowPosition(100,100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
void init(void)
{
glClearColor(0.0,0.0,0.0,0.0); //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
glShadeModel(GL_FLAT);
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glPushMatrix(); // salva el estado actual de la matriz
glBegin(GL_POINTS);

const GLfloat radio = 4.0f;

for (int i = 0; i <= 360; ++i)
{
    GLfloat theta = static_cast<GLfloat>(i) * M_PI / 180.0f;
    GLfloat r = 3.0f - 3.0f*sin(theta);

    GLfloat x = r*cos(theta);
    GLfloat y = r*sin(theta);

    glVertex2f(x,y);
}
glEnd();
glPopMatrix(); // reecupera el estado del matriz
glFlush();
}
void reshape(int w, int h)
{
glViewport(0,0,(GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
