#include <stdio.h>
#include "objetos.h"
#include <stdlib.h>
#include <GL/glut.h>

// Variáveis globais
Ponto ponto_inicial_linha;
int esperando_segundo_ponto = 0;  // Flag para saber se estamos aguardando o segundo ponto da linha

ObjetosGeometricos criar_objetos() {
    ObjetosGeometricos objs;
    objs.pontos = NULL;
    objs.linhas = NULL;
    objs.poligonos = NULL;
    objs.num_pontos = objs.num_linhas = objs.num_poligonos = 0;
    return objs;
}

// Função para adicionar linha
void adicionar_linha(ObjetosGeometricos* objetos, float x, float y) {
    if (esperando_segundo_ponto == 0) {
        // Primeiro clique, armazena o ponto inicial
        ponto_inicial_linha.x = x;
        ponto_inicial_linha.y = y;
        esperando_segundo_ponto = 1;  // Agora espera o segundo ponto
        printf("Primeiro ponto da linha: (%f, %f)\n", x, y);
        adicionar_ponto(objetos, x, y);
    } else {
        // Segundo clique, armazena o ponto final e adiciona a linha
        remover_ultimo_ponto(objetos);
        objetos->linhas = realloc(objetos->linhas, (objetos->num_linhas + 1) * sizeof(Linha));
        if (objetos->linhas == NULL) {
            fprintf(stderr, "Erro ao alocar memória para as linhas.\n");
            exit(EXIT_FAILURE);
        }
        // Define os pontos da linha
        objetos->linhas[objetos->num_linhas].inicio = ponto_inicial_linha;
        objetos->linhas[objetos->num_linhas].fim.x = x;
        objetos->linhas[objetos->num_linhas].fim.y = y;

        // Incrementa o número de linhas
        objetos->num_linhas++;
        esperando_segundo_ponto = 0;  // Reset para a próxima linha

        printf("Linha adicionada: (%f, %f) -> (%f, %f)\n", ponto_inicial_linha.x, ponto_inicial_linha.y, x, y);
    }
}

void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y) {
    objetos->pontos = realloc(objetos->pontos, (objetos->num_pontos + 1) * sizeof(Ponto));
    if (objetos->pontos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os pontos.\n");
        exit(EXIT_FAILURE);
    }
    objetos->pontos[objetos->num_pontos].x = x;
    objetos->pontos[objetos->num_pontos].y = y;
    objetos->num_pontos++;
}

void remover_ultimo_ponto(ObjetosGeometricos* objetos) {
    if (objetos->num_pontos > 0) {
        // Decrementa o número de pontos
        objetos->num_pontos--;

        // Realoca a memória para remover o último ponto
        objetos->pontos = realloc(objetos->pontos, objetos->num_pontos * sizeof(Ponto));

        // Verifica se a realocação ocorreu corretamente
        if (objetos->num_pontos > 0 && objetos->pontos == NULL) {
            fprintf(stderr, "Erro ao realocar memória após remover ponto.\n");
            exit(EXIT_FAILURE);
        }

        printf("Ponto removido. Agora há %d pontos.\n", objetos->num_pontos);
    } else {
        printf("Nenhum ponto para remover.\n");
    }
}


void adicionar_poligono(ObjetosGeometricos* objetos) {
    // Implementação futura para adicionar polígonos
}

// Função
void desenhar_objetos(ObjetosGeometricos* objetos) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < objetos->num_pontos; i++) {
        glVertex2f(objetos->pontos[i].x, objetos->pontos[i].y);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < objetos->num_linhas; i++) {
        glVertex2f(objetos->linhas[i].inicio.x, objetos->linhas[i].inicio.y);
        glVertex2f(objetos->linhas[i].fim.x, objetos->linhas[i].fim.y);
    }
    glEnd();

    glFlush();
}
