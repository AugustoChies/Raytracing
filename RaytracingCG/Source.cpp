#include "Input.h"
#include "Output.h"
#include "Filter.h"
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <GL/gl.h>
#include <freeglut\glut.h>

using namespace std;

Render *renderer;
Image *img;



void init(void)
{
	img = new Image(300, 300);
	//img = Input::loadImage("imagem.ptm");
	renderer = Input::loadScene("scenefile.txt");
	
	
	/*  select clearing (background) color       */
	glClearColor(0, 0, 0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, img->getWidth(), 0.0, img->getHeight(), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(img->getWidth(), img->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE,
		img->getPixels());


	glFlush();
}

int main(int argc, char** argv)
{
	


	init();

	renderer->run(img,60);
	//Output::saveImage(img, "DefaultSave.ptm");
	
	Filter::greyScale(img);
	Filter::sobel(img);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(img->getWidth(), img->getHeight());
	glutInitWindowPosition(300, 100);
	glutCreateWindow("hello");
	glutDisplayFunc(display);
	
	glutMainLoop();
	

	return 0;
}