#include <stdio.h>
#include <GL/glut.h>
#include "selecoes.h"
#include "objetos.h"

int pickPonto(float px, float py, float mx, float my, int t){
    if(px <= mx + t && px >= mx - t){
        if(py <= my + t && py >= my - t){
            return 1;
        }
    }
    return 0;
}

void andar(float *x0, float *y0, float x1, float y1, float fronteira, int mover_em_x, int mover_em_y) {
    if (mover_em_x) {
        *y0 = *y0 + (fronteira - *x0) * (y1 - *y0) / (x1 - *x0);
        *x0 = fronteira;
    } else if (mover_em_y) {
        *x0 = *x0 + (fronteira - *y0) * (x1 - *x0) / (y1 - *y0);
        *y0 = fronteira;
    }
}

void selecionar_ponto(ObjetosGeometricos* objetos, float x, float y) {
    int tolerancia = 5;
    int ponto_selecionado = 0;

    for (int i = 0; i < objetos->num_pontos; i++) {
        if (pickPonto(objetos->pontos[i].x, objetos->pontos[i].y, x, y, tolerancia)) {
            objetos->ponto_selecionado = i;
            objetos->linha_selecionada = -1;
            objetos->poligono_selecionado = -1;
            ponto_selecionado = 1;
            break;
        }
    }

    if (!ponto_selecionado) {
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

        float x0 = objetos->linhas[i].inicio.x;
        float y0 = objetos->linhas[i].inicio.y;
        float x1 = objetos->linhas[i].fim.x;
        float y1 = objetos->linhas[i].fim.y;

        if (x0 < x - tolerancia) ie = 1;
        if (x0 > x + tolerancia) id = 1;
        if (y0 < y - tolerancia) iab = 1;
        if (y0 > y + tolerancia) iac = 1;

        if (x1 < x - tolerancia) fe = 1;
        if (x1 > x + tolerancia) fd = 1;
        if (y1 < y - tolerancia) fab = 1;
        if (y1 > y + tolerancia) fac = 1;

        if ((ie == 0 && id == 0 && iab == 0 && iac == 0) || (fe == 0 && fd == 0 && fab == 0 && fac == 0)) {
            objetos->linha_selecionada = i;
            objetos->ponto_selecionado = -1;
            objetos->poligono_selecionado = -1;
            linha_selecionada = 1;
            break;
        }

        if ((ie == 1 && fe == 1) || (id == 1 && fd == 1) || (iac == 1 && fac == 1) || (iab == 1 && fab == 1))
            continue;

        while (1) {

            if (ie == 1) {
                andar(&x0, &y0, x1, y1, x - tolerancia, 1, 0);
            } else if (id == 1) {
                andar(&x0, &y0, x1, y1, x + tolerancia, 1, 0);
            } else if (iab == 1) {
                andar(&x0, &y0, x1, y1, y - tolerancia, 0, 1);
            } else if (iac == 1) {
                andar(&x0, &y0, x1, y1, y + tolerancia, 0, 1);
            }


            ie = id = iab = iac = 0;
            if (x0 < x - tolerancia) ie = 1;
            if (x0 > x + tolerancia) id = 1;
            if (y0 < y - tolerancia) iab = 1;
            if (y0 > y + tolerancia) iac = 1;

            if (ie == 0 && id == 0 && iab == 0 && iac == 0) {
                objetos->linha_selecionada = i;
                objetos->ponto_selecionado = -1;
                objetos->poligono_selecionado = -1;
                linha_selecionada = 1;
                break;
            }
            if ((ie == 1 && fe == 1) || (id == 1 && fd == 1) || (iac == 1 && fac == 1) || (iab == 1 && fab == 1))
                break;
        }
    }

    if (!linha_selecionada) {
        objetos->linha_selecionada = -1;
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

            if ((p1->y > y && p2->y > y) || (p1->y < y && p2->y < y) || (p1->x < x && p2->x < x) || (p1->x < x && p2->x < x)) {
                continue;
            }

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

        if (tiro % 2 != 0) {
            objetos->poligono_selecionado = i;
            objetos->ponto_selecionado = -1;
            objetos->linha_selecionada = -1;
            return;
        }
    }

    objetos->poligono_selecionado = -1;
}
