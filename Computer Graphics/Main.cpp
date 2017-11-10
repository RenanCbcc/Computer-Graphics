#include <gl/glut.h>
#include "Bresenham.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
struct Colour {
	GLfloat   r;
	GLfloat   g;
	GLfloat   b;

	bool operator!=(const Colour& colour) const {
		return ((colour.r != this->r) || (colour.g != this->g) || (colour.b != this->b));
	}
};

void init();
void drawLine();
void drawCircle();
void drawPoly();
void example();
void floodFill(GLint x, GLint y, Colour oldColor, Colour newColor);
void onMouseClick(int button, int state, int x, int y);
void setPixelColour(GLint x, GLint y, Colour colour);
Colour getPixelColour(GLint x, GLint y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Bresenham's Tribute");
	init();
	//glutDisplayFunc(example);
	//glutDisplayFunc(drawLine);
	glutDisplayFunc(drawCircle);
	//glutDisplayFunc(drawPoly);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}

void init() {
	/*We can set the projection type (The manner Opengl will transform  3d into 2d ) and
	other necessaries viewing parameters with the following two functions:
	OBS: Search for Orthogonal projection.
	*/
	glColor3f(0.0f, 0.0f, 0.0f); // Set the object colour;
	glClearColor(1.0f, 1.0f, 1.0f,1.0f);// Set the background colour;
	glMatrixMode(GL_PROJECTION); // Projection matrix defines the properties of the camera that views the objects in the world coordinate frame.
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // Essentially set coordinate system, anything outside this coordenate range will not be displayed.
	glPointSize(1);
}

void drawLine() {
	Bresenham bresenham(SCREEN_WIDTH, SCREEN_HEIGHT);
	bresenham.line(0, 0, 200, 300);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int x = 0; x< bresenham.buffer.size(); x++) {
		for (int y = 0; y< bresenham.buffer[x].size(); y++)
		{
			if (bresenham.buffer[x][y] != 0)
				glVertex2i(x, y);
		}
	}

	glEnd();
	glFlush();

}

void drawCircle() {
	Bresenham bresenham(SCREEN_WIDTH, SCREEN_HEIGHT);
	bresenham.circle(300, 300, 30);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	for (int x = 0; x< bresenham.buffer.size(); x++) {
		for (int y = 0; y< bresenham.buffer[x].size(); y++)
		{
			if (bresenham.buffer[x][y] != 0)
			glVertex2i(x,y);
		}
	}
	
	glEnd();
	glFlush();

}
void drawPoly() {
	Bresenham bresenham(SCREEN_WIDTH, SCREEN_HEIGHT);
	bresenham.polygon();

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	for (int x = 0; x< bresenham.buffer.size(); x++) {
		for (int y = 0; y< bresenham.buffer[x].size(); y++)
		{
			if (bresenham.buffer[x][y] != 0)
				glVertex2i(x, y);
		}
	}

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

void floodFill(GLint x, GLint y, Colour colour, Colour edgeColor) {

	Colour current = getPixelColour(x, y);

	if (current != edgeColor && current != colour)
	{
				setPixelColour(x, y, colour);
				floodFill(x + 1, y, colour, edgeColor);
				floodFill(x, y + 1, colour, edgeColor);
				floodFill(x - 1, y, colour, edgeColor);
				floodFill(x, y - 1, colour, edgeColor);
	
	}	
	return;
}

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

void onMouseClick(int button, int state, int x, int y)
{
	Colour edgeColor = { 0.0f, 0.0f, 0.0f };
	Colour newColour = { 0.0f, 1.0f, 0.0f };
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	floodFill(x, y, newColour, edgeColor);
}
