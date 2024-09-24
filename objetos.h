#ifndef OBJETOS_H
#define OBJETOS_H

typedef struct {
    float x, y;
} Ponto;

typedef struct {
    Ponto inicio, fim;
    float xcentroide;
    float ycentroide;
} Linha;

typedef struct {
    Ponto* pontos;
    int num_pontos;
    float xcentroide;
    float ycentroide;
} Poligono;

typedef struct {
    Ponto* pontos;
    Linha* linhas;
    Poligono* poligonos;
    int num_pontos;
    int num_linhas;
    int num_poligonos;

    int ponto_selecionado;
    int linha_selecionada;
    int poligono_selecionado;
} ObjetosGeometricos;

ObjetosGeometricos criar_objetos();

void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y);

void remover_ultimo_ponto(ObjetosGeometricos* objetos);

void cancelar_operacao(ObjetosGeometricos* objetos);

void deletar_objeto_selecionado(ObjetosGeometricos* objetos);

void adicionar_linha(ObjetosGeometricos* objetos, float x, float y);

void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar);

void desenhar_objetos(ObjetosGeometricos* objetos);

void setar_ponto_selecionado(ObjetosGeometricos* objetos, int indice);

#endif
