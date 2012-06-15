#include "Scene.h"
#include "3rdParty\assimp\assimp.hpp"
#include "3rdParty\assimp\aiScene.h"
#include "3rdParty\assimp\aiPostProcess.h"
#include <iostream>
int window;
int rotation;
char * dir;
aiScene * scene;
float dist;
void resize(int width, int height)
{
  // prevent division by zero
   if (height == 0) { height=1; }

  glViewport(0, 0, width, height);  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, width/height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}
GLenum returnprimitvetype(aiPrimitiveType t)
{
  switch(t)
  {
	case aiPrimitiveType::aiPrimitiveType_LINE:
		return GL_LINES;
	case aiPrimitiveType::aiPrimitiveType_POINT:
		return GL_POINTS;
	case aiPrimitiveType::aiPrimitiveType_POLYGON:
		return GL_POLYGON;
	case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
		return GL_TRIANGLES;
  }
}
void recursive_render (const aiNode* node, aiMatrix4x4 accumulatedTransform)
{
	aiMatrix4x4 transform;
	if (node->mNumMeshes > 0)
	{               
		for (int m=0; m < node->mNumMeshes; m++)
		{
			aiMesh* mesh = scene->mMeshes[m];
			for (int f =0; f< mesh->mNumFaces; f++)
			{
				aiFace * face =  &mesh->mFaces[f];
				glBegin(GL_TRIANGLES);
				::glColor3d(0,1,0);
				for (int v=0; v<3; v++)
				{
						glVertex3f( mesh->mVertices[ face->mIndices[v]].x,mesh->mVertices[ face->mIndices[v]].y,mesh->mVertices[ face->mIndices[v]].z);
				}
				glEnd();
			}
		}
	}
	 else 
     {
		//transform =	node->mTransformation * accumulatedTransform;
		//glLoadIdentity();
		//glMultMatrixf((const GLfloat *) &transform);
     }
	for (int i=0; i<node->mNumChildren; i++)
    {
            recursive_render(node->mChildren[i],transform);
    }
}
void display()
{
  glLoadIdentity();  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  glTranslatef(0,0, dist);
  glRotatef(rotation, 0, 1, 0);
  ::aiMatrix4x4 mat;
  recursive_render(scene->mRootNode, mat);
 
  
 // for (int numMesh = 0; numMesh < scene ->mNumMeshes; numMesh++)
 // {
	//  //glBegin(returnprimitvetype(scene->mMeshes[numMesh]->mPrimitiveTypes));
	//  
	//  glColor3d(0,1,0);
	//  scene->mRootNode-

	//  for(int vcount = 0; vcount < scene->mMeshes[numMesh]->mNumVertices; vcount++)
	//  {

	//	 std::cout<<scene->mMeshes[numMesh]->mNumVertices<<std::endl;
	//	  glVertex3f(scene->mMeshes[numMesh]->mVertices[vcount].x,scene->mMeshes[numMesh]->mVertices[vcount].y, scene->mMeshes[numMesh]->mVertices[vcount].z);
	//  }
	//glEnd();
 // }

  glutSwapBuffers();
  // Now we can access the file's contents. 
  //DoTheSceneProcessing( scene);

	//for(int x = 0; x < 1; x++)
	//{
	//	for(int y = 0; y <1; y++)
	//	{
	//		for(int z = -1; z < 0; z++)
	//		{
	//			glVertex3f(x,y,z);
	//		}
	//	}
	//}

}

void keyPressed(unsigned char key, int x, int y) 
{

  if (key == 27)  
  { 
	  glutDestroyWindow(window); 
    exit(0);                   
  }
  if (key == 'r') { 
  rotation = (rotation + 5) % 360;
  glutPostRedisplay();
}
  if (key == 'w') { 
  dist -= 0.05f;
  glutPostRedisplay();
}
    if (key == 's') { 
  dist += 0.05f;
  glutPostRedisplay();
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

Scene::Scene(int argc, char ** argv)
{
	dist = -6.0f;
	    Assimp::Importer importer;
		(importer.ReadFile( "C:\\Users\\abrajoe\\Documents\\Visual Studio 2010\\Projects\\Piano-Scene\\Debug\\lung.blend", 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType));
  scene  = importer.GetOrphanedScene();
  // If the import failed, report it
  if( !scene)
  {
    printf( importer.GetErrorString());
    return;
  }
  glutInit(&argc, argv);  
  dir = argv[0];
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("foo");  
  glutDisplayFunc(&display);  
  glutReshapeFunc(&resize);
  glutKeyboardFunc(&keyPressed); 



}


void Scene::Show()
{
  init(640, 480);
  glutMainLoop();  
}

Scene::~Scene(void)
{
}
