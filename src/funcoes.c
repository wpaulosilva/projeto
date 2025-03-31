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
     a->next = nova; //atualiza o a 
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
     Antena* atual = lista;
 
     while (atual) {
         (*num_antenas)++;
         atual = atual->next;
     }
 
     Antena* resultado;
     resultado = (Antena*)malloc(sizeof(Antena) * (*num_antenas));
 
     if (!resultado) return NULL;
 
     atual = lista;
     for (int i = 0; atual; atual = atual->next, i++) {
         resultado[i] = *atual;
     }
 
     return resultado;
 }
 #pragma endregion
 
 #pragma region CalculaNefasto
 
 /**
  * @brief Calcula as antenas com efeito nefasto
  * Quando tem duas antenas da mesma frequência na mesma coluna, a com menos valor tira dois e na maior soma mais 2
  * Quando tem duas antenas da mesma frequência na mesma linha, a com menos valor tira dois e na maior soma mais 2
  * 
  * @param lista Lista de antenas
  * @return Lista de antenas com efeito nefasto
  */
 Antena* CalculaNefasto(Antena* lista) {
     printf("\nEfeito nefasto:\n");
 
     for (Antena* a = lista; a != NULL; a = a->next) {
         for (Antena* b = a->next; b != NULL; b = b->next) {
             if (a->frequencia == b->frequencia) {
                 if (a->x == b->x && abs(a->y - b->y) == 2) { // vertical
                     int aux = a->y;
                     
                     if (a->y < b->y) {
                         a->y = a->y - 2;
                     } else {
                         a->y = a->y + 2;
                     }
                     
                     if (aux < b->y) {
                         b->y = b->y + 2;
                     } else {
                         b->y = b->y - 2;
                     }
                 
                     printf("Vertical: (%d, %d) e (%d, %d)\n", a->x, a->y, b->x, b->y);
                 } 
                 else if (a->y == b->y && abs(a->x - b->x) == 2) { // horizontal
                     int aux = a->x;
                     
                     if (a->x < b->x) {
                         a->x = a->x - 2;
                     } else {
                         a->x = a->x + 2;
                     }
                     
                     if (aux < b->x) {
                         b->x = b->x + 2;
                     } else {
                         b->x = b->x - 2;
                     }
                 
                     printf("Horizontal: (%d, %d) e (%d, %d)\n", a->x, a->y, b->x, b->y);
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