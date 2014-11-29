#include "fluidsolver.h"

#define WINDOW_SIDE 300

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include "fluidsolver.h"

using namespace std;

int s = WINDOW_SIDE;
int window_id;

void init_gl();
void timerFunc(int);
void keyboardFunc(unsigned char, int, int);
void displayFunc();
void render();

int n = 60;
int dg = WINDOW_SIDE / n; // cell dimensions
int dg_2 = dg / 2;
float dt = 0.2f;

inline int I(int i, int j){ return i + (n + 2) * j; }

FluidSolver fs(n, dt);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  render();
  return 0;
}

void render()
{
  glutInitWindowSize(WINDOW_SIDE, WINDOW_SIDE);
  window_id = glutCreateWindow("Flame");
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);

  glutDisplayFunc(displayFunc);
  glutKeyboardFunc(keyboardFunc);

  glClearColor(1, 1, 1, 1);
  glColor3f(0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WINDOW_SIDE, 0, WINDOW_SIDE);
  glutTimerFunc(1000, timerFunc, 0);
  glutMainLoop();
}

void timerFunc(int iter)
{
  if(iter < 2000)
  {
    cout << iter << endl;
    fs.step();
    iter++;
    glutPostRedisplay();
    glutTimerFunc(0, timerFunc, iter); 
  }
}

void displayFunc()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_QUADS);
  for (int i = 1 ; i <= n ; i++)
  {
    int dx, dy;
    dx = (int) ((i - 0.5f) * dg);
    for (int j = 1 ; j <= n ; j++)
    {
      dy = (int)((j - 0.5f) * dg);
      if (fs.d[I(i, j)] > 0)
      {
        int c = (int)((1.0 - fs.d[I(i, j)]) * 255); // color
        if (c < 0) c = 0;
        glColor3ub(c, c, c);
        glVertex2f(dx-dg_2, dy-dg_2);
        glVertex2f(dx-dg_2, dy+dg_2);
        glVertex2f(dx+dg_2, dy+dg_2);
        glVertex2f(dx+dg_2, dy-dg_2);
      }

      // // draw velocity field
      // if (vkey && i % 5 == 1 && j % 5 == 1)
      // {
      //   u = (int)( 50 * fs.u[I(i,j)] );
      //   v = (int)( 50 * fs.v[I(i,j)] );
      //   big.setColor(Color.red);
      //   big.drawLine(dx, dy, dx+u, dy+v);
      // }
    }
  }
  glEnd();
  glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y)
{
  if (key == 27)
    glutDestroyWindow(window_id);
}