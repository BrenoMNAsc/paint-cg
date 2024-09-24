#ifndef ARQUIVOS_H
#define ARQUIVOS_H

// Função para salvar os objetos geométricos no arquivo "desenhos.json".
// Recebe um ponteiro para a estrutura ObjetosGeometricos, que contém os dados
// dos pontos, linhas e polígonos a serem salvos.
// O arquivo será criado ou sobrescrito, e os dados serão formatados em JSON.
void salvar_json(ObjetosGeometricos* objetos);

// Função para carregar os objetos geométricos a partir do arquivo "desenhos.json".
// Recebe um ponteiro para a estrutura ObjetosGeometricos, onde os dados carregados
// do arquivo JSON serão armazenados. Caso o arquivo exista, ele será lido e a estrutura
// será preenchida com os pontos, linhas e polígonos contidos no arquivo.
void carregar_json(ObjetosGeometricos* objetos);

#endif // ARQUIVOS_H
