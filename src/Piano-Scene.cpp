#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <gl\freeglut.h>
#endif

#include <stdlib.h> // for exit
//#include <unistd.h>
#include "Scene.h"

int main(int argc, char **argv) 
{  
	Scene sc(argc,argv);
	sc.Show();

}
