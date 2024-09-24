#include <stdio.h>
#include "objetos.h"
#include <stdlib.h>
#include <GL/glut.h>

// Vari�veis globais
Ponto ponto_inicial_linha;
int esperando_segundo_ponto = 0;  // Flag para saber se estamos aguardando o segundo ponto da linha

// Vari�veis est�ticas para o pol�gono
Ponto* pontos_poligono = NULL;  // Armazena os pontos tempor�rios do pol�gono
int num_pontos_poligono = 0;    // Conta o n�mero de pontos tempor�rios do pol�gono

ObjetosGeometricos criar_objetos() {
    ObjetosGeometricos objs;
    objs.pontos = NULL;
    objs.linhas = NULL;
    objs.poligonos = NULL;
    objs.num_pontos = objs.num_linhas = objs.num_poligonos = 0;
    objs.linha_selecionada, objs.ponto_selecionado, objs.poligono_selecionado = -1;
    return objs;
}

// Fun��o para adicionar linha
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
            fprintf(stderr, "Erro ao alocar mem�ria para as linhas.\n");
            exit(EXIT_FAILURE);
        }
        objetos->linhas[objetos->num_linhas].inicio = ponto_inicial_linha;
        objetos->linhas[objetos->num_linhas].fim.x = x;
        objetos->linhas[objetos->num_linhas].fim.y = y;

        objetos->linhas[objetos->num_linhas].xcentroide = (ponto_inicial_linha.x + x) / 2.0;
        objetos->linhas[objetos->num_linhas].ycentroide = (ponto_inicial_linha.y + y) / 2.0;

        // Incrementa o n�mero de linhas
        objetos->num_linhas++;
        esperando_segundo_ponto = 0;  // Reset para a pr�xima linha

        printf("Linha adicionada: (%f, %f) -> (%f, %f) | Centroide: (%f, %f)\n",
               ponto_inicial_linha.x, ponto_inicial_linha.y, x, y,
               objetos->linhas[objetos->num_linhas - 1].xcentroide, objetos->linhas[objetos->num_linhas - 1].ycentroide);

        // Redesenhar a tela
        glutPostRedisplay();
    }
}

void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y) {
    objetos->pontos = realloc(objetos->pontos, (objetos->num_pontos + 1) * sizeof(Ponto));
    if (objetos->pontos == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para os pontos.\n");
        exit(EXIT_FAILURE);
    }
    objetos->pontos[objetos->num_pontos].x = x;
    objetos->pontos[objetos->num_pontos].y = y;
    objetos->num_pontos++;

    printf("Ponto: (%f, %f)\n", x, y);

    glutPostRedisplay();
}

void remover_ultimo_ponto(ObjetosGeometricos* objetos) {
    if (objetos->num_pontos > 0) {
        // Decrementa o n�mero de pontos
        objetos->num_pontos--;

        // Realoca a mem�ria para remover o �ltimo ponto
        objetos->pontos = realloc(objetos->pontos, objetos->num_pontos * sizeof(Ponto));

        // Verifica se a realoca��o ocorreu corretamente
        if (objetos->num_pontos > 0 && objetos->pontos == NULL) {
            fprintf(stderr, "Erro ao realocar mem�ria ap�s remover ponto.\n");
            exit(EXIT_FAILURE);
        }

        printf("Ponto removido. Agora h� %d pontos.\n", objetos->num_pontos);

        // Redesenhar a tela
        glutPostRedisplay();
    } else {
        printf("Nenhum ponto para remover.\n");
    }
}

void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar) {
    if (!finalizar) {
        // Adicionar ponto ao pol�gono
        adicionar_ponto(objetos, novo_ponto.x, novo_ponto.y);
        pontos_poligono = realloc(pontos_poligono, (num_pontos_poligono + 1) * sizeof(Ponto));
        if (pontos_poligono == NULL) {
            fprintf(stderr, "Erro ao alocar mem�ria para os pontos do pol�gono.\n");
            exit(EXIT_FAILURE);
        }
        pontos_poligono[num_pontos_poligono] = novo_ponto;  // Adiciona novo ponto
        num_pontos_poligono++;

        printf("Ponto adicionado ao pol�gono: (%f, %f)\n", novo_ponto.x, novo_ponto.y);
    } else {
        if (num_pontos_poligono > 2) {
            for (int i = 0; i < num_pontos_poligono; i++) {
                remover_ultimo_ponto(objetos);
            }
            // Finalizar pol�gono e adicionar � lista de pol�gonos
            objetos->poligonos = realloc(objetos->poligonos, (objetos->num_poligonos + 1) * sizeof(Poligono));
            if (objetos->poligonos == NULL) {
                fprintf(stderr, "Erro ao alocar mem�ria para os pol�gonos.\n");
                exit(EXIT_FAILURE);
            }

            // Copia os pontos para o novo pol�gono
            objetos->poligonos[objetos->num_poligonos].pontos = pontos_poligono;
            objetos->poligonos[objetos->num_poligonos].num_pontos = num_pontos_poligono;

            // C�lculo do centr�ide do pol�gono
            float soma_x = 0, soma_y = 0;
            for (int i = 0; i < num_pontos_poligono; i++) {
                soma_x += pontos_poligono[i].x;
                soma_y += pontos_poligono[i].y;
            }
            objetos->poligonos[objetos->num_poligonos].xcentroide = soma_x / num_pontos_poligono;
            objetos->poligonos[objetos->num_poligonos].ycentroide = soma_y / num_pontos_poligono;

            // Incrementa o n�mero de pol�gonos
            objetos->num_poligonos++;

            printf("Pol�gono finalizado com %d pontos. Centroide: (%f, %f)\n", num_pontos_poligono,
                   objetos->poligonos[objetos->num_poligonos - 1].xcentroide,
                   objetos->poligonos[objetos->num_poligonos - 1].ycentroide);

            // Resetar as vari�veis est�ticas
            pontos_poligono = NULL;
            num_pontos_poligono = 0;

            // Redesenhar a tela
            glutPostRedisplay();
        } else {
            printf("Pol�gono precisa de pelo menos 3 pontos.\n");
        }
    }
}

void deletar_objeto_selecionado(ObjetosGeometricos* objetos) {
    // Verifica se h� um ponto selecionado e o remove
    if (objetos->ponto_selecionado != -1) {
        int idx = objetos->ponto_selecionado;
        for (int i = idx; i < objetos->num_pontos - 1; i++) {
            objetos->pontos[i] = objetos->pontos[i + 1];  // Desloca os pontos para preencher o espa�o vazio
        }
        objetos->num_pontos--;  // Decrementa o n�mero de pontos
        objetos->pontos = realloc(objetos->pontos, objetos->num_pontos * sizeof(Ponto));
        objetos->ponto_selecionado = -1;  // Reseta a sele��o
        printf("Ponto deletado. Agora h� %d pontos.\n", objetos->num_pontos);
    }

    // Verifica se h� uma linha selecionada e a remove
    else if (objetos->linha_selecionada != -1) {
        int idx = objetos->linha_selecionada;
        for (int i = idx; i < objetos->num_linhas - 1; i++) {
            objetos->linhas[i] = objetos->linhas[i + 1];  // Desloca as linhas para preencher o espa�o vazio
        }
        objetos->num_linhas--;  // Decrementa o n�mero de linhas
        objetos->linhas = realloc(objetos->linhas, objetos->num_linhas * sizeof(Linha));
        objetos->linha_selecionada = -1;  // Reseta a sele��o
        printf("Linha deletada. Agora h� %d linhas.\n", objetos->num_linhas);
    }

    // Verifica se h� um pol�gono selecionado e o remove
    else if (objetos->poligono_selecionado != -1) {
        int idx = objetos->poligono_selecionado;

        // Libera a mem�ria dos pontos do pol�gono
        free(objetos->poligonos[idx].pontos);

        for (int i = idx; i < objetos->num_poligonos - 1; i++) {
            objetos->poligonos[i] = objetos->poligonos[i + 1];  // Desloca os pol�gonos para preencher o espa�o vazio
        }
        objetos->num_poligonos--;  // Decrementa o n�mero de pol�gonos
        objetos->poligonos = realloc(objetos->poligonos, objetos->num_poligonos * sizeof(Poligono));
        objetos->poligono_selecionado = -1;  // Reseta a sele��o
        printf("Pol�gono deletado. Agora h� %d pol�gonos.\n", objetos->num_poligonos);
    }

    // Redesenhar a tela ap�s a exclus�o
    glutPostRedisplay();
}


// Fun��o para cancelar a opera��o atual
void cancelar_operacao(ObjetosGeometricos* objetos) {
    // Cancelar a opera��o de linha
    if (esperando_segundo_ponto == 1) {
        esperando_segundo_ponto = 0;  // Cancelar a espera pelo segundo ponto
        remover_ultimo_ponto(objetos);  // Remover o ponto inicial da linha
        printf("Opera��o de linha cancelada.\n");
    }

    // Cancelar a opera��o de pol�gono
    if (num_pontos_poligono > 0) {
        // Remover todos os pontos tempor�rios do pol�gono
        for (int i = 0; i < num_pontos_poligono; i++) {
            remover_ultimo_ponto(objetos);
        }
        num_pontos_poligono = 0;
        free(pontos_poligono);
        pontos_poligono = NULL;
        printf("Opera��o de pol�gono cancelada.\n");

        // Redesenhar a tela
        glutPostRedisplay();
    }
}



// Fun��o modificada para desenhar objetos
void desenhar_objetos(ObjetosGeometricos* objetos) {
    // Desenha pontos
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < objetos->num_pontos; i++) {
        glVertex2f(objetos->pontos[i].x, objetos->pontos[i].y);
    }
    glEnd();

    // Desenha linhas
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < objetos->num_linhas; i++) {
        glVertex2f(objetos->linhas[i].inicio.x, objetos->linhas[i].inicio.y);
        glVertex2f(objetos->linhas[i].fim.x, objetos->linhas[i].fim.y);
    }
    glEnd();

    // Desenha pol�gonos com tessela��o
    for (int i = 0; i < objetos->num_poligonos; i++) {
        int num_pontos = objetos->poligonos[i].num_pontos;
        GLdouble** poligon_vertex = (GLdouble**)malloc(num_pontos * sizeof(GLdouble*));

        // Carrega os v�rtices do pol�gono
        for (int j = 0; j < num_pontos; j++) {
            poligon_vertex[j] = (GLdouble*)malloc(3 * sizeof(GLdouble));
            poligon_vertex[j][0] = (GLdouble) objetos->poligonos[i].pontos[j].x;
            poligon_vertex[j][1] = (GLdouble) objetos->poligonos[i].pontos[j].y;
            poligon_vertex[j][2] = 0.0;  // Como estamos em 2D, o z � 0
        }

        // Desenha o pol�gono com tessela��o
        GLUtesselator* tess = gluNewTess();  // Criar o tesselador

        // Definir callbacks para tessela��o
        gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())glBegin);
        gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())glVertex3dv);
        gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())glEnd);

        // Definir a cor verde para o pol�gono antes de iniciar a tessela��o
        glColor3f(0.0f, 1.0f, 0.0f);  // Cor dos pol�gonos
        gluTessBeginPolygon(tess, 0);  // Come�ar o pol�gono
        gluTessBeginContour(tess);  // Come�ar o contorno do pol�gono
        for (int k = 0; k < num_pontos; k++) {
            gluTessVertex(tess, poligon_vertex[k], poligon_vertex[k]);
        }
        gluTessEndContour(tess);  // Finalizar o contorno
        gluTessEndPolygon(tess);  // Finalizar o pol�gono

        gluDeleteTess(tess);  // Deletar o tesselador ap�s o uso

        // Liberar a mem�ria alocada para cada v�rtice
        for (int j = 0; j < num_pontos; j++) {
            free(poligon_vertex[j]);
        }
        free(poligon_vertex);  // Libera a mem�ria alocada para os v�rtices
    }

    glFlush();
}
