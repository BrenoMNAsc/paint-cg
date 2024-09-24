#ifndef OBJETOS_H
#define OBJETOS_H

// Defini??o de uma estrutura para representar um ponto 2D
typedef struct {
    float x, y;
} Ponto;

// Defini??o de uma estrutura para representar uma linha (composta de dois pontos)
typedef struct {
    Ponto inicio, fim;
    float xcentroide;
    float ycentroide;
} Linha;

// Defini??o de uma estrutura para representar um pol?gono (composto por v?rios v?rtices)
typedef struct {
    Ponto* pontos;    // Array de pontos que formam o pol?gono
    int num_pontos;   // N?mero de v?rtices (pontos) no pol?gono
    float xcentroide;
    float ycentroide;
} Poligono;

// Estrutura principal que cont?m listas de pontos, linhas e pol?gonos
typedef struct {
    Ponto* pontos;        // Array de pontos
    Linha* linhas;        // Array de linhas
    Poligono* poligonos;  // Array de pol?gonos
    int num_pontos;       // Quantidade de pontos armazenados
    int num_linhas;       // Quantidade de linhas armazenadas
    int num_poligonos;    // Quantidade de pol?gonos armazenados

    // Adiciona campos para acompanhar qual objeto est? selecionado
    int ponto_selecionado;    // ?ndice do ponto selecionado (-1 se nenhum ponto for selecionado)
    int linha_selecionada;    // ?ndice da linha selecionada (-1 se nenhuma linha for selecionada)
    int poligono_selecionado; // ?ndice do pol?gono selecionado (-1 se nenhum pol?gono for selecionado)
} ObjetosGeometricos;

// Fun??es p?blicas para manipula??o dos objetos geom?tricos

// Fun??o para criar a estrutura que armazena os objetos geom?tricos
ObjetosGeometricos criar_objetos();

// Fun??o para adicionar um ponto
void adicionar_ponto(ObjetosGeometricos* objetos, float x, float y);

// Fun??o para remover o ?ltimo ponto adicionado
void remover_ultimo_ponto(ObjetosGeometricos* objetos);

// Fun??o para cancelar a opera??o atual
void cancelar_operacao(ObjetosGeometricos* objetos);

// Fun??o para adicionar uma linha (necessita de dois cliques/pontos)
void adicionar_linha(ObjetosGeometricos* objetos, float x, float y);

// Fun??o para adicionar um pol?gono, com `finalizar` indicando se o pol?gono est? completo
void adicionar_poligono(ObjetosGeometricos* objetos, Ponto novo_ponto, int finalizar);

// Fun??o para desenhar todos os objetos geom?tricos (pontos, linhas, pol?gonos)
void desenhar_objetos(ObjetosGeometricos* objetos);

// Fun??o para selecionar um ponto pelo ?ndice
void setar_ponto_selecionado(ObjetosGeometricos* objetos, int indice);

#endif
