#ifndef OBJETOS_H
#define OBJETOS_H

// Definição de uma estrutura para representar um ponto 2D
typedef struct {
    float x, y;
} Ponto;

// Definição de uma estrutura para representar uma linha (composta de dois pontos)
typedef struct {
    Ponto inicio, fim;
} Linha;

// Definição de uma estrutura para representar um polígono (composto por vários vértices)
typedef struct {
    Ponto* pontos;    // Array de pontos que formam o polígono
    int num_pontos;   // Número de vértices (pontos) no polígono
} Poligono;

// Estrutura principal que contém listas de pontos, linhas e polígonos
typedef struct {
    Ponto* pontos;        // Array de pontos
    Linha* linhas;        // Array de linhas
    Poligono* poligonos;  // Array de polígonos
    int num_pontos;       // Quantidade de pontos armazenados
    int num_linhas;       // Quantidade de linhas armazenadas
    int num_poligonos;    // Quantidade de polígonos armazenados
} ObjetosGeometricos;

// Funções públicas para manipulação dos objetos geométricos

// Função para criar a estrutura que armazena os objetos geométricos
ObjetosGeometricos criar_objetos();

// Função para adicionar um ponto
void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y);

// Função para remover o último ponto adicionado
void remover_ultimo_ponto(ObjetosGeometricos* objetos);

void cancelar_operacao(ObjetosGeometricos* objetos);

// Função para adicionar uma linha (necessita de dois cliques/pontos)
void adicionar_linha(ObjetosGeometricos* objetos, float x, float y);

// Função para adicionar um polígono, com `finalizar` indicando se o polígono está completo
void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar);

// Função para desenhar todos os objetos geométricos (pontos, linhas, polígonos)
void desenhar_objetos(ObjetosGeometricos* objetos);

#endif
