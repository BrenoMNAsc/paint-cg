#include <stdio.h>
#include "objetos.h"
#include <stdlib.h>
#include <GL/glut.h>

// Variáveis globais
Ponto ponto_inicial_linha;
int esperando_segundo_ponto = 0;  // Flag para saber se estamos aguardando o segundo ponto da linha

// Variáveis estáticas para o polígono
Ponto* pontos_poligono = NULL;  // Armazena os pontos temporários do polígono
int num_pontos_poligono = 0;    // Conta o número de pontos temporários do polígono

ObjetosGeometricos criar_objetos() {
    ObjetosGeometricos objs;
    objs.pontos = NULL;
    objs.linhas = NULL;
    objs.poligonos = NULL;
    objs.num_pontos = objs.num_linhas = objs.num_poligonos = 0;
    objs.linha_selecionada, objs.ponto_selecionado, objs.poligono_selecionado = -1;
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

        // Redesenhar a tela
        glutPostRedisplay();
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

    printf("Ponto: (%f, %f)\n", x, y);

    // Redesenhar a tela
    glutPostRedisplay();
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

        // Redesenhar a tela
        glutPostRedisplay();
    } else {
        printf("Nenhum ponto para remover.\n");
    }
}

void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar) {
    if (!finalizar) {
        // Adicionar ponto ao polígono
        adicionar_ponto(objetos, novo_ponto.x, novo_ponto.y);
        pontos_poligono = realloc(pontos_poligono, (num_pontos_poligono + 1) * sizeof(Ponto));
        if (pontos_poligono == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os pontos do polígono.\n");
            exit(EXIT_FAILURE);
        }
        pontos_poligono[num_pontos_poligono] = novo_ponto;  // Adiciona novo ponto
        num_pontos_poligono++;

        printf("Ponto adicionado ao polígono: (%f, %f)\n", novo_ponto.x, novo_ponto.y);
    } else {
        if (num_pontos_poligono > 2) {
            for (int i = 0; i < num_pontos_poligono; i++) {
                remover_ultimo_ponto(objetos);
            }
            // Finalizar polígono e adicionar à lista de polígonos
            objetos->poligonos = realloc(objetos->poligonos, (objetos->num_poligonos + 1) * sizeof(Poligono));
            if (objetos->poligonos == NULL) {
                fprintf(stderr, "Erro ao alocar memória para os polígonos.\n");
                exit(EXIT_FAILURE);
            }

            // Copia os pontos para o novo polígono
            objetos->poligonos[objetos->num_poligonos].pontos = pontos_poligono;
            objetos->poligonos[objetos->num_poligonos].num_pontos = num_pontos_poligono;

            // Incrementa o número de polígonos
            objetos->num_poligonos++;

            printf("Polígono finalizado com %d pontos.\n", num_pontos_poligono);

            // Resetar as variáveis estáticas
            pontos_poligono = NULL;
            num_pontos_poligono = 0;

            // Redesenhar a tela
            glutPostRedisplay();
        } else {
            printf("Polígono precisa de pelo menos 3 pontos.\n");
        }
    }
}

// Função para cancelar a operação atual
void cancelar_operacao(ObjetosGeometricos* objetos) {
    // Cancelar a operação de linha
    if (esperando_segundo_ponto == 1) {
        esperando_segundo_ponto = 0;  // Cancelar a espera pelo segundo ponto
        remover_ultimo_ponto(objetos);  // Remover o ponto inicial da linha
        printf("Operação de linha cancelada.\n");
    }

    // Cancelar a operação de polígono
    if (num_pontos_poligono > 0) {
        // Remover todos os pontos temporários do polígono
        for (int i = 0; i < num_pontos_poligono; i++) {
            remover_ultimo_ponto(objetos);
        }
        num_pontos_poligono = 0;
        free(pontos_poligono);
        pontos_poligono = NULL;
        printf("Operação de polígono cancelada.\n");

        // Redesenhar a tela
        glutPostRedisplay();
    }
}

// Função para desenhar todos os objetos geométricos
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

    // Desenhar os polígonos
    glColor3f(0.0f, 1.0f, 0.0f);  // Cor dos polígonos
    for (int i = 0; i < objetos->num_poligonos; i++) {
        glBegin(GL_POLYGON);  // Desenhar os polígonos preenchidos
        for (int j = 0; j < objetos->poligonos[i].num_pontos; j++) {
            glVertex2f(objetos->poligonos[i].pontos[j].x, objetos->poligonos[i].pontos[j].y);
        }
        glEnd();
    }
    glFlush();
}
