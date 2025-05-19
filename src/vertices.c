/**
 * @file vertices.c
 * @brief Implementação das funções relacionadas com vértices (antenas) do grafo.
 *
 * Contém funções para criar, inserir e listar antenas, assim como para estabelecer as adjacências
 * entre vértices de mesma frequência.
 * 
 * @author Andre Braga
 */

#include "global.h"

/**
 * @brief Cria um novo vértice (antena) com os dados fornecidos.
 *
 * Reserva memória, preenche os campos da antena e inicializa os ponteiros para NULL.
 *
 * @param freq Frequência da antena (ex: 'A', '0')
 * @param x Linha onde a antena se encontra
 * @param y Coluna onde a antena se encontra
 * @return Ponteiro para o novo vértice criado
 */
Vertice* criarVertice(char freq, int x, int y) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->freq = freq;
    novo->x = x;
    novo->y = y;
    novo->visitado = 0;
    novo->adjacentes = NULL;
    novo->next = NULL;
    return novo;
}

/**
 * @brief Insere um novo vértice (antena) na lista ligada de vértices do grafo.
 *
 * O novo vértice é adicionado à cabeça da lista ligada.
 *
 * @param grafo Ponteiro para o início da lista ligada de vértices
 * @param freq Frequência da antena
 * @param x Linha da antena
 * @param y Coluna da antena
 */
void inserirVertice(Vertice **grafo, char freq, int x, int y) {
    Vertice *novo = criarVertice(freq, x, y);
    novo->next = *grafo;
    *grafo = novo;
}

/**
 * @brief Lista todas as antenas presentes no grafo.
 *
 * Percorre a lista ligada de vértices e imprime as coordenadas e frequência de cada antena.
 *
 * @param grafo Ponteiro para o início da lista ligada de vértices
 */
void listarAntenas(Vertice *grafo) {
    printf("Antenas:\n");
    for (Vertice *v = grafo; v; v = v->next)
        printf("(%d, %d) [%c]\n", v->x, v->y, v->freq);
}

/**
 * @brief Liga os vértices de mesma frequência criando as listas de adjacências.
 *
 * Para cada par de vértices diferentes, se tiverem a mesma frequência, cria uma aresta entre eles
 * e adiciona à lista de adjacências do vértice de origem.
 *
 * @param grafo Ponteiro para o início da lista ligada de vértices
 */
void ligarVertices(Vertice *grafo) {
    for (Vertice *v1 = grafo; v1; v1 = v1->next) {
        for (Vertice *v2 = grafo; v2; v2 = v2->next) {
            if (v1 != v2 && v1->freq == v2->freq) {
                Aresta *a = malloc(sizeof(Aresta));
                a->destino = v2;
                a->next = v1->adjacentes;
                v1->adjacentes = a;
            }
        }
    }
}