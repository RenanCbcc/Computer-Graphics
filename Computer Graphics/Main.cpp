#include <gl/glut.h>
#include "Bresenham.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
void init();
void drawLine();
void drawCircle();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Bresenham's Tribute");
	glutDisplayFunc(drawLine);
	//glutDisplayFunc(drawCircle);
	init();
	glutMainLoop();
}

void init() {
	/*We can set the projection type (The manner Opengl will transform  3d into 2d ) and
	other necessaries viewing parameters with the following two functions:
	OBS: Search for Orthogonal projection.
	*/
	glColor3f(0.0, 0.0, 0.0); // Set the object colour;
	glClearColor(1.0, 1.0, 1.0, 1.0);// Set the background colour;
	glMatrixMode(GL_PROJECTION); // Projection matrix defines the properties of the camera that views the objects in the world coordinate frame.
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // Essentially set coordinate system, anything outside this coordenate range will not be displayed.

}

void drawLine() {
	Bresenham bresh(SCREEN_WIDTH, SCREEN_HEIGHT);
	bresh.line(0, 0, 200, 300);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int i = 0; i < bresh.point.size(); i++) {
		glVertex2i(bresh.point[i].getXcoodinate(), bresh.point[i].getYcoodinate());
	}
	glEnd();
	glFlush();

}
void drawCircle() {
	Bresenham bresh(SCREEN_WIDTH, SCREEN_HEIGHT);
	bresh.circle(300, 300, 100);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int i = 0; i < bresh.point.size(); i++) {
		glVertex2i(bresh.point[i].getXcoodinate(), bresh.point[i].getYcoodinate());
	}
	glEnd();
	glFlush();

}
void fillIn() {}