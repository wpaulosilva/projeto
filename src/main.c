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
#include "dados.h"

int main() {
    Antena* lista = NULL;
    lista = LerAntenas("antenas.txt", lista);

    #pragma region Inserir Antena
    //lista = InsereOrdenado(lista, 'A', 3, 4);
    #pragma endregion

    #pragma region Remover Antena
    //lista = RemoveAntena(lista, 3, 4);
    #pragma endregion

    #pragma region Listar Antena

    printf("Lista de antenas:\n");
    for (Antena* a = lista; a != NULL; a = a->next) {
        printf("Frequência: %c, Posição: (%d, %d)\n", a->frequencia, a->x, a->y);
    }
    
    #pragma endregion
    
    #pragma region Calculo do Nefasto
    CalculaNefasto(lista);
    #pragma endregion

    #pragma region Gravação das Antenas
    GravaAntenasBinario("antenas2.bin", lista);
    #pragma endregion

    return 0;
}