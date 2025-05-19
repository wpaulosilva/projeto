#include <stdio.h>
#include <stdlib.h>
#include "../src/dados.h"

int main() {
    Antena* lista = NULL;
    lista = LerAntenas("antenas.txt", lista);

    #pragma region Inserir Antena
    // lista = InserirAntena(lista, 'A', 5, 7);
    lista = InserirAntena(lista, 'B', 9, 7);
    #pragma endregion

    #pragma region Remover Antena
    // lista = RemoveAntena(lista, 9, 5);
    #pragma endregion

    #pragma region Calcular Nefasto
    lista = CalculaNefasto(lista);   
    #pragma endregion

    Antena* origem = ProcuraAntena(lista, 7,1 );
    Antena* destino = ProcuraAntena(lista, 9, 7);

    #pragma region Criar Aresta
    InserirAresta(origem, destino);
    #pragma endregion

    lista = CriarGrafo(lista);

    #pragma region Remover Aresta
    RemoverAresta(origem, destino);
    #pragma endregion

    #pragma region Mostrar Grafo

    printf("\nGrafo:\n");
    for (Antena* a = lista; a != NULL; a = a->next) {
        printf("\n%c - (%d,%d): ", a->frequencia, a->x, a->y);
        for (Adj* ad = a->adj; ad != NULL; ad = ad->prox) {
            printf("(%c - %d,%d) ", ad->destino->frequencia, ad->destino->x, ad->destino->y);
        }
    }
    printf("\n");
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