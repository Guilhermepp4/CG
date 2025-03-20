#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float transx = 0.0;
float transz = 0.0;
float angle = 0.0;
float angle2 = 0.0;
float scale = 1.0;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put axis drawing in here
	glBegin(GL_LINES);
		
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);

		// Y axis in 
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);

		// Z axis in blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);

	glEnd();
	glBegin(GL_TRIANGLES);
	// Triângulo na extremidade do eixo X (Vermelho)
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(2.1f, 0.0f, 0.0f);  
		glVertex3f(2.0f, 0.0f, -0.1f);  
		glVertex3f(2.0f, 0.0f, 0.1f); 

		// Triângulo na extremidade do eixo Y (Verde)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 2.1f, 0.0f);  
		glVertex3f(-0.1f, 2.0f, 0.0f);  
		glVertex3f(0.1f, 2.0f, 0.0f); 

		// Triângulo na extremidade do eixo Z (Azul)
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 2.1f); 
		glVertex3f(0.1f, 0.0f, 2.0f);  
		glVertex3f(-0.1f, 0.0f, 2.0f); 
	glEnd();

// put the geometric transformations here
	glTranslatef(transx, 0.0f, transz);

	glScalef(scale, scale, scale);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glRotatef(angle2, 1.0f, 0.0f, -1.0f);

// put pyramid drawing instructions here
	glBegin(GL_TRIANGLES);		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);

		glColor3f(1.0f, 0.5f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		glColor3f(1.0f, 0.5f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();
	// End of frame

	glutSwapBuffers();
}



// write function to process keyboard events

void alteraPosicao(unsigned char tecla, int x, int y) {
	float move = 0.3;
	float angle1 = 10;
	float angle3 = 10;

		switch (tecla){
			case 'w':
				transx -= move;
				transz -= move;
				break;
			case 's':
				transx += move;
				transz += move;
				break;
			case 'd':
				transx += move;
				transz -= move;
				break;
			case 'a':
				transx -= move;
				transz += move;
				break;
			case 'q':
				angle -= angle1;
				break;
			case 'e':
				angle += angle1;
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

void scaleFunc(int tecla, int x, int y) {
	float size = 1.1;

	switch (tecla){
		case GLUT_KEY_UP:
			scale *= size;
			break;
		case GLUT_KEY_DOWN:
			scale /= size;
			
			break;
	default:
		break;	
	}
	glutPostRedisplay();

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

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(alteraPosicao);
	glutSpecialFunc(scaleFunc);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
