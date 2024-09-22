#include <stdio.h>
#include <GL/glut.h>
#include "objetos.h"
#include "transformacoes.h"

// Vari�veis globais
ObjetosGeometricos objetos;
int modo_desenho = 0;  // 0: pontos, 1: linhas, 2: pol�gonos

// Fun��o de exibi��o
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhar_objetos(&objetos);
    glutSwapBuffers();  // Para duplo buffer
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Ajusta o viewport para o tamanho da janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Manter o sistema de coordenadas fixo de 0 a 500 em ambas as dire��es
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fun��o de inicializa��o
void inicializar() {
    objetos = criar_objetos();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// Fun��o de teclado
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            if (modo_desenho != 0) {
                cancelar_operacao(&objetos);
                modo_desenho = 0;  // Modo de desenhar pontos
                printf("Modo: Pontos\n");
            }
            break;
        case 'w':
            if (modo_desenho != 1) {
                if(modo_desenho == 2) cancelar_operacao(&objetos);
                modo_desenho = 1;  // Modo de desenhar linhas
                printf("Modo: Linhas\n");
            }
            break;
        case 'e':
            if(modo_desenho != 2) {
                if(modo_desenho == 1) cancelar_operacao(&objetos);
                modo_desenho = 2;  // Modo de desenhar pol�gonos
                printf("Modo: Pol�gonos\n");
            }
            break;
        case 27:
            cancelar_operacao(&objetos);
        case 13:  // Tecla Enter
            if (modo_desenho == 2) {
                adicionar_poligono(&objetos, (Ponto){0, 0}, 1);  // Finaliza o pol�gono
                printf("Pol�gono finalizado!\n");
            }
            break;
    }
}

// Fun��o de mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float x_convertido = (float)x / width * 500.0f;
        float y_convertido = (float)(height - y) / height * 500.0f;

        if (modo_desenho == 0) {
            adicionar_ponto(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 1) {
            adicionar_linha(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 2) {
            adicionar_poligono(&objetos, (Ponto){x_convertido, y_convertido}, 0);  // Adiciona v�rtice ao pol�gono
            printf("V�rtice do pol�gono adicionado: (%f, %f)\n", x_convertido, y_convertido);
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Paint OpenGL");

    inicializar();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(teclado);  // Define a fun��o de teclado
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
