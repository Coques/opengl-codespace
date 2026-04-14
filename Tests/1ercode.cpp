#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
void puntos(int,int,int,int);
void circunferencia(int,int,int,int);
void circunferencia_relleno(int,int,int,int);
void engranaje(int,int,int);

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
void init(void)
{
glClearColor(1,1,1,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
glShadeModel(GL_FLAT);
}

void circunferencia(int h,int k,int radio,int Np)
{
    glBegin(GL_LINE_LOOP);
        puntos(h,k,radio,Np);
    glEnd();
}

void circunferencia_relleno(int h,int k,int radio,int Np)
{
    glBegin(GL_POLYGON);
        puntos(h,k,radio,Np);
    glEnd();
}

void puntos(int h,int k,int radio,int Np)
{
    GLfloat ang, x, y;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/Np)
        {
            x = radio * cos(ang)+h;
            y = radio * sin(ang)+k;
            glVertex2f(x,y);
        }
}

void engranaje(int radiomenor,int radiomayor,int Nv)
{
    GLfloat ang,radio, x, y;
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<Nv;i++)
        {
            if(i%2==0)
                radio=radiomayor;
            else
                radio=radiomenor;
            ang=i*2*M_PI/Nv;
            x = radio * cos(ang);
            y = radio * sin(ang);
            glVertex2f(x,y);
        }
    glEnd();
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();                      // salva el estado actual de la matriz
/*
    glColor3f(0,1,0);
    circunferencia_relleno(20,0,20,12);

    glLineWidth(3);
    glLineStipple(2,0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor3f(1,0,0);
    circunferencia(20,0,20,12);

    glLineStipple(4,0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor3f(0,0,1);
    circunferencia(-20,0,20,12);

*/
    glColor3f(0,0,1);
    engranaje(20,25,36);
    glPopMatrix();      // reecupera el estado del matriz
    glFlush();
}
void reshape(int w, int h)
{
glViewport(0,0,(GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-50.0,50.0,-50.0,50,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}