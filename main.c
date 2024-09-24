#include <stdio.h>
#include <GL/glut.h>
#include "objetos.h"
#include "selecoes.h"
#include "transformacoes.h"

// Variáveis globais
ObjetosGeometricos objetos;
int modo_desenho = 0;  // 0: pontos, 1: linhas, 2: polígonos
float mouse_x = 0.0f, mouse_y = 0.0f;  // Coordenadas atuais do mouse

// Função para desenhar uma caixa de tolerância de 5x5 ao redor do mouse
void desenhar_caixa_tolerancia(float x, float y) {
    float half_size = 5.0f / 2.0f;  // Metade do tamanho da caixa
    glColor3f(0.0f, 1.0f, 0.0f);  // Cor da caixa (verde)
    glBegin(GL_LINE_LOOP);
        glVertex2f(x - half_size, y - half_size);  // Canto inferior esquerdo
        glVertex2f(x + half_size, y - half_size);  // Canto inferior direito
        glVertex2f(x + half_size, y + half_size);  // Canto superior direito
        glVertex2f(x - half_size, y + half_size);  // Canto superior esquerdo
    glEnd();
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhar_objetos(&objetos);

    // Desenhar a caixa de tolerância no ponto atual do mouse
    desenhar_caixa_tolerancia(mouse_x, mouse_y);

    glutSwapBuffers();  // Para duplo buffer
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Ajusta o viewport para o tamanho da janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Manter o sistema de coordenadas fixo de 0 a 500 em ambas as direções
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Função de inicialização
void inicializar() {
    objetos = criar_objetos();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// Função de teclado
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            if (modo_desenho != 0) {
                cancelar_operacao(&objetos);
                modo_desenho = 0;  // Modo de desenhar pontos
                printf("Modo: Pontos\n");
            }
            break;
        case 'o':
            if (modo_desenho != 1) {
                if(modo_desenho == 2) cancelar_operacao(&objetos);
                modo_desenho = 1;  // Modo de desenhar linhas
                printf("Modo: Linhas\n");
            }
            break;
        case 'p':
            if(modo_desenho != 2) {
                if(modo_desenho == 1) cancelar_operacao(&objetos);
                modo_desenho = 2;  // Modo de desenhar polígonos
                printf("Modo: Polígonos\n");
            }
            break;
        case 27:
            cancelar_operacao(&objetos);
        case 13:  // Tecla Enter
            if (modo_desenho == 2) {
                adicionar_poligono(&objetos, (Ponto){0, 0}, 1);  // Finaliza o polígono
                printf("Polígono finalizado!\n");
            }
            break;
        case 'l':
            if (objetos.linha_selecionada != -1) {
                calcularCentroideLinha(&objetos.linhas[objetos.linha_selecionada]);
                transladar(-objetos.linhas[objetos.linha_selecionada].xcentroide, -objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
                rotacionar(10, &objetos.linhas[objetos.linha_selecionada], LINHA);
                transladar(objetos.linhas[objetos.linha_selecionada].xcentroide, objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                calcularCentroidePoligono(&objetos.poligonos[objetos.poligono_selecionado]);
                transladar(-objetos.poligonos[objetos.poligono_selecionado].xcentroide, -objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                rotacionar(10, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                transladar(objetos.poligonos[objetos.poligono_selecionado].xcentroide, objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'r':
            if (objetos.linha_selecionada != -1) {
                calcularCentroideLinha(&objetos.linhas[objetos.linha_selecionada]);
                transladar(-objetos.linhas[objetos.linha_selecionada].xcentroide, -objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
                rotacionar(-10, &objetos.linhas[objetos.linha_selecionada], LINHA);
                transladar(objetos.linhas[objetos.linha_selecionada].xcentroide, objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                calcularCentroidePoligono(&objetos.poligonos[objetos.poligono_selecionado]);
                transladar(-objetos.poligonos[objetos.poligono_selecionado].xcentroide, -objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                rotacionar(-10, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                transladar(objetos.poligonos[objetos.poligono_selecionado].xcentroide, objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case '+':
            if (objetos.ponto_selecionado != -1) {
                //escalar(2.0, 2.0, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                calcularCentroideLinha(&objetos.linhas[objetos.linha_selecionada]);
                transladar(-objetos.linhas[objetos.linha_selecionada].xcentroide, -objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
                escalar(2.0, 2.0, &objetos.linhas[objetos.linha_selecionada], LINHA);
                transladar(objetos.linhas[objetos.linha_selecionada].xcentroide, objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                calcularCentroidePoligono(&objetos.poligonos[objetos.poligono_selecionado]);
                transladar(-objetos.poligonos[objetos.poligono_selecionado].xcentroide, -objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                escalar(2.0, 2.0, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                transladar(objetos.poligonos[objetos.poligono_selecionado].xcentroide, objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case '-':
            if (objetos.ponto_selecionado != -1) {
                //escalar(0.5, 0.5, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                calcularCentroideLinha(&objetos.linhas[objetos.linha_selecionada]);
                transladar(-objetos.linhas[objetos.linha_selecionada].xcentroide, -objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
                escalar(0.5, 0.5, &objetos.linhas[objetos.linha_selecionada], LINHA);
                transladar(objetos.linhas[objetos.linha_selecionada].xcentroide, objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                calcularCentroidePoligono(&objetos.poligonos[objetos.poligono_selecionado]);
                transladar(-objetos.poligonos[objetos.poligono_selecionado].xcentroide, -objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                escalar(0.5, 0.5, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
                transladar(objetos.poligonos[objetos.poligono_selecionado].xcentroide, objetos.poligonos[objetos.poligono_selecionado].ycentroide, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'x':
            if (objetos.ponto_selecionado != -1) {
                cisalhamento_x(2.0, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                cisalhamento_x(2.0, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                cisalhamento_x(2.0, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'y':
            if (objetos.ponto_selecionado != -1) {
                cisalhamento_y(2.0, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                cisalhamento_y(2.0, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                cisalhamento_y(2.0, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'v':
            if (objetos.ponto_selecionado != -1) {
                reflexao_vertical(&objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                reflexao_vertical(&objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                reflexao_vertical(&objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'h':
            if (objetos.ponto_selecionado != -1) {
                reflexao_horizontal(&objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                reflexao_horizontal(&objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                reflexao_horizontal(&objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'z':
            if (objetos.ponto_selecionado != -1) {
                reflexao_diagonal(&objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                reflexao_diagonal(&objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                reflexao_diagonal(&objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
    }
    glutPostRedisplay();
}

void teclas_especiais(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (objetos.ponto_selecionado != -1) {
                transladar(0, 5, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                transladar(0, 5, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                transladar(0, 5, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case GLUT_KEY_DOWN:
            if (objetos.ponto_selecionado != -1) {
                transladar(0, -5, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                transladar(0, -5, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                transladar(0, -5, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case GLUT_KEY_LEFT:
            if (objetos.ponto_selecionado != -1) {
                transladar(-5, 0, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                transladar(-5, 0, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                transladar(-5, 0, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (objetos.ponto_selecionado != -1) {
                transladar(5, 0, &objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                transladar(5, 0, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                transladar(5, 0, &objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
    }
    glutPostRedisplay();
}



// Função de mouse
void mouse(int button, int state, int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float x_convertido = (float)x / width * 500.0f;
    float y_convertido = (float)(height - y) / height * 500.0f;

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        if (modo_desenho == 0) {
            adicionar_ponto(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 1) {
            adicionar_linha(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 2) {
            adicionar_poligono(&objetos, (Ponto){x_convertido, y_convertido}, 0);  // Adiciona vértice ao polígono
            printf("Vértice do polígono adicionado: (%f, %f)\n", x_convertido, y_convertido);
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        selecionar_ponto(&objetos, x_convertido, y_convertido);
        selecionar_linha(&objetos, x_convertido, y_convertido);
        selecionar_area(&objetos, x_convertido, y_convertido);
        printf("\n\n Seleciondados: %d, %d, %d \n\n", objetos.ponto_selecionado, objetos.linha_selecionada, objetos.poligono_selecionado);
    }
    glutPostRedisplay();
}

// Função chamada sempre que o mouse se move, usada para atualizar a posição do mouse
void passive_motion(int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // Converte as coordenadas da tela para o sistema de coordenadas da janela (0 a 500)
    mouse_x = (float)x / width * 500.0f;
    mouse_y = (float)(height - y) / height * 500.0f;

    glutPostRedisplay();  // Solicita a atualização da tela
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Paint OpenGL");

    inicializar();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(teclado);  // Define a função de teclado
    glutSpecialFunc(teclas_especiais);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);  // Atualiza a posição do mouse enquanto ele se move

    glutMainLoop();

    return 0;
}
