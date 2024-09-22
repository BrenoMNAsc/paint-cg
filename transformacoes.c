#include "transformacoes.h"
#include "objetos.h"

#include <stdlib.h>
#include <stdio.h>

void multMatriz(GLfloat matriz[3][3], void* objeto, TipoObjeto tipo) {
    switch (tipo) {
        case PONTO: {
            Ponto* ponto = (Ponto*)objeto;
            GLfloat x = ponto->x;
            GLfloat y = ponto->y;
            GLfloat w = 1.0;

            ponto->x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2] * w;
            ponto->y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2] * w;
            break;
        }
        case LINHA: {
            Linha* linha = (Linha*)objeto;

            GLfloat x1 = linha->inicio.x;
            GLfloat y1 = linha->inicio.y;
            GLfloat w1 = 1.0;

            linha->inicio.x = matriz[0][0] * x1 + matriz[0][1] * y1 + matriz[0][2] * w1;
            linha->inicio.y = matriz[1][0] * x1 + matriz[1][1] * y1 + matriz[1][2] * w1;

            GLfloat x2 = linha->fim.x;
            GLfloat y2 = linha->fim.y;
            GLfloat w2 = 1.0;

            linha->fim.x = matriz[0][0] * x2 + matriz[0][1] * y2 + matriz[0][2] * w2;
            linha->fim.y = matriz[1][0] * x2 + matriz[1][1] * y2 + matriz[1][2] * w2;
            break;
        }
        case POLIGONO: {


            for (int i = 0; i < poligono->num_pontos; i++) {
                GLfloat x = poligono->pontos[i].x;
                GLfloat y = poligono->pontos[i].y;
                GLfloat w = 1.0;

                poligono->pontos[i].x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2] * w;
                poligono->pontos[i].y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2] * w;
            }
            break;
        }
    }
}


void transladar(GLfloat tx, GLfloat ty, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_translacao[3][3] = {
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_translacao, &objeto, tipo);
}

void rotacionar(GLfloat angulo, void* objeto, TipoObjeto tipo) {
    GLfloat cose = cos(angulo * M_PI / 180.0);
    GLfloat sen = sin(angulo * M_PI / 180.0);

    GLfloat matriz_rotacao[3][3] = {
        {cose, -sen, 0.0},
        {sen, cose, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_rotacao, &objeto, tipo);
}

void escalar(GLfloat sx, GLfloat sy, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_escalar[3][3] = {
        {sx, 0.0, 0.0},
        {0.0, sy, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_escalar, &objeto, tipo);
}

void cisalhamento_x(GLfloat c, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, c, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_cisalhamento, &objeto, tipo);
}

void cisalhamento_y(GLfloat c, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, 0.0, 0.0},
        {c, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_cisalhamento, &objeto, tipo);
}

void reflexao_vertical(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, &objeto, tipo);
}

void reflexao_horizontal(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, &objeto, tipo);
}

void reflexao_diagonal(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
    multMatriz(matriz_reflexao, &objeto, tipo);
}
