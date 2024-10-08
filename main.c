#include <stdio.h>
#include <GL/glut.h>
#include "objetos.h"
#include "selecoes.h"
#include "transformacoes.h"
#include "arquivos.h"

ObjetosGeometricos objetos;
int modo_desenho = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhar_objetos(&objetos);


    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect_ratio = (float)w / (float)h;
    if (aspect_ratio >= 1.0) {
        gluOrtho2D(-250.0 * aspect_ratio, 250.0 * aspect_ratio, -250.0, 250.0);
    } else {
        gluOrtho2D(-250.0, 250.0, -250.0 / aspect_ratio, 250.0 / aspect_ratio);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            if (modo_desenho != 0) {
                cancelar_operacao(&objetos);
                modo_desenho = 0;
                printf("Modo: Pontos\n");
            }
            break;
        case 'o':
            if (modo_desenho != 1) {
                if(modo_desenho == 2) cancelar_operacao(&objetos);
                modo_desenho = 1;
                printf("Modo: Linhas\n");
            }
            break;
        case 'p':
            if(modo_desenho != 2) {
                if(modo_desenho == 1) cancelar_operacao(&objetos);
                modo_desenho = 2;
                printf("Modo: Pol�gonos\n");
            }
            break;
        case 27:
            cancelar_operacao(&objetos);
        case 13:
            if (modo_desenho == 2) {
                adicionar_poligono(&objetos, (Ponto){0, 0}, 1);
                printf("Pol�gono finalizado!\n");
            }
            break;
        case 'l':
            if (objetos.linha_selecionada != -1) {
                calcularCentroideLinha(&objetos.linhas[objetos.linha_selecionada]);
                transladar(-objetos.linhas[objetos.linha_selecionada].xcentroide, -objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
                rotacionar(10, &objetos.linhas[objetos.linha_selecionada], LINHA);
                transladar(objetos.linhas[objetos.linha_selecionada].xcentroide, objetos.linhas[objetos.linha_selecionada].ycentroide, &objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if(objetos.ponto_selecionado != -1) {
                    rotacionar(10, &objetos.pontos[objetos.ponto_selecionado], PONTO);
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
            } else if(objetos.ponto_selecionado != -1) {
                rotacionar(-10, &objetos.pontos[objetos.ponto_selecionado], PONTO);
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
        case 0x7F:
            deletar_objeto_selecionado(&objetos);
            break;
        case 'd':
            if (objetos.ponto_selecionado != -1) {
                reflexao_diagonal(&objetos.pontos[objetos.ponto_selecionado], PONTO);
            } else if (objetos.linha_selecionada != -1) {
                reflexao_diagonal(&objetos.linhas[objetos.linha_selecionada], LINHA);
            } else if (objetos.poligono_selecionado != -1) {
                reflexao_diagonal(&objetos.poligonos[objetos.poligono_selecionado], POLIGONO);
            }
            break;
        case 'g':
            salvar_json(&objetos);
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



void mouse(int button, int state, int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    float aspect_ratio = (float)width / (float)height;

    float x_convertido, y_convertido;

    if (aspect_ratio >= 1.0) {
        x_convertido = ((float)x / width) * 500.0f * aspect_ratio - 250.0f * aspect_ratio;
        y_convertido = ((float)(height - y) / height) * 500.0f - 250.0f;
    } else {
        x_convertido = ((float)x / width) * 500.0f - 250.0f;
        y_convertido = ((float)(height - y) / height) * 500.0f / aspect_ratio - 250.0f / aspect_ratio;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (modo_desenho == 0) {
            adicionar_ponto(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 1) {
            adicionar_linha(&objetos, x_convertido, y_convertido);
        } else if (modo_desenho == 2) {
            adicionar_poligono(&objetos, (Ponto){x_convertido, y_convertido}, 0);
        }
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        selecionar_ponto(&objetos, x_convertido, y_convertido);
        selecionar_linha(&objetos, x_convertido, y_convertido);
        selecionar_area(&objetos, x_convertido, y_convertido);
    }

    glutPostRedisplay();
}

void inicializar() {
    objetos = criar_objetos();

    FILE *file = fopen("desenhos.json", "r");
    if (file) {
        fclose(file);
        carregar_json(&objetos);
        printf("Arquivo 'desenhos.json' carregado com sucesso.\n");
    } else {
        printf("Arquivo 'desenhos.json' n�o encontrado. Nenhum dado carregado.\n");
    }

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Paint OpenGL");

    inicializar();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclas_especiais);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}