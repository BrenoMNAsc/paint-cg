#include "transformacoes.h"

#include <stdlib.h>
#include <stdio.h>

void calcularCentroideLinha(Linha* linha) {
    linha->xcentroide = (linha->inicio.x + linha->fim.x) / 2.0;
    linha->ycentroide = (linha->inicio.y + linha->fim.y) / 2.0;
}

void calcularCentroidePoligono(Poligono* poligono) {
    float soma_x = 0.0;
    float soma_y = 0.0;

    for (int i = 0; i < poligono->num_pontos; i++) {
        soma_x += poligono->pontos[i].x;
        soma_y += poligono->pontos[i].y;
    }

    poligono->xcentroide = soma_x / poligono->num_pontos;
    poligono->ycentroide = soma_y / poligono->num_pontos;
}

void multMatrizPonto(GLfloat matriz[3][3], Ponto* ponto) {
    GLfloat x = ponto->x;
    GLfloat y = ponto->y;
    GLfloat w = 1.0;

    ponto->x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2] * w;
    ponto->y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2] * w;
}

void multMatrizLinha(GLfloat matriz[3][3], Linha* linha) {
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
}

void multMatrizPoligono(GLfloat matriz[3][3], Poligono* poligono) {
    for (int i = 0; i < poligono->num_pontos; i++) {
        GLfloat x = poligono->pontos[i].x;
        GLfloat y = poligono->pontos[i].y;
        GLfloat w = 1.0;

        poligono->pontos[i].x = matriz[0][0] * x + matriz[0][1] * y + matriz[0][2] * w;
        poligono->pontos[i].y = matriz[1][0] * x + matriz[1][1] * y + matriz[1][2] * w;
    }
}

void transladar(GLfloat tx, GLfloat ty, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_translacao[3][3] = {
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_translacao, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_translacao, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_translacao, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void rotacionar(GLfloat angulo, void* objeto, TipoObjeto tipo) {
    GLfloat cose = cos(angulo * M_PI / 180.0);
    GLfloat sen = sin(angulo * M_PI / 180.0);

    GLfloat matriz_rotacao[3][3] = {
        {cose, -sen, 0.0},
        {sen, cose, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_rotacao, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_rotacao, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_rotacao, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void escalar(GLfloat sx, GLfloat sy, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_escalar[3][3] = {
        {sx, 0.0, 0.0},
        {0.0, sy, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_escalar, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_escalar, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_escalar, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void cisalhamento_x(GLfloat c, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, c, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_cisalhamento, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_cisalhamento, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_cisalhamento, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void cisalhamento_y(GLfloat c, void* objeto, TipoObjeto tipo) {
    GLfloat matriz_cisalhamento[3][3] = {
        {1.0, 0.0, 0.0},
        {c, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_cisalhamento, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_cisalhamento, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_cisalhamento, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void reflexao_vertical(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_reflexao, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_reflexao, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_reflexao, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void reflexao_horizontal(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_reflexao, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_reflexao, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_reflexao, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}

void reflexao_diagonal(void* objeto, TipoObjeto tipo) {
    GLfloat matriz_reflexao[3][3] = {
        {-1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    switch (tipo) {
        case PONTO:
            multMatrizPonto(matriz_reflexao, (Ponto*)objeto);
            break;
        case LINHA:
            multMatrizLinha(matriz_reflexao, (Linha*)objeto);
            break;
        case POLIGONO:
            multMatrizPoligono(matriz_reflexao, (Poligono*)objeto);
            break;
        default:
            printf("Tipo de objeto desconhecido.\n");
            break;
    }
}
