#include "grid.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

Grid* curr_grid;

void init(){

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,1,0,1, -1, 10);

  glMatrixMode(GL_MODELVIEW);

  curr_grid = new Grid(0.01,0.01,PIC);
  curr_grid->initialise_grid(100,100);
  curr_grid->initialise_grid(50,50);
  curr_grid->initialise_fluid(); 

}

bool recording=true;
unsigned int framenum=0;
unsigned char *pRGB;

int SCREEN_WIDTH=800;
int SCREEN_HEIGHT=600;

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"animation/100x100_2/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}

void display( void ) {
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	curr_grid->Draw();

	if (recording)
    	capture_frame(framenum++);

	glutSwapBuffers();
	//sleep(3);
}

void timer(int val)
{
	if(val < 2000){
		curr_grid->Exec_Time_Step();
		glutPostRedisplay();
		glutTimerFunc(0, timer, val+1);	
	}
}

void keyboard(unsigned char key, int x, int y) {
	glutPostRedisplay();
}

int main (int argc, char *argv[]) 
{
	//give file name as the argument	
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( 800, 600 );

	glutCreateWindow( " Fluid Sim " );

	glutDisplayFunc( display );

	//glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	//glutMouseFunc( mouse );
	glutTimerFunc(10, timer, 0 );

    init();
	glutMainLoop();
}
