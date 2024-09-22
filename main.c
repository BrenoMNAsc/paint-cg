#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Ponto;

Ponto triangulo[3] = {
    {-60.0, -10.0},
    {-30.0, -10.0},
    {-45.0, 30.0}
};

Ponto centroide;

void calcularCentroide(Ponto* pontos, int num_pontos, Ponto* centroide) {
    float soma_x = 0.0;
    float soma_y = 0.0;
    for (int i = 0; i < num_pontos; i++) {
        soma_x += pontos[i].x;
        soma_y += pontos[i].y;
    }
    centroide->x = soma_x / num_pontos;
    centroide->y = soma_y / num_pontos;
    printf("centralX: %f, centralY: %f\n", centroide->x, centroide->y);
}

void multMatriz(GLfloat matriz[3][3], Ponto* pontos, int num_pontos) {
    for (int i = 0; i < num_pontos; i++) {
        GLfloat x = pontos[i].x;
        GLfloat y = pontos[i].y;
        GLfloat w = 1.0;

        GLfloat novo_x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2] * w;
        GLfloat novo_y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2] * w;

        pontos[i].x = novo_x;
        pontos[i].y = novo_y;
    }
}

void transladar(GLfloat tx, GLfloat ty) {
    GLfloat matriz_translacao[3][3] = {
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_translacao, triangulo, 3);
}

void rotacionar(GLfloat angulo) {
    GLfloat cose = cos(angulo * M_PI / 180.0);
    GLfloat sen = sin(angulo * M_PI / 180.0);

    GLfloat matriz_rotacao[3][3] = {
        {cose, -sen, 0.0},
        {sen, cose, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_rotacao, triangulo, 3);
}

void escalar(GLfloat sx, GLfloat sy) {
    GLfloat matriz_escalar[3][3] = {
        {sx, 0.0, 0.0},
        {0.0, sy, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_escalar, triangulo, 3);
}

void cisalhamento_x(GLfloat c) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, c, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_cisalhamento, triangulo, 3);
}

void cisalhamento_y(GLfloat c) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, 0.0, 0.0},
        {c, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_cisalhamento, triangulo, 3);
}

void reflexao_vertical() {
    GLfloat matriz_reflexao[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, triangulo, 3);
}

void reflexao_horizontal() {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, triangulo, 3);
}

void reflexao_diagonal() {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, triangulo, 3);
}

void criar_triangulo() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 3; i++) {
        glVertex2f(triangulo[i].x, triangulo[i].y);
    }
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
        criar_triangulo();
    glPopMatrix();
    for (int i = 0; i < 3; i++) {
        printf("x:%f y:%f\n", triangulo[i].x, triangulo[i].y);
    }
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 't':
            transladar(0, 10);
            glutPostRedisplay();
            break;
        case 'r':
            calcularCentroide(triangulo, 3, &centroide);
            transladar(-centroide.x, -centroide.y);
            rotacionar(90);
            transladar(centroide.x, centroide.y);
            glutPostRedisplay();
            break;
        case 'e':
            calcularCentroide(triangulo, 3, &centroide);
            transladar(-centroide.x, -centroide.y);
            escalar(2, 2);
            transladar(centroide.x, centroide.y);
            glutPostRedisplay();
            break;
        case 'x':
            cisalhamento_x(2);
            glutPostRedisplay();
            break;
        case 'y':
            cisalhamento_y(2);
            glutPostRedisplay();
            break;
        case 'v':
            reflexao_vertical();
            glutPostRedisplay();
            break;
        case 'h':
            reflexao_horizontal();
            glutPostRedisplay();
            break;
        case 'd':
            reflexao_diagonal();
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Paint");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
