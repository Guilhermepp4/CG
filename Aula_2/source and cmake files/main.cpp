#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
float angle = 0;
float angle2 = 0;

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

void gera_esfera(float radius, int slices, int stacks) {
	float dPhi = 2 * M_PI / slices;    
	float dTheta = M_PI / stacks;     
	glColor3f(1.0f, 0.0f, 0.8f);

	for (int j = 0; j < stacks; j++) {
		float angle = j * dTheta;         
		float next_angle = (j + 1) * dTheta; 

		for (int i = 0; i < slices; i++) {
			float space = dPhi * i;         
			float next_space = dPhi * (i + 1); 

			float x1 = radius * sin(angle) * cos(space);
			float z1 = radius * sin(angle) * sin(space);

			float x2 = radius * sin(angle) * cos(next_space);
			float z2 = radius * sin(angle) * sin(next_space);
			
			float y = radius * cos(angle);

			float next_x1 = radius * sin(next_angle) * cos(space);
			float next_z1 = radius * sin(next_angle) * sin(space);

			float next_x2 = radius * sin(next_angle) * cos(next_space);
			float next_z2 = radius * sin(next_angle) * sin(next_space);

			float next_y = radius * cos(next_angle);

			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y, z1);
				glVertex3f(next_x1, next_y, next_z1);
				glVertex3f(x2, y, z2);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex3f(x2, y, z2);
				glVertex3f(next_x1, next_y, next_z1);
				glVertex3f(next_x2, next_y, next_z2);
			glEnd();
		}
	}
}

void gera_cone(float radius, float height, int slices, int stacks) {
	float angle = 2 * M_PI / slices;
	float heightBase = height / stacks;

	// Base
	for (int i = 0; i < slices; i++) {
		float x1 = radius * sin(angle * i);
		float z1 = radius * cos(angle * i);
		float x2 = radius * sin(angle * (i + 1));
		float z2 = radius * cos(angle * (i + 1));

		glBegin(GL_TRIANGLES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(x2,0.0, z2);
			glVertex3f(x1, 0.0, z1);
		glEnd();
	}

	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < stacks; j++) {
			float currRadius = radius * (1.0f - float(j) / stacks);
			float nextRadius = radius * (1.0f - float(j + 1) / stacks);

			float x1 = currRadius * sin(angle * i);
			float z1 = currRadius * cos(angle * i);
			float x2 = currRadius * sin(angle * (i + 1));
			float z2 = currRadius * cos(angle * (i + 1));

			float next_x1 = nextRadius * sin(angle * i);
			float next_z1 = nextRadius * cos(angle * i);
			float next_x2 = nextRadius * sin(angle * (i + 1));
			float next_z2 = nextRadius * cos(angle * (i + 1));

			float y = heightBase * j;
			float next_y = heightBase * (j + 1);

			// Left Triangles
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y, z1);
				glVertex3f(x2, y, z2);
				glVertex3f(next_x1, next_y, next_z1);
			glEnd();

			// Right Triangles
			glBegin(GL_TRIANGLES);
				glVertex3f(x2, y, z2);
				glVertex3f(next_x2, next_y, next_z2);
				glVertex3f(next_x1, next_y, next_z1);
			glEnd();
		}
	}
}

void gera_Box(float dimensao, int divisoes) {
	float altura = dimensao / 2;
	float tamanho_divisoes = dimensao / divisoes;
	float dist_centro = dimensao / 2;
	float x1, x2, y1, y2, z1, z2;

	//Base e topo
	for (int i = 0; i < divisoes; i++) {
		z1 = (tamanho_divisoes * i) - dist_centro;
		z2 = (tamanho_divisoes * (i + 1)) - dist_centro;

		for (int j = 0; j < divisoes; j++) {
			x1 = (tamanho_divisoes * j) - dist_centro;
			x2 = (tamanho_divisoes * (j + 1)) - dist_centro;

			// y positivo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, altura, z1);
				glVertex3f(x1, altura, z2);
				glVertex3f(x2, altura, z2);
			glEnd();

			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, altura, z1);
				glVertex3f(x2, altura, z2);
				glVertex3f(x2, altura, z1);
			glEnd();

			// y negativo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, -altura, z1);
				glVertex3f(x2, -altura, z2);
				glVertex3f(x1, -altura, z2);
			glEnd();

			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, -altura, z1);
				glVertex3f(x2, -altura, z1);
				glVertex3f(x2, -altura, z2);
			glEnd();
		}
	}

	//Laterais sobre o eixo dos x
	for (int i = 0; i < divisoes; i++) {
		y1 = (tamanho_divisoes * i) - dist_centro;
		y2 = (tamanho_divisoes * (i + 1)) - dist_centro;

		for (int j = 0; j < divisoes; j++) {
			z1 = (tamanho_divisoes * j) - dist_centro;
			z2 = (tamanho_divisoes * (j + 1)) - dist_centro;

			// x negativo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(-dist_centro, y1, z1);
				glVertex3f(-dist_centro, y1, z2);
				glVertex3f(-dist_centro, y2, z2);
			glEnd();

			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(-dist_centro, y1, z1);
				glVertex3f(-dist_centro, y2, z2);
				glVertex3f(-dist_centro, y2, z1);
			glEnd();
			
			// x positivo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(dist_centro, y2, z2);
				glVertex3f(dist_centro, y1, z2);
				glVertex3f(dist_centro, y1, z1);
			glEnd();
			
			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(dist_centro, y2, z2);
				glVertex3f(dist_centro, y1, z1);
				glVertex3f(dist_centro, y2, z1);
			glEnd();
			
		}

	}

	// Laterais sobre o eixo dos z
	for (int i = 0; i < divisoes; i++) {
		y1 = (tamanho_divisoes * i) - dist_centro;
		y2 = (tamanho_divisoes * (i + 1)) - dist_centro;

		for (int j = 0; j < divisoes; j++) {
			x1 = (tamanho_divisoes * j) - dist_centro;
			x2 = (tamanho_divisoes * (j + 1)) - dist_centro;

			// z negativo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y2, -dist_centro);
				glVertex3f(x2, y1, -dist_centro);
				glVertex3f(x1, y1, -dist_centro);
			glEnd();

			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y2, -dist_centro);
				glVertex3f(x2, y2, -dist_centro);
				glVertex3f(x2, y1, -dist_centro);
			glEnd();

			// z positivo
			// Triangulo 1
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y2, dist_centro);
				glVertex3f(x1, y1, dist_centro);
				glVertex3f(x2, y1, dist_centro);
			glEnd();

			// Triangulo 2
			glBegin(GL_TRIANGLES);
				glVertex3f(x1, y2, dist_centro);
				glVertex3f(x2, y1, dist_centro);
				glVertex3f(x2, y2, dist_centro);
			glEnd();

		}
	}
}

void drawCylinder(float radius, float height, int slices) {

	float angleStep = 2.0f * M_PI / slices;  
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.8f); 
		glVertex3f(0.0f, 0.0f, 0.0f); 

		for (int i = 0; i <= slices; i++) {
			float angle = i * angleStep;
			float x = radius * sin(-angle);
			float z = radius * cos(-angle);
			glVertex3f(x, 0.0f,z);
		}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, height, 0.0f);

		for (int i = 0; i <= slices; i++) {
			float angle = i * angleStep;
			float x = radius * sin(angle);
			float z = radius * cos(angle);
			glVertex3f(x, height, z);
		}
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.5f);
		for (int i = 0; i <= slices; i++) {
			float angle = i * angleStep;
			float angle2 = (i+1) * angleStep;
			float x = radius * sin(angle);
			float z = radius * cos(angle);
			float x2 = radius * sin(angle2);
			float z2 = radius * cos(angle2);
			glVertex3f(x, height, z);
			glVertex3f(x2, 0.0f, z2);
			glVertex3f(x2, height, z2);
		}
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.5f);
		for (int i = 0; i <= slices; i++) {
			float angle = i * angleStep;
			float angle2 = (i + 1) * angleStep;
			float x = radius * sin(angle);
			float z = radius * cos(angle);
			float x2 = radius * sin(angle2);
			float z2 = radius * cos(angle2);
			glVertex3f(x, 0.0f , z);
			glVertex3f(x2, 0.0f, z2);
			glVertex3f(x, height, z);
	}
	glEnd();
}

void gera_Cylinder(float radius, float height, int slices) {
	glColor3f(1.0f, 0.0f, 0.0f);
	float angleStep = 2.0f * M_PI / slices;
	for (int i = 0; i < slices; i++) {
		float angle = i * angleStep;
		float next_angle = (i + 1) * angleStep;
		float x1 = radius * sin(angle);
		float z1 = radius * cos(angle);
		float x2 = radius * sin(next_angle);
		float z2 = radius * cos(next_angle);

		// Bottom Base
		glBegin(GL_TRIANGLES);
			glVertex3f(x2, 0.0f, z2);
			glVertex3f(x1, 0.0f, z1);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();

		// Top Base
		glBegin(GL_TRIANGLES);
			glVertex3f(x1, height, z1);
			glVertex3f(x2, height, z2);
			glVertex3f(0.0f, height, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(x1, 0.0f, z1);
			glVertex3f(x2, 0.0f, z2);
			glVertex3f(x1, height, z1);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(x2, 0.0f, z2);
			glVertex3f(x2, height, z2);
			glVertex3f(x1, height, z1);
		glEnd();
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,0.0,5.0, 
		      0.0,1.0,0.0,
			  0.0f,1.0f,0.0f);
	// put axis drawing in here
	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);

	// Y axis in 
	glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);

	// Z axis in blue
	glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);

	glEnd();
	// angle = fmin(fmax(-90.0, angle), 90.0);
	glRotatef(angle, 1.0f, 0.0f, -1.0f);
	glRotatef(angle2, 0.0f, 1.0f, 0.0f);

	gera_esfera(1, 30, 30);
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

	float angle1 = 10;
	float angle3 = 10;

	switch (c) {
		case 'q':
			angle += angle1;
			break;
		case 'e':
			angle -= angle1;
			break;
		case 'z':
			angle2 += angle3;
			break;
		case 'c':
			angle2 -= angle3;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

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
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
