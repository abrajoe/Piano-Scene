#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <gl\freeglut.h>
#endif

#include <stdlib.h> // for exit
//#include <unistd.h>

int window; 

void resize(int width, int height)
{
  // prevent division by zero
  if (height == 0) { height=1; }
  
  glViewport(0, 0, width, height);  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glLoadIdentity();  

  glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) 
{

  if (key == 27)  { 
    glutDestroyWindow(window); 
    exit(0);                   
  }
}

void init(int width, int height)  
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);        
  glDepthFunc(GL_LESS);      
  glEnable(GL_DEPTH_TEST);  
  glShadeModel(GL_SMOOTH);  
  resize(width, height);
}

int main(int argc, char **argv) 
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(2640, 1480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("MainWindow");  
  glutDisplayFunc(&display);  
  glutReshapeFunc(&resize);
  glutKeyboardFunc(&keyPressed);
  init(640, 480);
  glutFullScreen();
  glutMainLoop();  
  return 0;
}
