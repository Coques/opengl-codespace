#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
void recta_punto_medio(int,int,int,int);
void pintar(int,int,char);
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}

void recta_punto_medio(int x0, int y0, int x1, int y1)
{
    int dx, dy, dE, dNE, d, x, y;
    dx = x1 - x0;
    dy = y1- y0;
    d = 2*dy - dx;
    dE = 2*dy;
    dNE = 2*(dy - dx);
    x = x0;
    y = y0;
    pintar(x, y, 'r');
    while (x<x1)
    {
        if(d<=0){
        d += dE;
        x++;
    }
    else{
        d += dNE;
        x++;
        y++;
    }
    pintar(x, y, 'g');
    }
}

void pintar(int x,int y, char atributo)
{
    switch(atributo)
    {
        case 'r': glColor3f(1.0, 0.0, 0.0); break;
        case 'g': glColor3f(0.0, 1.0, 0.0); break;
        case 'b': glColor3f(0.0, 0.0, 1.0); break;
    }

    glVertex2i(x, y);
}    

void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
glShadeModel(GL_FLAT);
}
void display(void)
{
GLfloat ang, radio = 8.0f, x, y;
glClear(GL_COLOR_BUFFER_BIT);
glPushMatrix();


recta_punto_medio(-10.0, -20.0, 30.0, 80.0);

glPopMatrix();      // reecupera el estado del matriz
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