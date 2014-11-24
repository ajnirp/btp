#include "fluidsolver.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>

using namespace std;

int w = 200;
int h = 200;
int window_id;

void init_gl();
void timerFunc(int);
void keyboardFunc(unsigned char, int, int);
void displayFunc();
void render(int, char**);

FluidSolver* fs;

int main(int argc, char **argv)
{
  fs = new FluidSolver(100, 0.2f);
  // render(argc, argv);
  return 0;
}

void render(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(w, h);
  window_id = glutCreateWindow("BTP");
  glutDisplayFunc(displayFunc);
  glutKeyboardFunc(keyboardFunc);
  glutTimerFunc(10,timerFunc,0);
  init_gl();
  glutMainLoop();
}

void timerFunc(int iter)
{
  if(iter < 2000)
  {
    cout << iter << endl;
    fs->step();
    iter += 1;
    glutPostRedisplay();
    glutTimerFunc(0,timerFunc,iter); 
  }
}

void init_gl()
{
  glClearColor(1,1,1,0);
  glColor3f(0,0,0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);
}

void displayFunc()
{
  // for (int i = 0 ; i < )
  glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y)
{
  if (key == 27)
    glutDestroyWindow(window_id);
}