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
typedef struct Antena {
    char frequencia;
    int x, y;
    struct Antena* next;
} Antena;

/**
 * @brief Estrutura para guardar as antenas no ficheiro binário.
 */
typedef struct {
    char frequencia;
    int x, y;
} AntenaFile;
#pragma endregion

#pragma region Declarações
/**
 * @brief Declaração da função para ler do ficheiro, criar, procurar, inserire listar as antenas
 */
Antena* LerAntenas(const char* nome_ficheiro, Antena* lista);
Antena* CriaAntena(char frequencia, int x, int y);
Antena* ProcuraAntena(Antena* lista, int x, int y);
Antena* InsereOrdenado(Antena* lista, char frequencia, int x, int y);
Antena* ListaAntenas(Antena* lista, int* num_antenas);
Antena* RemoveAntena(Antena* lista, int x, int y);

/**
 * @brief Declaração da função para calcular o efeito nefasto
 */
Antena* CalculaNefasto(Antena* lista);

/**
 * @brief Declaração da função para guardar no ficheiro binário
 * @return Verdadeiro se a gravação for feita
 */
bool GravaAntenasBinario(const char* nome_ficheiro, Antena* lista);

/**
 * @brief Declaração da função ler o ficheiro binário
 */
Antena* LerAntenasBinario(const char* nome_ficheiro);

#pragma endregion