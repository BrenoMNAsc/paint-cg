#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include "objetos.h"

void salvar_json(ObjetosGeometricos* objetos) {
    cJSON *json_objetos = cJSON_CreateObject();

    cJSON *json_pontos = cJSON_CreateArray();
    for (int i = 0; i < objetos->num_pontos; i++) {
        cJSON *json_ponto = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_ponto, "x", objetos->pontos[i].x);
        cJSON_AddNumberToObject(json_ponto, "y", objetos->pontos[i].y);
        cJSON_AddItemToArray(json_pontos, json_ponto);
    }
    cJSON_AddItemToObject(json_objetos, "pontos", json_pontos);

    cJSON *json_linhas = cJSON_CreateArray();
    for (int i = 0; i < objetos->num_linhas; i++) {
        cJSON *json_linha = cJSON_CreateObject();
        cJSON *inicio = cJSON_CreateObject();
        cJSON_AddNumberToObject(inicio, "x", objetos->linhas[i].inicio.x);
        cJSON_AddNumberToObject(inicio, "y", objetos->linhas[i].inicio.y);
        cJSON *fim = cJSON_CreateObject();
        cJSON_AddNumberToObject(fim, "x", objetos->linhas[i].fim.x);
        cJSON_AddNumberToObject(fim, "y", objetos->linhas[i].fim.y);
        cJSON_AddItemToObject(json_linha, "inicio", inicio);
        cJSON_AddItemToObject(json_linha, "fim", fim);
        cJSON_AddItemToArray(json_linhas, json_linha);
    }
    cJSON_AddItemToObject(json_objetos, "linhas", json_linhas);

    cJSON *json_poligonos = cJSON_CreateArray();
    for (int i = 0; i < objetos->num_poligonos; i++) {
        cJSON *json_poligono = cJSON_CreateObject();
        cJSON *json_pontos_poligono = cJSON_CreateArray();
        for (int j = 0; j < objetos->poligonos[i].num_pontos; j++) {
            cJSON *json_ponto_poligono = cJSON_CreateObject();
            cJSON_AddNumberToObject(json_ponto_poligono, "x", objetos->poligonos[i].pontos[j].x);
            cJSON_AddNumberToObject(json_ponto_poligono, "y", objetos->poligonos[i].pontos[j].y);
            cJSON_AddItemToArray(json_pontos_poligono, json_ponto_poligono);
        }
        cJSON_AddItemToObject(json_poligono, "pontos", json_pontos_poligono);
        cJSON_AddItemToArray(json_poligonos, json_poligono);
    }
    cJSON_AddItemToObject(json_objetos, "poligonos", json_poligonos);

    char *json_string = cJSON_Print(json_objetos);
    FILE *file = fopen("desenhos.json", "w");
    if (file) {
        fprintf(file, "%s\n", json_string);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
    }

    cJSON_Delete(json_objetos);
    free(json_string);
}

void carregar_json(ObjetosGeometricos* objetos) {
    FILE *file = fopen("desenhos.json", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo para carregar os dados.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char*) malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';

    cJSON *json_objetos = cJSON_Parse(data);
    if (json_objetos == NULL) {
        printf("Erro ao parsear o arquivo JSON.\n");
        free(data);
        return;
    }

    cJSON *json_pontos = cJSON_GetObjectItem(json_objetos, "pontos");
    objetos->pontos = NULL;
    objetos->num_pontos = 0;
    cJSON *json_ponto;
    cJSON_ArrayForEach(json_ponto, json_pontos) {
        float x = (float)cJSON_GetObjectItem(json_ponto, "x")->valuedouble;
        float y = (float)cJSON_GetObjectItem(json_ponto, "y")->valuedouble;
        adicionar_ponto(objetos, x, y);
    }

    cJSON *json_linhas = cJSON_GetObjectItem(json_objetos, "linhas");
    objetos->linhas = NULL;
    objetos->num_linhas = 0;
    cJSON *json_linha;
    cJSON_ArrayForEach(json_linha, json_linhas) {
        cJSON *inicio = cJSON_GetObjectItem(json_linha, "inicio");
        cJSON *fim = cJSON_GetObjectItem(json_linha, "fim");
        adicionar_linha(objetos, (float)cJSON_GetObjectItem(inicio, "x")->valuedouble,
                        (float)cJSON_GetObjectItem(inicio, "y")->valuedouble);
        adicionar_linha(objetos, (float)cJSON_GetObjectItem(fim, "x")->valuedouble,
                        (float)cJSON_GetObjectItem(fim, "y")->valuedouble);
    }

    cJSON *json_poligonos = cJSON_GetObjectItem(json_objetos, "poligonos");
    objetos->poligonos = NULL;
    objetos->num_poligonos = 0;
    cJSON *json_poligono;
    cJSON_ArrayForEach(json_poligono, json_poligonos) {
        cJSON *json_pontos_poligono = cJSON_GetObjectItem(json_poligono, "pontos");
        Ponto novo_ponto;
        cJSON *json_ponto_poligono;
        cJSON_ArrayForEach(json_ponto_poligono, json_pontos_poligono) {
            novo_ponto.x = (float)cJSON_GetObjectItem(json_ponto_poligono, "x")->valuedouble;
            novo_ponto.y = (float)cJSON_GetObjectItem(json_ponto_poligono, "y")->valuedouble;
            adicionar_poligono(objetos, novo_ponto, 0);
        }
        adicionar_poligono(objetos, novo_ponto, 1);
    }

    cJSON_Delete(json_objetos);
    free(data);
}
