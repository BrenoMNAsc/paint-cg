#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include <GL/glut.h>
#include <math.h>

void multMatriz(GLfloat matriz[3][3], Ponto* pontos, int num_pontos);
void transladar(GLfloat tx, GLfloat ty);
void rotacionar(GLfloat angulo);
void escalar(GLfloat sx, GLfloat sy);
void cisalhamento_x(GLfloat c);
void cisalhamento_y(GLfloat c);
void reflexao_vertical();
void reflexao_horizontal();
void reflexao_diagonal();

#endif
