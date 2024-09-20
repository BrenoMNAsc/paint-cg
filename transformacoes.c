#include "transformacoes.h"

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
