#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float angle = 0.0f;
float teapotZ = 0.0f;  // Posição Z inicial do bule

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you can’t make a window with zero width).
    if (h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio = w * 1.0f / h;
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f);

    // Aplicar rotação
    glRotatef(angle, 1.0f, 1.0f, 1.0f);  // Roda no eixo Y

    // Aplicar translação para mover o bule em direção à câmera
    glTranslatef(0.0f, 0.0f, teapotZ);

    glColor3f(0.0f, 0.0f, 1.0f);

    // put drawing instructions here
    glutWireTeapot(1);

    // Atualizar o ângulo para o próximo frame
    angle += 0.1f;
    if (angle > 360.0f) angle -= 360.0f;

    // Atualizar a posição Z do bule para se aproximar da câmera
    teapotZ -= 0.001f;  // Move o bule 0.01 unidades em direção à câmera a cada frame

    // Forçar o redesenho
    glutPostRedisplay();

    // End of frame
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // put GLUT’s init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI");

    // put callback registry here
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUT’s main cycle
    glutMainLoop();

    return 1;
}