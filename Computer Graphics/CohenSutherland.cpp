#include <iostream>
#include<gl/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static double xmin = -0.5;
static double xmax = 0.5;
static double ymin = -0.5;
static double ymax = 0.5;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

static double p0x, p0y, p1x, p1y;


void convertDeviceXY2OpenglXY(int x, int y, float * ox, float  * oy)
{
	int w = SCREEN_WIDTH;
	int h = SCREEN_HEIGHT;
	*ox = (float)((x - (float)w / 2.0)*(float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0)*(float)(1.0 / (float)(h / 2.0)));
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP); // colored line-loop square
	glColor3f(0.0, 0.0, 0.0);

	glVertex2f(xmin, ymin);

	glVertex2f(xmax, ymin);

	glVertex2f(xmax, ymax);

	glVertex2f(xmin, ymax);

	glEnd();
	glFlush();
}

int inside(int code) {
	return (!code);
}

int reject(int code0, int code1) {
	return int(code0&code1);
}

int accept(int code0, int code1) {
	return int(!(code0 | code1));
}

int encode(double x, double y)
{
	
	int code = INSIDE;          // initialised as being inside of clip window

	if (x < xmin){code = code | LEFT;}           
		
	if (x > xmax){code |= RIGHT;}
		
	if (y < ymin){ code |= BOTTOM; }
		
	if (y > ymax){ code |= TOP; }		

	return code;
}


void cohenSutherland(double x0, double y0, double x1, double y1)
{
	int code0, code1;
	encode(x1, y1);
	bool done = false;

	while (!done) {
		code0 = encode(x0, y0);
		code1 =	encode(x1, y1);
		if ( accept(code0,code1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			done = true;
			break;
		}
		else if (reject(code0,code1)) { // Bitwise AND is not 0. Trivially reject and get out of loop
			done = true;
		}
		else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			int codeOut = code0 ? code0 : code1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (codeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (codeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (codeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else if (codeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}
			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (codeOut == code0) {
				x0 = x;
				y0 = y;
				code0 = encode(x0, y0);
			}
			else {
				x1 = x;
				y1 = y;
				code1 = encode(x1, y1);
			}
		}
	}
	if (done) {
		
		glBegin(GL_LINE_LOOP);

		glColor3f(1.0, 0, 0);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
		glFlush();
	}
}


void processMouse(int button, int state, int x, int y)
{
	float ox;
	float oy;
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			//Left Button code.
			glBegin(GL_LINE_LOOP);
			glColor3f(0.0, 0.0, 0.0);
			convertDeviceXY2OpenglXY(x, y, &ox, &oy);
			glVertex2f(ox, oy);

			p0x = (double)ox;
			p0y = (double)oy;



		}
		else if (button == GLUT_MIDDLE_BUTTON)
		{
			//middle button code
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			//right button code
			convertDeviceXY2OpenglXY(x, y, &ox, &oy);
			glVertex2f(ox, oy);

			glEnd();
			glFlush();

			p1x = (double)ox;
			p1y = (double)oy;

			cohenSutherland(p0x, p0y, p1x, p1y);

		}
	}
	else
	{
		//alternate code
	}
}



int main(int argc, char * argv[]) //argv const
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Cohen-Suferland");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// Set the background colour;
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMainLoop();
	return 0;
}


