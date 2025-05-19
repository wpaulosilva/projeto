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
 
#pragma region Criar Aresta
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
Adj* CriarAresta(Antena* destino, bool* validar) {
    
    Adj* aux; 
    aux = (Adj*)malloc(sizeof(Adj));

    if (aux) {
        aux->destino = destino;
        aux->prox = NULL;
        *validar = true;
    } else {
        *validar = false;
    }
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
Adj* InserirAresta(Antena* inicio, Adj* aresta, bool* validar) {
    
    if (aresta == NULL || inicio == NULL) {
        *validar = false;
        return NULL;
    }

    if (inicio->adj == NULL) {
        inicio->adj = aresta;
        *validar = true;
        return aresta;
    }

    Adj* aux = inicio->adj;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = aresta;

    *validar = true;
    return inicio->adj;
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
    if (lista == NULL){
        return NULL;
    }

    Antena* aux = lista;
    bool ok;

    while (aux != NULL) {
        Antena* comparar = lista;
        
        while (comparar != NULL) {
            if (comparar != aux && comparar->frequencia == aux->frequencia) {
                Adj* aresta = CriarAresta(comparar, &ok);
                if (ok) {
                    InserirAresta(aux, aresta, &ok);
                }
            }
            comparar = comparar->next;
        }
        aux = aux->next;
    }
    return lista;
}

#pragma endregion

#pragma region Largura

/**
 * @brief Cria uma nova fila com uma antena
 * 
 * Recebe um ponteiro para a antena
 * Retorna um ponteiro para a nova fila criada
 * 
 * @param antena Ponteiro para a antena
 * @return Ponteiro para o inicio da fila criada
 */
Fila* criarFila(Antena* antena) {
    Fila* aux = (Fila*)malloc(sizeof(Fila));
    
    if (aux == NULL){
        return NULL;    
    }
    
    aux->antena = antena;
    aux->seguinte = NULL;
    return aux;
}

/**
 * @brief Adiciona uma antena à fila
 * 
 * Recebe um ponteiro para a fila e um ponteiro para a antena
 * Retorna true se adicionou com sucesso, false caso contrário
 * 
 * @param fila Ponteiro para a estrutura da fila
 * @param antena Ponteiro para a antena a adicionar
 * @return true se adicionou com sucesso, false caso contrário
 */
bool adicionarFila(Fila2* fila, Antena* antena) {
    
    Fila* aux; 
    aux = criarFila(antena);
    
    if (aux == NULL){
        return false;
    }

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = aux;
    } else {
        fila->fim->seguinte = aux;
        fila->fim = aux;
    }
    return true;
}

/**
 * @brief Remove uma antena da fila
 * 
 * Recebe um ponteiro para a fila
 * Retorna o ponteiro para a antena removida
 * 
 * @param fila Ponteiro para a estrutura da fila
 * @return Ponteiro para a antena removida, NULL se fila vazia
 */
Antena* removerFila(Fila2* fila) {
    
    if (fila->inicio == NULL){
        return NULL;
    }

    Fila* aux;
    aux = fila->inicio;

    Antena* aux2 = aux->antena;
    fila->inicio = aux->seguinte;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(aux);
    return aux2;
}

/**
 * @brief Marca todas as antenas do grafo como não visitadas
 * 
 * Recebe o ponteiro para a lista de antenas
 * Retorna true se todas as antenas ainda nao forem visitadas, false se a lista estiver vazia
 * 
 * @param inicio Ponteiro para a lista ligada de antenas
 */
bool tirarVisitado(Antena* inicio) {
    if (inicio == NULL){
        return false;
    }

    for (Antena* aux = inicio; aux != NULL; aux = aux->next) {
        aux->marcado = false;
    }
    return true;
}

/**
 * @brief Busca em largura (BFS) no grafo a partir de uma antena origem
 * 
 * @param grafo Ponteiro para o grafo
 * @param origem Ponteiro para a antena de origem
 * @return Lista ligada de antenas visitadas
 */
Antena* Largura(Antena* grafo, Antena* origem) {
    
    if (grafo == NULL || origem == NULL){
        return NULL;
    }

    tirarVisitado(grafo);

    Fila2 fila = { NULL, NULL };

    adicionarFila(&fila, origem);

    Antena* listaInicio = NULL;
    Antena* listaFim = NULL;

    while (fila.inicio != NULL) {
        Antena* aux = removerFila(&fila);

        if (!aux->marcado) {
            aux->next = NULL;
            if (listaInicio == NULL) {
                listaInicio = listaFim = aux;
            } else {
                listaFim->next = aux;
                listaFim = aux;
            }

            aux->marcado = true;

            // Percorre todos os adjacentes não visitados
            for (Adj* adjacente = aux->adj; adjacente != NULL; adjacente = adjacente->prox) {
                if (!adjacente->destino->marcado) {
                    adicionarFila(&fila, adjacente->destino);
                }
            }
        }
    }

    return listaInicio;
}

#pragma endregion

#pragma region Profundidade

/**
 * @brief Adiciona uma antena à lista de profundidade
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
    while (aux2->prox != NULL) { //percorrer ate ao ultimo
        aux2 = aux2->prox;
    }
    aux2->prox = aux;

    return profundidade;
}

/**
 * @brief Visita as antenas em profundidade
 * 
 * Recebe o ponteiro para a antena atual e a lista de profundidade
 * Retorna a lista de profundidade atualizada
 * 
 * @param atual Ponteiro para a antena atual
 * @param profundidade Ponteiro para a lista de profundidade
 * @return Ponteiro para a lista de profundidade atualizada
 */

Profundidade* visitarProfundidade(Antena* atual, Profundidade* profundidade) {
    
    if (atual == NULL || atual->marcado){
        return profundidade;
    }

    // printf("Debug: %c (%d, %d)\n", atual->frequencia, atual->x, atual->y); // debug

    atual->marcado = true;
    profundidade = adicionarAProfundidade(profundidade, atual);

    for (Adj* aux = atual->adj; aux != NULL; aux = aux->prox) {
        if (!aux->destino->marcado) {
            profundidade = visitarProfundidade(aux->destino, profundidade);
        }
    }

    return profundidade;
}

#pragma endregion

#pragma region Caminho

/**
 * @brief Adiciona uma antena ao caminho.
 * 
 * @param caminho Lista de caminhos.
 * @param antena Antena a adicionar.
 * @return Lista de caminhos atualizada.
 */

ListaCaminhos* EncontrarCaminhos(Antena* atual, Antena* fim, Caminho* caminhoAtual, ListaCaminhos* listaCaminhos) {
    
    if (atual == NULL){
        return listaCaminhos;
    }

    atual->marcado = true;

    Caminho* aux = malloc(sizeof(Caminho));
    aux->antena = atual;
    aux->prox = caminhoAtual;
    caminhoAtual = aux;

    if (atual == fim) {
        ListaCaminhos* novoCaminho = malloc(sizeof(ListaCaminhos));
        novoCaminho->caminho = caminhoAtual;
        novoCaminho->prox = listaCaminhos;
        listaCaminhos = novoCaminho;
    } else {
        for (Adj* adj = atual->adj; adj != NULL; adj = adj->prox) {
            if (!adj->destino->marcado) {
                listaCaminhos = EncontrarCaminhos(adj->destino, fim, caminhoAtual, listaCaminhos);
            }
        }
    }

    return listaCaminhos;
}

#pragma endregion

#pragma region Gravar Antena
 
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