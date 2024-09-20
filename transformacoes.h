#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include <GL/glut.h>
#include <math.h>

void transladar(GLfloat tx, GLfloat ty);
void rotacionar(GLfloat angulo);
void escalar(GLfloat x, GLfloat y);
void reflexao_vertical();
void reflexao_horizontal();
void reflexao_diagonal();
void cisalhamento_y(GLfloat c);
void cisalhamento_x(GLfloat c);

#endif
