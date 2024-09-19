#ifndef OBJETOS_H
#define OBJETOS_H

typedef struct {
    float x, y;
} Ponto;

typedef struct {
    Ponto inicio, fim;
} Linha;

typedef struct {
    Ponto* vertices;
    int num_vertices;
} Poligono;

typedef struct {
    Ponto* pontos;
    Linha* linhas;
    Poligono* poligonos;
    int num_pontos, num_linhas, num_poligonos;
} ObjetosGeometricos;

ObjetosGeometricos criar_objetos();
void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y);
void remover_ultimo_ponto(ObjetosGeometricos* objetos);
void adicionar_linha(ObjetosGeometricos* objetos, float x, float y);
void desenhar_objetos(ObjetosGeometricos* objetos);
int selecionar_objeto(ObjetosGeometricos* objetos, int x, int y);
void excluir_objeto(ObjetosGeometricos* objetos, int indice);

#endif