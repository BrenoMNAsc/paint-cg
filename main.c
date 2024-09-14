#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

typedef struct {
    float x;
    float y;
} Ponto;

GLfloat triangulo[3][2] = {
    {-50.0, -10.0},
    {-30.0, -10.0},
    {-40.0, 10.0}
};

GLfloat triangulo_x = 0;
GLfloat triangulo_y = 0;

void especial(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            triangulo_x -= 5.0;
            break;
        case GLUT_KEY_RIGHT:
            triangulo_x += 5.0;
            break;
        case GLUT_KEY_UP:
            triangulo_y += 5.0;
            break;
        case GLUT_KEY_DOWN:
            triangulo_y -= 5.0;
            break;
    }
    glutPostRedisplay();
}

void translate2D(GLfloat tx, GLfloat ty) {
    glTranslatef(tx, ty, 0.0f);
}

void criar_triangulo() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(triangulo[i]);
    }
    glEnd();
}

Ponto centroide_triangulo(GLfloat triangulo[3][2], GLfloat tx, GLfloat ty) {
    Ponto centroide;
    centroide.x = 0;
    centroide.y = 0;
    for (int i = 0; i < 3; i++) {
        centroide.x += triangulo[i][0] + tx;
        centroide.y += triangulo[i][1] + ty;
    }
    centroide.x /= 3;
    centroide.y /= 3;
    return centroide;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
        Ponto centro = centroide_triangulo(triangulo, triangulo_x, triangulo_y);
        translate2D(triangulo_x, triangulo_y);
        criar_triangulo();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Paint");

    glutSpecialFunc(especial);
    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
