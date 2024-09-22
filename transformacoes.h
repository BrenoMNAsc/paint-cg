#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include <GL/glut.h>
#include <math.h>

typedef enum {
    PONTO,
    LINHA,
    POLIGONO
} TipoObjeto;

void multMatriz(GLfloat matriz[3][3], void* objeto, TipoObjeto tipo);
void transladar(GLfloat tx, GLfloat ty, void* objeto, TipoObjeto tipo);
void rotacionar(GLfloat angulo, void* objeto, TipoObjeto tipo);
void escalar(GLfloat sx, GLfloat sy, void* objeto, TipoObjeto tipo);
void cisalhamento_x(GLfloat c, void* objeto, TipoObjeto tipo);
void cisalhamento_y(GLfloat c, void* objeto, TipoObjeto tipo);
void reflexao_vertical(void* objeto, TipoObjeto tipo);
void reflexao_horizontal(void* objeto, TipoObjeto tipo);
void reflexao_diagonal(void* objeto, TipoObjeto tipo);

#endif
