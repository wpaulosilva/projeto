/**
 * @file dados.h
 * @author Paulo Silva (a31506@alunos.ipca.pt)
 * @brief Declaração de dados
 * @version 0.1
 * @date 2025-03-20
 * 
 * @copyright Copyright (c) 2025
 */

#include <stdbool.h>

#pragma region Estruturas

/**
 * @brief Estrutura que representa uma antena.
 * 
 * Contém a frequência e as coordenadas (x, y) da antena
 * E um ponteiro para a próxima antena da lista
 */
typedef struct antena {
    char frequencia;
    int x, y;
    bool marcado; 
    struct adj* adj;
    struct antena* next;
} Antena;

/**
 * @brief Estrutura que representa uma aresta entre antenas.
 * 
 * Contém um ponteiro para a antena de destino e um ponteiro para a próxima aresta
 */
typedef struct adj {
    Antena* destino;
    struct adj* prox;
} Adj;

/**
 * @brief Estrutura para guardar as antenas no ficheiro binário.
 */
typedef struct AntenaFile {
    char frequencia;
    int x, y;
} AntenaFile;

/**
 * @brief Estrutura para guardar as arestas no ficheiro binário.
 * 
 * Contém as coordenadas (x, y) da antena de destino
 */
typedef struct {
    int x; 
    int y;
} ArestaFile;

/**
 * @brief Estrutura para guardar as antenas na fila.
 * 
 * Contém um ponteiro para a antena e um ponteiro para a próxima antena na fila
 */
typedef struct Fila {
    Antena* antena;
    struct Fila* seguinte;
} Fila;

/**
 * @brief Estrutura para guardar a fila de antenas.
 * 
 * Contém ponteiros para o início e o fim da fila
 */
typedef struct Fila2 {
    Fila* inicio;
    Fila* fim;
} Fila2;

/**
 * @brief Estrutura para guardar os caminhos encontrados na busca profundidade.
 * 
 * Contém um ponteiro para a antena e um ponteiro para o próximo caminho
 */	
typedef struct Profundidade {
    Antena* antena;
    struct Profundidade* prox;
} Profundidade;

/**
 * @brief Estrutura para guardar os caminhos encontrados na busca profundidade.
 * 
 * Contém um ponteiro para a antena e um ponteiro para o próximo caminho
 */
typedef struct Caminho {
    Antena* antena;
    struct Caminho* prox;
} Caminho;

/**
 * @brief Estrutura para guardar os caminhos encontrados na busca profundidade.
 * 
 * Contém um ponteiro para o caminho completo (lista de antenas) e um ponteiro para o próximo caminho
 */
typedef struct ListaCaminhos {
    Caminho* caminho;
    struct ListaCaminhos* prox;
} ListaCaminhos;

#pragma endregion

#pragma region Declarações
/**
 * @brief Declaração da função para ler do ficheiro, criar, procurar, inserir e remover antenas
 */
Antena* LerAntenas(char* nome_ficheiro, Antena* lista);
Antena* CriaAntena(char frequencia, int x, int y);
Antena* ProcuraAntena(Antena* lista, int x, int y);
Antena* InserirAntena(Antena* lista, char frequencia, int x, int y);
Antena* RemoveAntena(Antena* lista, int x, int y);

/**
 * @brief Declaração da função para calcular o efeito nefasto
 */
Antena* CalculaNefasto(Antena* lista);

/**
 * @brief Declaração da função para criar arestas
 */
Adj* CriarAresta(Antena* destino, bool* validar);

/**
 * @brief Declaração da função para inserir arestas
 * 
 * Recebe o ponteiro para a antena de início, a aresta a inserir e um ponteiro para validação
 * Retorna a lista de adjacências atualizada
 */
Adj* InserirAresta(Antena* inicio, Adj* aresta, bool* validar);

/**
 * @brief Declaração da função para criar o grafo
 * 
 * Recebe o ponteiro para a lista de antenas
 * Retorna a lista de antenas com as arestas criadas
 */
Antena* CriarGrafo(Antena* lista);

/**
 * @brief Meter as antenas como nao visitadas
 * 
 * @param inicio 
 * @return true 
 * @return false 
 */
bool tirarVisitado(Antena* inicio);

/**
 * @brief Guardar a ordem das antenas visitadas
 * 
 * @param grafo 
 * @param origem 
 * @return Antena* 
 */
Antena* Largura(Antena* grafo, Antena* origem);

/**
 * @brief Realizar a profundidade a partide uma certa antena
 * 
 * @param atual 
 * @param profundidade 
 * @return Profundidade* 
 */
Profundidade* visitarProfundidade(Antena* atual, Profundidade* profundidade);

/**
 * @brief Adicionar uma antena a lista:
 * 
 * @param profundidade 
 * @param antena 
 * @return Profundidade* 
 */
Profundidade* adicionarAProfundidade(Profundidade* profundidade, Antena* antena);

/**
 * @brief Declaração da função para guardar no ficheiro binário
 * @return Verdadeiro se a gravação for feita
 */
bool GravaAntenasBinario(char* nome_ficheiro, Antena* lista);

#pragma endregion