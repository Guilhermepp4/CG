#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
float radiusCone = 1;
float height = 3;
float angle = 0.0f;
float angle2 = 0.0f;

float radiusTea = 15.0f;
float radiusTea2 = 35.0f;
float radiusTrunk = 0.5f;
float trunkHeight = 2.0f;

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawTrees(void) {
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
	glVertex3f(100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, 100.0f);

	glVertex3f(100.0f, 0, -100.0f);
	glVertex3f(-100.0f, 0, 100.0f);
	glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	// put code to draw scene in here
	glColor3f(0.5f, 1.0f, 0.5f);
	srand(0);

	for (int i = 0; i < 300; i++) {
		float x, z;

		do {
			x = (rand() % 201) - 100;
			z = (rand() % 201) - 100;

		} while (x * x + z * z < 50 * 50);


		glPushMatrix();
		glTranslatef(x, trunkHeight / 2.0f, z);
		glColor3f(0.82f, 0.41f, 0.12f);
		glRotatef(-90, 1.0, 0.0, 0.0);
		GLUquadric* quad = gluNewQuadric();
		gluCylinder(quad, radiusTrunk, radiusTrunk, trunkHeight, 15, 15);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x, trunkHeight, z);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCone(1, 3, 15, 15);
		glPopMatrix();

	}
}

void drawTorus(void) {
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.43f, 0.71f);
		glutSolidTorus(2.0f, 4.0f, 15, 15);
	glPopMatrix();
}

void drawTeapot(void) {
	// Desenha 8 cilindros em posições circulares
	for (int i = 0; i < 8; i++) {
		float theta = i * (360 / 8) + angle;


		// Desenha o teapot
		glPushMatrix();
		glRotatef(theta, 0.0f, 1.0f, 0.0f);
		glTranslatef(radiusTea, 2.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidTeapot(2.0f);
		glPopMatrix();
	}
	angle -= 0.5;


	for (int i = 0; i < 16; i++) {
		float theta2 = i * (360 / 16) + angle2;

		glPushMatrix();
		glRotatef(theta2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 2.0f, radiusTea2);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidTeapot(2.0f);
		glPopMatrix();
	}
	angle2 += 0.5;
}
void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	drawTrees();
	drawTorus();
	drawTeapot();
	glutSwapBuffers();
}



void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
