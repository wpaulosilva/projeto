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
 
#pragma region Criar Antena
 
 /**
  * @brief Cria uma nova antena
  * Aloca a memória para a nova antena
  * Recebe a frequência e as coordenadas x e y
  * Retorna um ponteiro onde esta essa memoria alocada
  * 
  * @param frequencia A frequência da antena
  * @param x Coordenada x
  * @param y Coordenada y
  */
 Antena* CriaAntena(char frequencia, int x, int y) {
     Antena* aux;
     aux = (Antena*)malloc(sizeof(Antena));
 
     if (aux != NULL) {
         aux->frequencia = frequencia;
         aux->x = x;
         aux->y = y;
         aux->adj = NULL;
         aux->next = NULL;
     }
     return aux;
 }
 
 #pragma endregion
 
#pragma region Procurar Antena
 
 /**
  * @brief Procura uma antena na lista nas coordenadas x e y
  * Percorre a lista de antenas a antena se o x e y forem iguais
  * 
  * Recebe o ponteiro do inicio da lista 
  * Retorna NULL se não encontrar
  * Retorna o ponteiro para a antena encontrada 
  * 
  * @param lista Lista das antenas
  * @param x Coordenada x
  * @param y Coordenada y
  * @return Ponteiro para a antena encontrada ou NULL se não encontrar
  */
 Antena* ProcuraAntena(Antena* lista, int x, int y) {
     for (Antena* aux = lista; aux != NULL; aux = aux->next) {
         if (aux->x == x && aux->y == y){
             return aux;
         }
     }
     return NULL;
 }
 #pragma endregion
 
#pragma region Inserir Antena
 
 /**
  * @brief Insere uma antena na lista de forma ordenada por coordenadas
  * A antena é inserida em uma posição onde as antenas são ordenadas pelo y e depois se for igual o x
  *  
  * Recebe o ponteiro do inicio da lista 
  * Recebe a frequência e as coordenadas x e y
  * Retorna o ponteiro do inicio da lista atualizada
  * 
  * @param lista Lista de antenas
  * @param frequencia Frequência da antena
  * @param x Coordenada x
  * @param y Coordenada y
  * @return Lista de antenas atualizada
  */
 
 Antena* InserirAntena(Antena* lista, char frequencia, int x, int y) {
   
     if (ProcuraAntena(lista, x, y)){
         return lista;
     }
 
     Antena* aux;
     aux = CriaAntena(frequencia, x, y);
     
     if (aux == NULL){
         return lista;
     } 
 
     if (lista == NULL || (lista->y > y || (lista->y == y && lista->x > x))) {
         aux->next = lista;
         return aux;
     }
 
     Antena* a = lista;
     while (a->next && (a->next->y < y || (a->next->y == y && a->next->x < x))) {
         a = a->next;
     }
     aux->next = a->next;
     a->next = aux;
     return lista;
 }
 #pragma endregion
 
#pragma region Remover Antena
 
 /**
  * @brief Remove uma antena
  * 
  * Recebe o ponteiro do inicio da lista
  * Recebe as coordenadas x e y
  * Retorna o ponteiro do inicio da lista atualizada
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
     
     if (lista->x == x && lista->y == y) {
         Antena* aux2 = lista->next;
         free(lista);
         return aux2;
     }
 
     Antena* aux = lista;
     while (aux->next && (aux->next->x != x || aux->next->y != y)) {
         aux = aux->next;
     }
 
     if (aux->next){
         Antena* aux2 = aux->next;
         aux->next = aux2->next;
         free(aux2);
     }
 
     return lista;
 }
 #pragma endregion
 
#pragma region Calcular Nefasto
 
 /**
  * @brief Calcular as antenas com efeito nefasto
  * 
  * Recebe o ponteiro do inicio da lista
  * Retorna o ponteiro do inicio da lista atualizada
  * 
  * @param lista Lista de antenas
  * @return Lista de antenas com efeito nefasto
  */
 Antena* CalculaNefasto(Antena* lista) {
    int tamanho = 3;

    for (Antena* a = lista; a != NULL; a = a->next) {
        for (Antena* b = a->next; b != NULL; b = b->next) {
            if (a->frequencia == b->frequencia) {
                int novoX, novoY;

                if (a->x == b->x && abs(a->y - b->y) == tamanho) {
                    if (a->y < b->y) {
                        novoY = a->y - tamanho;
                        lista = InserirAntena(lista, '#', a->x, novoY);
                        novoY = b->y + tamanho;
                        lista = InserirAntena(lista, '#', b->x, novoY);
                    } else {
                        novoY = a->y + tamanho;
                        lista = InserirAntena(lista, '#', a->x, novoY);
                        novoY = b->y - tamanho;
                        lista = InserirAntena(lista, '#', b->x, novoY);
                    }
                } 
                else if (a->y == b->y && abs(a->x - b->x) == tamanho) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        lista = InserirAntena(lista, '#', novoX, a->y);
                        novoX = b->x + tamanho;
                        lista = InserirAntena(lista, '#', novoX, b->y);
                    } else {
                        novoX = a->x + tamanho;
                        lista = InserirAntena(lista, '#', novoX, a->y);
                        novoX = b->x - tamanho;
                        lista = InserirAntena(lista, '#', novoX, b->y);
                    }
                } 
                else if (abs(a->x - b->x) == tamanho && abs(a->y - b->y) == tamanho && (a->x - b->x) == (a->y - b->y)) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        novoY = a->y - tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                        novoX = b->x + tamanho;
                        novoY = b->y + tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                    } else {
                        novoX = a->x + tamanho;
                        novoY = a->y + tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                        novoX = b->x - tamanho;
                        novoY = b->y - tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                    }
                }
                else if (abs(a->x - b->x) == tamanho && abs(a->y - b->y) == tamanho && (a->x - b->x) == -(a->y - b->y)) {
                    if (a->x < b->x) {
                        novoX = a->x - tamanho;
                        novoY = a->y + tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                        novoX = b->x + tamanho;
                        novoY = b->y - tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                    } else {
                        novoX = a->x + tamanho;
                        novoY = a->y - tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                        novoX = b->x - tamanho;
                        novoY = b->y + tamanho;
                        lista = InserirAntena(lista, '#', novoX, novoY);
                    }
                }
            }
        }
    }
    return lista;
}
 #pragma endregion
 
#pragma region Ler Antenas 
 
/**
  * @brief Lê as antenas do ficheiro de texto
  * 
  * Recebe o nome do ficheiro e o ponteiro para o inicio da lista
  * Retorna o ponteiro para a lista atualizada
  * 
  * Guarda até 200 caracteres por linha
  * @param lista Lista de antenas
  * @return Lista de antenas atualizada
  */
 Antena* LerAntenas(char* nome_ficheiro, Antena* lista) {
     FILE* ficheiro = fopen(nome_ficheiro, "r");
     if (ficheiro == NULL) {
         return lista;
     }
 
     char* linha = malloc(200); 
     int y = 0;
 
     for (int x = 0; fgets(linha, 200, ficheiro) != NULL; y++) {
         for (int x = 0; linha[x] != '\0'; x++) {
             if (linha[x] != '.' && linha[x] != '\n') {
                 lista = InserirAntena(lista, linha[x], x, y);
             }
         }
     }
 
     free(linha);
     fclose(ficheiro);
     return lista;
 }
 
 #pragma endregion
 
#pragma region Criar Arestas
 /**
 * @brief Cria uma nova aresta
 * 
 * Recebe a antena de destino e um ponteiro para validação
 * Retorna um ponteiro para a nova aresta criada
 * 
 * @param destino Antena de destino
 * @param validar Validação
 * @return Nova aresta criada
 */
Adj* CriarAresta(Antena* destino) {
    
    Adj* aux; 
    aux = (Adj*)malloc(sizeof(Adj));
    
    if (aux == NULL) {
        return NULL;
    }

    aux->destino = destino;
    aux->prox = NULL;

    return aux;
}
#pragma endregion

#pragma region Inserir Aresta
/**
 * @brief Insere uma aresta na lista
 *  
 * Recebe o ponteiro para a antena de início, a aresta a inserir e um ponteiro para validação
 * Retorna a lista de adjacências atualizada
 * 
 * @param inicio Antena onde a aresta será inserida.
 * @param aresta Aresta a inserir
 * @param validar Validação
 * @return Lista de adjacências atualizada
 */
Adj* InserirAresta(Antena* inicio, Antena* destino) {
    
    if(inicio == NULL){
        return NULL;
    }

    if(destino == NULL){
        return NULL;
    }

    Adj* novaAresta = (Adj*)malloc(sizeof(Adj));
    
    if (novaAresta == NULL){
        return NULL;
    }

    novaAresta->destino = destino;
    novaAresta->prox = NULL;

    if (inicio->adj == NULL) {
        inicio->adj = novaAresta;
    } else {
        Adj* aux = inicio->adj;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novaAresta;
    }
    return novaAresta;
}

#pragma endregion

#pragma region Criar grafo
/**
 * @brief Cria o grafo de antenas
 * 
 * Recebe o ponteiro para a lista de antenas
 * Retorna a lista de antenas com as arestas criadas
 * 
 * Percorre cada antena na lista
 * Se a antena for diferente e tiver a mesma frequência, cria uma aresta e retorna true
 * 
 * @param lista Lista de antenas
 * @return Lista de antenas com arestas criadas
 */

Antena* CriarGrafo(Antena* lista) {
    if (lista == NULL) return NULL;

    Antena* aux = lista;

    while (aux != NULL) {
        Antena* aux2 = lista;
        
        while (aux2 != NULL) {
            if (aux2 != aux && aux2->frequencia == aux->frequencia) {
                InserirAresta(aux, aux2);
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
    return lista;
}


#pragma endregion

#pragma region Remover Aresta
/**
 * @brief Remove uma aresta entre duas antenas
 * 
 * Recebe o ponteiro para a antena de início e o ponteiro para a antena de destino
 * Retorna true se a aresta foi removida com sucesso, false caso contrário
 * 
 * @param inicio Ponteiro para a antena de início
 * @param destino Ponteiro para a antena de destino
 * @return true se a aresta foi removida com sucesso, false caso contrário
 */
bool RemoverAresta(Antena* inicio, Antena* destino) {
    if (inicio == NULL || destino == NULL || inicio->adj == NULL) {
        return false;
    }

    Adj* aux = inicio->adj;
    Adj* aux2 = NULL;

    while (aux != NULL) {
        if (aux->destino == destino) {
            // Encontrou a aresta a remover
            if (aux2 == NULL) {
                // A aresta a remover é a primeira da lista
                inicio->adj = aux->prox;
            } else {
                // Aresta está no meio ou fim da lista
                aux2->prox = aux->prox;
            }
            free(aux);
            return true;  // Remoção feita com sucesso
        }
        aux2 = aux;
        aux = aux->prox;
    }
    return false; // Aresta não encontrada
}

#pragma endregion

#pragma region Profundidade

/**
 * @brief Adiciona uma antena à lista de profundidade
 * 
 * Cria uma nova celula para guardar uma antena
 * Adiciona no fim da lista
 * Retorna a lista
 * 
 * Recebe o ponteiro para a lista de profundidade e um ponteiro para a antena
 * Retorna o ponteiro para a lista de profundidade atualizada
 * 
 * @param profundidade Ponteiro para a lista de profundidade
 * @param antena Ponteiro para a antena a adicionar
 * @return Ponteiro para a lista de profundidade atualizada
 */

Profundidade* adicionarAProfundidade(Profundidade* profundidade, Antena* antena) {

    Profundidade* aux = malloc(sizeof(Profundidade));
    if (aux == NULL){
        return profundidade;
    }

    aux->antena = antena;
    aux->prox = NULL;

    if (profundidade == NULL) {
        return aux;
    }

    Profundidade* aux2 = profundidade;
    while (aux2->prox != NULL) {
        aux2 = aux2->prox;
    }
    aux2->prox = aux;

    return profundidade;
}

/**
 * @brief Visita as antenas em profundidade
 * 
 * Mete a antena como visitada
 * Adiciona a antena à lista
 * Vai visitar todos os adjacentes nao visitados
 * Retorna a lista
 * 
 * Recebe o ponteiro para a antena atual e a lista de profundidade
 * Retorna a lista de profundidade atualizada
 * 
 * @param origem Ponteiro para a antena atual
 * @param profundidade Ponteiro para a lista de profundidade
 * @return Ponteiro para a lista de profundidade atualizada
 */

Profundidade* verProfundidade(Antena* origem, Profundidade* profundidade) {
    
    if (origem == NULL || origem->marcado){
        return profundidade;
    }

    // printf("Debug: %c (%d, %d)\n", atual->frequencia, atual->x, atual->y); // debug

    origem->marcado = true;
    profundidade = adicionarAProfundidade(profundidade, origem);

    for (Adj* aux = origem->adj; aux != NULL; aux = aux->prox) {
        if (!aux->destino->marcado) {
            profundidade = verProfundidade(aux->destino, profundidade);
        }
    }

    return profundidade;
}

#pragma endregion

#pragma region Caminho

/**
 * @brief Encontra todos os caminhos entre duas antenas
 * 
 * Recebe o ponteiro para a antena de origem, o ponteiro para a antena de destino, o caminho atual e a lista de caminhos
 * Retorna a lista de caminhos encontrados
 * 
 * @param origem Ponteiro para a antena de origem
 * @param destino Ponteiro para a antena de destino
 * @param caminhoAtual Ponteiro para o caminho atual
 * @param listaCaminhos Ponteiro para a lista de caminhos encontrados
 * @return Lista de caminhos encontrados
 */

ListaCaminhos* Caminhos(Antena* origem, Antena* destino, Caminho* caminhoAtual, ListaCaminhos* listaCaminhos) {
    
    if (origem == NULL){
        return listaCaminhos;
    }

    origem->marcado = true;

    Caminho* aux = malloc(sizeof(Caminho));
    aux->antena = origem;
    aux->prox = caminhoAtual;
    caminhoAtual = aux;

    if (origem == destino) {
        ListaCaminhos* novoCaminho = malloc(sizeof(ListaCaminhos));
        novoCaminho->caminho = caminhoAtual;
        novoCaminho->prox = listaCaminhos;
        listaCaminhos = novoCaminho;
    } else {
        // falta a parte de percorrer o grafo
    }

    return listaCaminhos;
}

#pragma endregion

#pragma region Gravar
 
 /**
  * @brief Grava as antenas no ficheiro antenas2.bin
  * Cada antena é gravada no formato `AntenaFile`, que contém frequência e coordenadas
  * 
  * Recebe o nome do ficheiro e a lista de antenas
  * Retorna verdadeiro se a gravação for bem-sucedida, falso caso contrário
  * 
  * @param nome_ficheiro Nome do ficheiro onde as antenas serão gravadas
  * @param lista Lista de antenas a ser gravada
  * @return Verdadeiro se a gravação for bem-sucedida, falso caso contrário
  */
bool GravaAntenasBinario(char* nome_ficheiro, Antena* lista) {
    
    FILE* ficheiro = fopen(nome_ficheiro, "wb");
    
    if (ficheiro == NULL) {
        return false;
    }

    for (Antena* a = lista; a != NULL; a = a->next) {
        AntenaFile auxAnten = {a->frequencia, a->x, a->y};
        fwrite(&auxAnten, sizeof(AntenaFile), 1, ficheiro);

        int numArestas = 0;
        for (Adj* adj = a->adj; adj != NULL; adj = adj->prox) {
            numArestas++;
        }
        fwrite(&numArestas, sizeof(int), 1, ficheiro);

        for (Adj* adj = a->adj; adj != NULL; adj = adj->prox) {
            ArestaFile aresta = {adj->destino->x, adj->destino->y};
            fwrite(&aresta, sizeof(ArestaFile), 1, ficheiro);
        }
    }

    fclose(ficheiro);
    return true;
}

 #pragma endregion