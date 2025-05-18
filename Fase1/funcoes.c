/**
 * @file funcoes.c
 * @author Paulo Silva (a31506@alunos.ipca.pt)
 * @brief Implementar funções
 * @version 0.1
 * @date 2025-03-20
 * 
 * @copyright Copyright (c) 2025
 */

 #include "dados.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 #pragma region CriaAntena
 
 /**
  * @brief Cria uma nova antena
  * Aloca a memória e começa com os valores da antena com a frequência, x e y
  * 
  * @param frequencia A frequência da antena
  * @param x Coordenada x
  * @param y Coordenada y
  */
 Antena* CriaAntena(char frequencia, int x, int y) {
     Antena* nova;
     nova = (Antena*)malloc(sizeof(Antena));
 
     if (nova != NULL) {
         nova->frequencia = frequencia;
         nova->x = x;
         nova->y = y;
         nova->next = NULL;
     }
     return nova;
 }
 
 #pragma endregion
 
 #pragma region ProcuraAntena
 
 /**
  * @brief Procura uma antena na lista nas coordenadas x e y
  * Percorre a lista de antenas e retorna a primeira antena que tem as coordenadas fornecidas
  * 
  * @param lista Lista das antenas
  * @param x Coordenada x
  * @param y Coordenada y
  * @return Ponteiro para a antena encontrada ou NULL se não encontrar
  */
 Antena* ProcuraAntena(Antena* lista, int x, int y) {
     for (Antena* a = lista; a != NULL; a = a->next) {
         if (a->x == x && a->y == y){
             return a;
         }
     }
     return NULL;
 }
 #pragma endregion
 
 #pragma region InsereOrdenado
 
 /**
  * @brief Insere uma antena na lista de forma ordenada por coordenadas
  * A antena é inserida em uma posição onde as antenas são ordenadas pelo y e depois se for igual o x
  *  
  * @param lista Lista de antenas
  * @param frequencia Frequência da antena
  * @param x Coordenada x
  * @param y Coordenada y
  * @return Lista de antenas atualizada
  */
 
 Antena* InsereOrdenado(Antena* lista, char frequencia, int x, int y) {
   
     if (ProcuraAntena(lista, x, y)){
         return lista; //Se já existe
     }
 
     Antena* nova; // cria antena
     nova = CriaAntena(frequencia, x, y);
     
     if (nova == NULL){
         return lista;
     } 
 
     if (lista == NULL || (lista->y > y || (lista->y == y && lista->x > x))) {
         nova->next = lista;
         return nova;
     }
 
     Antena* a = lista;
     while (a->next && (a->next->y < y || (a->next->y == y && a->next->x < x))) {
         a = a->next;
     }
     nova->next = a->next;
     a->next = nova;
     return lista;
 }
 #pragma endregion
 
 #pragma region RemoveAntena
 
 /**
  * @brief Remove uma antena com a posicao indicada
  *  
  * @param lista Lista de antenas
  * @param x Coordenada x
  * @param y Coordenada y
  * @return Lista de antenas atualizada
  */
 
 Antena* RemoveAntena(Antena* lista, int x, int y) {
     
     if (lista == NULL){
         return NULL;
     }
     
     if (lista->x == x && lista->y == y) { //se for a primeira
         Antena* temp = lista->next;
         free(lista);
         return temp;
     }
 
     Antena* atual = lista;
     while (atual->next && (atual->next->x != x || atual->next->y != y)) {
         atual = atual->next;
     }
 
     if (atual->next){
         Antena* temp = atual->next;
         atual->next = temp->next;
         free(temp);
     }
 
     return lista;
 }
 #pragma endregion
 
 #pragma region Listantena
 
 /**
  * @brief Lista todas as antenas da lista
  * Conta o número total de antenas na lista e cria uma nova lista com as antenas.
  * 
  * @param lista Lista de antenas
  * @param num_antenas Número total de antenas na lista
  * @return Lista de antenas copiada para um novo array
  */
 
 Antena* ListaAntenas(Antena* lista, int* num_antenas) {
     *num_antenas = 0;
     Antena* aux = lista;
 
     while (aux) {
         (*num_antenas)++;
         aux = aux->next;
     }
 
     Antena* resultado;
     resultado = (Antena*)malloc(sizeof(Antena) * (*num_antenas));
 
     if (!resultado) return NULL;
 
     aux = lista;
     for (int i = 0; aux; aux = aux->next, i++) {
         resultado[i] = *aux;
     }
 
     return resultado;
 }
 #pragma endregion
 
 #pragma region CalculaNefasto
 
 /**
  * @brief Calcula as antenas com efeito nefasto
  * @param lista Lista de antenas
  * @return Lista de antenas com efeito nefasto
  */
 Antena* CalculaNefasto(Antena* lista) {
    int tamanho = 2;

    for (Antena* a = lista; a != NULL; a = a->next) {
        for (Antena* b = a->next; b != NULL; b = b->next) {
            if (a->frequencia == b->frequencia) {
                int novoX, novoY;

                if (a->x == b->x && abs(a->y - b->y) == tamanho) {
                    if (a->y < b->y) {
                        novoY = a->y - tamanho;
                        lista = InsereOrdenado(lista, '#', a->x, novoY);
                        novoY = b->y + tamanho;
                        lista = InsereOrdenado(lista, '#', b->x, novoY);
                    } else {
                        novoY = a->y + tamanho;
                        lista = InsereOrdenado(lista, '#', a->x, novoY);
                        novoY = b->y - tamanho;
                        lista = InsereOrdenado(lista, '#', b->x, novoY);
                    }
                } 
                else if (a->y == b->y && abs(a->x - b->x) == tamanho) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, a->y);
                        novoX = b->x + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, b->y);
                    } else {
                        novoX = a->x + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, a->y);
                        novoX = b->x - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, b->y);
                    }
                } 
                else if (abs(a->x - b->x) == tamanho && abs(a->y - b->y) == tamanho && (a->x - b->x) == (a->y - b->y)) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        novoY = a->y - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                        novoX = b->x + tamanho;
                        novoY = b->y + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                    } else {
                        novoX = a->x + tamanho;
                        novoY = a->y + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                        novoX = b->x - tamanho;
                        novoY = b->y - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                    }
                }
                else if (abs(a->x - b->x) == tamanho && abs(a->y - b->y) == tamanho && (a->x - b->x) == -(a->y - b->y)) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        novoY = a->y + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                        novoX = b->x + tamanho;
                        novoY = b->y - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                    } else {
                        novoX = a->x + tamanho;
                        novoY = a->y - tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                        novoX = b->x - tamanho;
                        novoY = b->y + tamanho;
                        lista = InsereOrdenado(lista, '#', novoX, novoY);
                    }
                }
            }
        }
    }
    return lista;
}
 #pragma endregion
 
 #pragma region LerAntenas
 
 Antena* LerAntenas(const char* nome_ficheiro, Antena* lista) {
     FILE* ficheiro = fopen(nome_ficheiro, "r");
     if (ficheiro == NULL) {
         return lista;
     }
 
     char* linha = malloc(200); 
     int y = 0;
 
     for (int x = 0; fgets(linha, 200, ficheiro) != NULL; y++) {
         for (int x = 0; linha[x] != '\0'; x++) {
             if (linha[x] != '.' && linha[x] != '\n') {
                 lista = InsereOrdenado(lista, linha[x], x, y);
             }
         }
     }
 
     free(linha);
     fclose(ficheiro);
     return lista;
 }
 
 #pragma endregion
 
 #pragma region GravarAntena
 
 /**
  * @brief Grava as antenas em formato binário no ficheiro antenas2.bin
  * Cada antena é gravada no formato `AntenaFile`, que contém frequência e coordenadas
  * 
  * @param nome_ficheiro Nome do ficheiro onde as antenas serão gravadas
  * @param lista Lista de antenas a ser gravada
  * @return Verdadeiro se a gravação for bem-sucedida, falso caso contrário
  */
 bool GravaAntenasBinario(const char* nome_ficheiro, Antena* lista) {
     FILE* ficheiro = fopen(nome_ficheiro, "wb");
     
     if (ficheiro == NULL) {
         return false;
     }
 
     for (Antena* a = lista; a != NULL; a = a->next) {
         AntenaFile aux = {a->frequencia, a->x, a->y};
         fwrite(&aux, sizeof(AntenaFile), 1, ficheiro);
     }
 
     fclose(ficheiro);
     return true;
 }
 #pragma endregion

 #pragma region LerFicheiroBin

 /**
  * @brief Lê as antenas do ficheiro binário
  * @return Lista ligada de antenas
  */
 Antena* LerAntenasBinario(const char* nome_ficheiro) {
     FILE* fp;
     Antena* lista = NULL;
     Antena* nova;
 
     if ((fp = fopen(nome_ficheiro, "rb")) == NULL) return NULL;
 
     AntenaFile auxAntena;
     while (fread(&auxAntena, sizeof(AntenaFile), 1, fp)) {
         nova = CriaAntena(auxAntena.frequencia, auxAntena.x, auxAntena.y);
         lista = InsereOrdenado(lista, nova->frequencia, nova->x, nova->y);
     }
 
     fclose(fp);
     return lista;
 }
 
 #pragma endregion