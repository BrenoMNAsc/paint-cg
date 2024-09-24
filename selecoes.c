#include <stdio.h>
#include <GL/glut.h>
#include "selecoes.h"
#include "objetos.h"

// Function from the provided image to pick a point
int pickPonto(float px, float py, float mx, float my, int t){
    if(mx <= px + t && mx >= px - t){
        if(my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
}

void andar(float *x0, float *y0, float x1, float y1, float fronteira, int mover_em_x, int mover_em_y) {
    if (mover_em_x) {
        *y0 = *y0 + (fronteira - *x0) * (y1 - *y0) / (x1 - *x0);  // Recalcula y
        *x0 = fronteira;  // Move x para a fronteira
    } else if (mover_em_y) {
        *x0 = *x0 + (fronteira - *y0) * (x1 - *x0) / (y1 - *y0);  // Recalcula x
        *y0 = fronteira;  // Move y para a fronteira
    }
}

// Function to handle mouse clicks and check if a point is selected
void selecionar_ponto(ObjetosGeometricos* objetos, float x, float y) {
    int tolerancia = 5;  // Tolerance for how close the click must be to the point
    int ponto_selecionado = 0;

    // Check all individual points
    for (int i = 0; i < objetos->num_pontos; i++) {
        if (pickPonto(objetos->pontos[i].x, objetos->pontos[i].y, x, y, tolerancia)) {
            printf("Ponto selecionado: (%f, %f)\n", objetos->pontos[i].x, objetos->pontos[i].y);
            objetos->ponto_selecionado = i;
            objetos->linha_selecionada = -1;
            objetos->poligono_selecionado = -1;
            ponto_selecionado = 1;
            break;
        }
    }

    if (!ponto_selecionado) {
        printf("Nenhum ponto selecionado.\n");
        objetos->ponto_selecionado = -1;
    }

}

void selecionar_linha(ObjetosGeometricos* objetos, float x, float y) {
    int tolerancia = 5;
    int linha_selecionada = 0;

    for (int i = 0; i < objetos->num_linhas; i++) {
        int ie = 0;
        int id = 0;
        int iab = 0;
        int iac = 0;
        int fe = 0;
        int fd = 0;
        int fab = 0;
        int fac = 0;

        // Extrair as coordenadas do in?cio (x0, y0) e do fim (x1, y1) da linha
        float x0 = objetos->linhas[i].inicio.x;
        float y0 = objetos->linhas[i].inicio.y;
        float x1 = objetos->linhas[i].fim.x;
        float y1 = objetos->linhas[i].fim.y;

        // Detectar o recorte para o v?rtice inicial da linha
        if (x0 < x - tolerancia) ie = 1;  // ? esquerda da regi?o
        if (x0 > x + tolerancia) id = 1;  // ? direita da regi?o
        if (y0 < y - tolerancia) iab = 1; // Abaixo da regi?o
        if (y0 > y + tolerancia) iac = 1; // Acima da regi?o

        // Detectar o recorte para o v?rtice final da linha
        if (x1 < x - tolerancia) fe = 1;  // ? esquerda da regi?o
        if (x1 > x + tolerancia) fd = 1;  // ? direita da regi?o
        if (y1 < y - tolerancia) fab = 1; // Abaixo da regi?o
        if (y1 > y + tolerancia) fac = 1; // Acima da regi?o

        // Verificar se a linha est? trivialmente dentro ou trivialmente fora
        if ((ie == 0 && id == 0 && iab == 0 && iac == 0) || (fe == 0 && fd == 0 && fab == 0 && fac == 0)) {
            printf("Linha selecionada\n");
            objetos->linha_selecionada = i;
            objetos->ponto_selecionado = -1;
            objetos->poligono_selecionado = -1;
            linha_selecionada = 1;
            break;
        }
        if ((ie == 1 && fe == 1) || (id == 1 && fd == 1) || (iac == 1 && fac == 1) || (iab == 1 && fab == 1))
            break;
        // N?o trivialmente dentro, aplicar l?gica de recorte
        while (1) {
            // Recorte ? esquerda para o ponto inicial
            if (ie == 1) {
                andar(&x0, &y0, x1, y1, x - tolerancia, 1, 0);  // Mover para a fronteira esquerda
                printf("Mover v?rtice para fronteira esquerda, novo in?cio: (%f, %f)\n", x0, y0);
            }
            // Recorte ? direita para o ponto inicial
            else if (id == 1) {
                andar(&x0, &y0, x1, y1, x + tolerancia, 1, 0);  // Mover para a fronteira direita
                printf("Mover v?rtice para fronteira direita, novo in?cio: (%f, %f)\n", x0, y0);
            }
            // Recorte abaixo para o ponto inicial
            else if (iab == 1) {
                andar(&x0, &y0, x1, y1, y - tolerancia, 0, 1);  // Mover para a fronteira inferior
                printf("Mover v?rtice para fronteira inferior, novo in?cio: (%f, %f)\n", x0, y0);
            }
            // Recorte acima para o ponto inicial
            else if (iac == 1) {
                andar(&x0, &y0, x1, y1, y + tolerancia, 0, 1);  // Mover para a fronteira superior
                printf("Mover v?rtice para fronteira superior, novo in?cio: (%f, %f)\n", x0, y0);
            }

            // Recode o v?rtice inicial ap?s mov?-lo
            ie = id = iab = iac = 0;
            if (x0 < x - tolerancia) ie = 1;
            if (x0 > x + tolerancia) id = 1;
            if (y0 < y - tolerancia) iab = 1;
            if (y0 > y + tolerancia) iac = 1;

            // Se o v?rtice inicial agora estiver trivialmente dentro, saia
            if (ie == 0 && id == 0 && iab == 0 && iac == 0) {
                printf("Vertice dentro apos movimento\n");
                objetos->linha_selecionada = i;
                objetos->ponto_selecionado = -1;
                objetos->poligono_selecionado = -1;
                linha_selecionada = 1;
                break;
            }

            // Pare ap?s o recorte, pode ser estendido para mais casos complexos
            break;
        }
    }

    if (!linha_selecionada) {
        printf("Nenhuma linha selecionada.\n");
        objetos->linha_selecionada = -1;  // Nenhuma linha selecionada
    }
}


void selecionar_area(ObjetosGeometricos* objetos, float x, float y) {
    int tiro = 0;
    int msmponto1 = 0;
    int msmponto2 = 0;
    for (int i = 0; i < objetos->num_poligonos; i++) {
        for (int j = 0; j < objetos->poligonos[i].num_pontos; j++) {
            Ponto* p1 = NULL;
            Ponto* p2 = NULL;
            if (j == objetos->poligonos[i].num_pontos - 1) {
                p1 = &objetos->poligonos[i].pontos[j];
                p2 = &objetos->poligonos[i].pontos[0];
            } else {
                p1 = &objetos->poligonos[i].pontos[j];
                p2 = &objetos->poligonos[i].pontos[j + 1];
            }
            if (p1->y == p2->y) {
                continue;
            }

            // Verifica se o ponto esta fora da area do poligono
            if ((p1->y > y && p2->y > y) || (p1->y < y && p2->y < y) || (p1->x < x && p2->x < x) || (p1->x < x && p2->x < x)) {
                continue;
            }
            // Verifica se o ponto esta dentro do poligono e seleciona
            if ((p1->x > x && p2->x > x) && ((p1->y > y && p2->y < y) || (p1->y < y && p2->y > y))) {
                tiro++;
                continue;
            }

            float xi = p1->x + (y - p1->y)*(p2->x - p1->x)/(p2->y - p1->y);
            if (xi > x) {
                if (p1->y == y) {
                    msmponto1++;
                } else if (p2->y == y) {
                    msmponto2++;
                }
                if (msmponto1 == 2 || msmponto2 == 2) {
                    msmponto1 = 0;
                    msmponto2 = 0;
                    continue;
                }
                tiro++;
            }
        }
        // Se o numero de interseccoes for impar, o ponto esta dentro do poligono
        if (tiro % 2 != 0) {
            objetos->poligono_selecionado = i;
            objetos->ponto_selecionado = -1;
            objetos->linha_selecionada = -1;
            printf("Poligono %d selecionado\n", i);
            return;
        }
    }
    // Se nao selecionar nenhum poligono
    printf("Nenhum poligono selecionado\n");
    objetos->poligono_selecionado = -1;
}
