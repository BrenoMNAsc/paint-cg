#include "transformacoes.h"

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
