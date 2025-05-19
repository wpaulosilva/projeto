#include <stdio.h>
#include <stdlib.h>
#include "../src/dados.h"

int main() {
    Antena* lista = NULL;
    lista = LerAntenas("antenas.txt", lista);

    #pragma region Inserir Antena
    lista = InserirAntena(lista, 'A', 5, 7);
    #pragma endregion

    #pragma region Remover Antena
    lista = RemoveAntena(lista, 9, 5);
    #pragma endregion

    #pragma region Calcular Nefasto
    lista = CalculaNefasto(lista);   
    #pragma endregion

    #pragma region Criar Grafo
    lista = CriarGrafo(lista);

    printf("\nGrafo:\n");
    for (Antena* a = lista; a != NULL; a = a->next) {
        printf("\n%c - (%d,%d): ", a->frequencia, a->x, a->y);
        for (Adj* ad = a->adj; ad != NULL; ad = ad->prox) {
            printf("(%c - %d,%d) ", ad->destino->frequencia, ad->destino->x, ad->destino->y);
        }
    }
    printf("\n");

    #pragma endregion

    int origemX = 5; 
    int origemY = 0;

    Antena* origem = ProcuraAntena(lista, origemX, origemY);

    #pragma region Largura

    tirarVisitado(lista);   
    Antena* resultadoLargura = Largura(lista, origem);

    printf("\nLargura:\n", origemX, origemY);
    for (Antena* a = resultadoLargura; a != NULL; a = a->next) {
        printf("Tipo: %c, Coordenadas: (%d, %d)\n", a->frequencia, a->x, a->y);
    }

    #pragma endregion
    
    #pragma region Profundidade

    Profundidade* listaProfundidade = NULL;
    listaProfundidade = visitarProfundidade(origem, listaProfundidade);

    Profundidade* temp = listaProfundidade;
    while (temp != NULL) {
        printf("Tipo: %c, Coordenadas: (%d, %d)\n", temp->antena->frequencia, temp->antena->x, temp->antena->y);
        temp = temp->prox;
    }

    #pragma endregion

    #pragma region Gravar Antenas
    GravaAntenasBinario("antenas2.bin", lista);
    #pragma endregion
        
    return 0;
}