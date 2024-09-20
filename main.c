#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Ponto;

GLfloat triangulo[3][2] = {
    {-40.0, -10.0},
    {-20.0, -10.0},
    {-30.0, 10.0}
};

Ponto centroide_triangulo(GLfloat triangulo[][2]) {
    Ponto centroide;
    centroide.x = 0;
    centroide.y = 0;
    for (int i = 0; i < 3; i++) {
        centroide.x += triangulo[i][0];
        centroide.y += triangulo[i][1];
    }
    centroide.x /= 3;
    centroide.y /= 3;
    return centroide;
}

void transladar(GLfloat tx, GLfloat ty) {
    GLfloat matriz_translacao[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        tx, ty, 0.0, 1.0
    };

    glMultMatrixf(matriz_translacao);
}

void rotacionar(GLfloat angulo) {
    // transformar graus em radianos, pois a funcao cos e sin trabalham com radianos
    GLfloat cose = cos(angulo * M_PI / 180.0);
    GLfloat sen = sin(angulo * M_PI / 180.0);

    GLfloat matriz_rotacao[16] = {
        cose, sen, 0.0, 0.0,
        -sen, cose, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_rotacao);
}

void escalar(GLfloat x, GLfloat y) {
    GLfloat matriz_escala[16] = {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_escala);
}

void reflexao_vertical() {
    GLfloat matriz_reflexao[16] = {
        1.0,  0.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 0.0,
        0.0,  0.0, 1.0, 0.0,
        0.0,  0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_reflexao);
}

void reflexao_horizontal() {
    GLfloat matriz_reflexao[16] = {
        -1.0,  0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0,  0.0, 1.0, 0.0,
        0.0,  0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_reflexao);
}

void reflexao_diagonal() {
    GLfloat matriz_reflexao[16] = {
        -1.0, 0.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 0.0,
        0.0,  0.0, 1.0, 0.0,
        0.0,  0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_reflexao);
}

void cisalhamento_y(GLfloat c) {
    GLfloat matriz_cisalhamento[16] = {
        1.0, c, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0,  0.0, 1.0, 0.0,
        0.0,  0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_cisalhamento);
}

void cisalhamento_x(GLfloat c) {
    GLfloat matriz_cisalhamento[16] = {
        1.0, 0.0, 0.0, 0.0,
        c, 1.0, 0.0, 0.0,
        0.0,  0.0, 1.0, 0.0,
        0.0,  0.0, 0.0, 1.0
    };

    glMultMatrixf(matriz_cisalhamento);
}

void criar_triangulo() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(triangulo[i]);
    }
    glEnd();
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
        Ponto centro = centroide_triangulo(triangulo);
        transladar(centro.x, centro.y);
        rotacionar(90);
        transladar(-centro.x, -centro.y);
        Ponto centro2 = centroide_triangulo(triangulo);
        transladar(centro2.x, centro2.y);
        escalar(2.0, 2.0);
        transladar(-centro2.x, -centro2.y);
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

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
