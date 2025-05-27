/**
 * @file main.c
 * @author Paulo Silva (a31506@alunos.ipca.pt)
 * @brief Ficheiro main para chamar as funções
 * @version 0.1
 * @date 2025-03-20
 * 
 * @copyright Copyright (c) 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "../src/dados.h"

int main() {
    Antena* lista = NULL;
    lista = LerAntenas("antenas.txt", lista);

    #pragma region Inserir Antena
    // if (InserirAntena(&lista, 'A', 10, 15)) {
    //     printf("Antena inserida!\n");
    // } else {
    //     printf("Erro!\n");
    // }
    #pragma endregion

    #pragma region Remover Antena
    //lista = RemoveAntena(lista, 9, 5);
    #pragma endregion

    #pragma region Calcular Nefasto
    // lista = CalculaNefasto(lista);   
    #pragma endregion

    Antena* origem = ProcuraAntena(lista, 7,1 );
    Antena* destino = ProcuraAntena(lista, 9, 7);

    #pragma region Inserir Aresta
        // if (InserirAresta(origem, destino)) {
        //     printf("Aresta inserida!\n");
        // } else {
        //     printf("Erro!\n");
        // } 
    #pragma endregion

    #pragma region Criar Grafo
    if (CriarGrafo(lista)) {
        printf("Grafo criado!\n");
    } else {
        printf("Erro!\n");
    }
    #pragma endregion

    #pragma region Remover Aresta
        // if (RemoverAresta(origem, destino)) {
        //     printf("Aresta Removida!\n");
        // } else {
        //     printf("Erro!\n");
        // } 
    #pragma endregion

    #pragma region Profundidade
    
    Profundidade* listaProf = NULL;
    listaProf = verProfundidade(origem, listaProf);

    Profundidade* aux = listaProf;
    
    while (aux != NULL) {
        // printf("Ola");
        printf("Tipo: %c, Coordenadas: (%d, %d)\n", aux->antena->frequencia, aux->antena->x, aux->antena->y);
        aux = aux->prox;
    }       
  
    #pragma endregion

    #pragma region Gravar Antenas
    GravaAntenasBinario("antenas2.bin", lista);
    #pragma endregion
        
    return 0;
}