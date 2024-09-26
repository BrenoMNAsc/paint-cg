#include <stdio.h>
#include "objetos.h"
#include <stdlib.h>
#include <GL/glut.h>

Ponto ponto_inicial_linha;
int esperando_segundo_ponto = 0;
Ponto* pontos_poligono = NULL;
int num_pontos_poligono = 0;

ObjetosGeometricos criar_objetos() {
    ObjetosGeometricos objs;
    objs.pontos = NULL;
    objs.linhas = NULL;
    objs.poligonos = NULL;
    objs.num_pontos = objs.num_linhas = objs.num_poligonos = 0;
    objs.linha_selecionada, objs.ponto_selecionado, objs.poligono_selecionado = -1;
    return objs;
}

void adicionar_linha(ObjetosGeometricos* objetos, float x, float y) {
    if (esperando_segundo_ponto == 0) {
        ponto_inicial_linha.x = x;
        ponto_inicial_linha.y = y;
        esperando_segundo_ponto = 1;
        printf("Primeiro ponto da linha: (%f, %f)\n", x, y);
        adicionar_ponto(objetos, x, y);
    } else {
        remover_ultimo_ponto(objetos);
        objetos->linhas = realloc(objetos->linhas, (objetos->num_linhas + 1) * sizeof(Linha));
        if (objetos->linhas == NULL) {
            fprintf(stderr, "Erro ao alocar memória para as linhas.\n");
            exit(EXIT_FAILURE);
        }
        objetos->linhas[objetos->num_linhas].inicio = ponto_inicial_linha;
        objetos->linhas[objetos->num_linhas].fim.x = x;
        objetos->linhas[objetos->num_linhas].fim.y = y;

        objetos->linhas[objetos->num_linhas].xcentroide = (ponto_inicial_linha.x + x) / 2.0;
        objetos->linhas[objetos->num_linhas].ycentroide = (ponto_inicial_linha.y + y) / 2.0;

        objetos->num_linhas++;
        esperando_segundo_ponto = 0;

        printf("Linha adicionada: (%f, %f) -> (%f, %f) | Centroide: (%f, %f)\n",
               ponto_inicial_linha.x, ponto_inicial_linha.y, x, y,
               objetos->linhas[objetos->num_linhas - 1].xcentroide, objetos->linhas[objetos->num_linhas - 1].ycentroide);

        glutPostRedisplay();
    }
}

void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y) {
    objetos->pontos = realloc(objetos->pontos, (objetos->num_pontos + 1) * sizeof(Ponto));
    objetos->pontos[objetos->num_pontos].x = x;
    objetos->pontos[objetos->num_pontos].y = y;
    objetos->num_pontos++;

    printf("Ponto: (%f, %f)\n", x, y);

    glutPostRedisplay();
}

void remover_ultimo_ponto(ObjetosGeometricos* objetos) {
    if (objetos->num_pontos > 0) {
        objetos->num_pontos--;
        objetos->pontos = realloc(objetos->pontos, objetos->num_pontos * sizeof(Ponto));
        if (objetos->num_pontos > 0 && objetos->pontos == NULL) {
            fprintf(stderr, "Erro ao realocar memória após remover ponto.\n");
            exit(EXIT_FAILURE);
        }

        printf("Ponto removido. Agora há %d pontos.\n", objetos->num_pontos);

        glutPostRedisplay();
    } else {
        printf("Nenhum ponto para remover.\n");
    }
}

void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar) {
    if (!finalizar) {
        adicionar_ponto(objetos, novo_ponto.x, novo_ponto.y);
        pontos_poligono = realloc(pontos_poligono, (num_pontos_poligono + 1) * sizeof(Ponto));
        pontos_poligono[num_pontos_poligono] = novo_ponto;
        num_pontos_poligono++;

    } else {
        if (num_pontos_poligono > 2) {
            for (int i = 0; i < num_pontos_poligono; i++) {
                remover_ultimo_ponto(objetos);
            }
            objetos->poligonos = realloc(objetos->poligonos, (objetos->num_poligonos + 1) * sizeof(Poligono));
            if (objetos->poligonos == NULL) {
                fprintf(stderr, "Erro ao alocar memória para os polígonos.\n");
                exit(EXIT_FAILURE);
            }
            objetos->poligonos[objetos->num_poligonos].pontos = pontos_poligono;
            objetos->poligonos[objetos->num_poligonos].num_pontos = num_pontos_poligono;

            float soma_x = 0, soma_y = 0;
            for (int i = 0; i < num_pontos_poligono; i++) {
                soma_x += pontos_poligono[i].x;
                soma_y += pontos_poligono[i].y;
            }
            objetos->poligonos[objetos->num_poligonos].xcentroide = soma_x / num_pontos_poligono;
            objetos->poligonos[objetos->num_poligonos].ycentroide = soma_y / num_pontos_poligono;

            objetos->num_poligonos++;

            pontos_poligono = NULL;
            num_pontos_poligono = 0;

            glutPostRedisplay();
        } else {
            printf("Polígono precisa de pelo menos 3 pontos.\n");
        }
    }
}

void deletar_objeto_selecionado(ObjetosGeometricos* objetos) {
    if (objetos->ponto_selecionado != -1) {
        int idx = objetos->ponto_selecionado;
        for (int i = idx; i < objetos->num_pontos - 1; i++) {
            objetos->pontos[i] = objetos->pontos[i + 1];
        }
        objetos->num_pontos--;
        objetos->pontos = realloc(objetos->pontos, objetos->num_pontos * sizeof(Ponto));
        objetos->ponto_selecionado = -1;
        printf("Ponto deletado. Agora há %d pontos.\n", objetos->num_pontos);
    }

    else if (objetos->linha_selecionada != -1) {
        int idx = objetos->linha_selecionada;
        for (int i = idx; i < objetos->num_linhas - 1; i++) {
            objetos->linhas[i] = objetos->linhas[i + 1];
        }
        objetos->num_linhas--;
        objetos->linhas = realloc(objetos->linhas, objetos->num_linhas * sizeof(Linha));
        objetos->linha_selecionada = -1;
        printf("Linha deletada. Agora há %d linhas.\n", objetos->num_linhas);
    }

    else if (objetos->poligono_selecionado != -1) {
        int idx = objetos->poligono_selecionado;

        free(objetos->poligonos[idx].pontos);

        for (int i = idx; i < objetos->num_poligonos - 1; i++) {
            objetos->poligonos[i] = objetos->poligonos[i + 1];
        }
        objetos->num_poligonos--;
        objetos->poligonos = realloc(objetos->poligonos, objetos->num_poligonos * sizeof(Poligono));
        objetos->poligono_selecionado = -1;
    }

    glutPostRedisplay();
}


void cancelar_operacao(ObjetosGeometricos* objetos) {
    if (esperando_segundo_ponto == 1) {
        esperando_segundo_ponto = 0;
        remover_ultimo_ponto(objetos);
        printf("Operação de linha cancelada.\n");
    }

    if (num_pontos_poligono > 0) {
        for (int i = 0; i < num_pontos_poligono; i++) {
            remover_ultimo_ponto(objetos);
        }
        num_pontos_poligono = 0;
        free(pontos_poligono);
        pontos_poligono = NULL;
        printf("Operação de polígono cancelada.\n");

        glutPostRedisplay();
    }
}



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
    for (int i = 0; i < objetos->num_poligonos; i++) {
        int num_pontos = objetos->poligonos[i].num_pontos;
        GLdouble** poligon_vertex = (GLdouble**)malloc(num_pontos * sizeof(GLdouble*));

        for (int j = 0; j < num_pontos; j++) {
            poligon_vertex[j] = (GLdouble*)malloc(3 * sizeof(GLdouble));
            poligon_vertex[j][0] = (GLdouble) objetos->poligonos[i].pontos[j].x;
            poligon_vertex[j][1] = (GLdouble) objetos->poligonos[i].pontos[j].y;
            poligon_vertex[j][2] = 0.0;
        }

        GLUtesselator* tess = gluNewTess();

        gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())glBegin);
        gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())glVertex3dv);
        gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())glEnd);

        glColor3f(0.0f, 1.0f, 0.0f);
        gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
        for (int k = 0; k < num_pontos; k++) {
            gluTessVertex(tess, poligon_vertex[k], poligon_vertex[k]);
        }
        gluTessEndContour(tess);
        gluTessEndPolygon(tess);

        gluDeleteTess(tess);

        for (int j = 0; j < num_pontos; j++) {
            free(poligon_vertex[j]);
        }
        free(poligon_vertex);
    }

    glFlush();
}
