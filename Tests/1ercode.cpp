#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int,int);
void planoXY(void);
void circunferencia(int);
void algoritmo_punto_medio(int,int,int,int);
void engranaje(int,int,int);

// Variables globales
int R = 30;  // Radio mayor
int r = 15;  // Radio menor
int N = 32;  // Número de dientes del engranaje

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(800,600);
glutInitWindowPosition(100,100);
glutCreateWindow("24200166 - Evaluacion 01"); // Cambia el título de la ventana a tu número de matrícula
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
void init(void)
{
glClearColor(0.85,0.85,0.85,0.0);  
glShadeModel(GL_FLAT);
}

void planoXY(void)
{
    glColor3f(0, 0.7, 0);

    glBegin(GL_LINES); 
    glVertex2f(-35.0, 0.0); 
    glVertex2f(35.0, 0.0);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(0.0, -35.0); 
    glVertex2f(0.0, 35.0);  
    glEnd();
}

void circunferencia(int radio)
{
    GLfloat ang,x,y;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        ang = i * M_PI / 180.0; // Convertir grados a radianes
        x = radio * cos(ang); // Calcular coordenada x
        y = radio * sin(ang); // Calcular coordenada y
        glVertex2f(x, y);
    }
    glEnd();
}

void algoritmo_punto_medio(int x0,int y0,int x1,int y1)
{
    GLfloat dx,dy,sx,sy,err,e2;

    dx = abs(x1 - x0); // Calcular la diferencia en x
    dy = abs(y1 - y0); // Calcular la diferencia en y

    sx = (x0 < x1) ? 1 : -1; // Determinar la dirección del paso en x
    sy = (y0 < y1) ? 1 : -1; // Determinar la dirección del paso en y

    err = dx - dy; // Inicializar el error

    glBegin(GL_POINTS);

    while (1)
    {
        glVertex2i(x0, y0);

        if (x0 == x1 && y0 == y1) // Verificar si se ha alcanzado el punto final
            break;

        e2 = 2 * err;

        if (e2 > -dy) // Verificar si se debe mover en x
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) // Verificar si se debe mover en y
        {
            err += dx;
            y0 += sy;
        }
    }

    glEnd();
}

void engranaje(int radiomenor,int radiomayor,int Nv)
{
    GLfloat x[100], y[100],radio,ang;
    int next;
    for (int i=0;i<Nv;i++)
        {
            if (i%2==0)
            {
                radio = radiomayor; // Alternar entre radio mayor y menor para crear los dientes del engranaje
            }
            else
            {
                radio = radiomenor; //  Alternar entre radio mayor y menor para crear los dientes del engranaje
            }
            ang = i * 2 * M_PI / Nv;
            x[i] = radio * cos(ang); // Calcular coordenada x
            y[i] = radio * sin(ang); // Calcular coordenada y
        }
    for (int i=0; i<Nv; i++)
    {
        next = (i+1) % Nv;
        algoritmo_punto_medio((int)x[i], (int)y[i], (int)x[next], (int)y[next]); // Dibujar línea entre el punto actual y el siguiente utilizando el algoritmo de punto medio
    }
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0); 
    glPushMatrix();                   

    planoXY();
    glColor3f(0,0,0.7);
    circunferencia(R);
    glColor3f(0.7,0,0);
    circunferencia(r);

    glColor3f(1,0,0);
    engranaje(r, R, N);
    glPopMatrix();     
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