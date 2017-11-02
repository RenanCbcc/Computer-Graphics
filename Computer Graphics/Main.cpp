#include <gl/glut.h>
#include "Bresenham.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
void init();
void drawLine();
void drawCircle();
void drawPoly();
void example();
void floodFill(GLint x, GLint y, Colour oldColor, Colour newColor);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Bresenham's Tribute");
	init();
	//glutDisplayFunc(example);
	//glutDisplayFunc(drawLine);
	//glutDisplayFunc(drawCircle);
	glutDisplayFunc(drawPoly);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
}

void init() {
	/*We can set the projection type (The manner Opengl will transform  3d into 2d ) and
	other necessaries viewing parameters with the following two functions:
	OBS: Search for Orthogonal projection.
	*/
	glColor3f(1.0, 1.0, 1.0); // Set the object colour;
	glClearColor(0.0, 0.0, 0.0, 0.0);// Set the background colour;
	glMatrixMode(GL_PROJECTION); // Projection matrix defines the properties of the camera that views the objects in the world coordinate frame.
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // Essentially set coordinate system, anything outside this coordenate range will not be displayed.
	glPointSize(5);
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

void drawPoly() {

	glBegin(GL_LINES);
	// l1
	glVertex2i(150, 200);
	glVertex2i(100, 300);
	// l2
	glVertex2i(150, 200);
	glVertex2i(300, 200);

	// l3
	glVertex2i(300, 200);
	glVertex2i(350, 300);

	// l3
	glVertex2i(100, 300);
	glVertex2i(350, 300);

	// l5
	glVertex2i(200, 300);
	glVertex2i(250, 350);

	// l6
	glVertex2i(250, 350);
	glVertex2i(350, 300);

	glEnd();
	glFlush();

}

void example() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glVertex2i(50, 100);
	glVertex2i(75, 150);
	glVertex2i(100, 200);
	glVertex2i(150, 280);
	glVertex2i(200, 340);
	glVertex2i(250, 390);
	glVertex2i(300, 460);
	glEnd();

	glFlush();

}

void floodFill(GLint x, GLint y, Colour oldColour, Colour newColour) {

	Colour colour;
	colour = getPixelColour(x, y);

	if (colour.r == oldColour.r && colour.g == oldColour.g && colour.b == oldColour.b)
	{
		setPixelColour(x, y, newColour);
		floodFill(x + 1, y, oldColour, newColour);
		floodFill(x, y + 1, oldColour, newColour);
		floodFill(x - 1, y, oldColour, newColour);
		floodFill(x, y - 1, oldColour, newColour);
	}
	return;
}

//this function is used for getting color of pixel
Colour getPixelColour(GLint x, GLint y) {
	Colour colour;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &colour);
	return colour;
}

void setPixelColour(GLint x, GLint y, Colour colour) {
	glColor3f(colour.r, colour.g, colour.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
struct Colour {
	GLubyte  r;
	GLubyte  g;
	GLubyte  b;
};

void onMouseClick(int button, int state, int x, int y)
{
	Colour newColour = { 1.0f, 0.0f, 0.0f };
	Colour oldColour = { 1.0f, 1.0f, 1.0f };

	floodFill(x, y, oldColour, newColour);
}
