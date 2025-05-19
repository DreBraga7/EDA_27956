/**
 * @file global.h
 * @brief Estruturas principais e assinaturas das funções do projeto EDA.
 * @author Andre Braga
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Vertice
 * @brief Representa uma antena no grafo.
 *
 * Guarda frequência, coordenadas, flag de visita, lista de adjacências (arestas) e ponteiro para o próximo vértice.
 */
typedef struct Vertice {
    char freq;
    int x;
    int y;
    int visitado;
    struct Aresta *adjacentes;
    struct Vertice *next;
} Vertice;

/**
 * @struct Aresta
 * @brief Representa uma ligação (aresta) entre dois vértices.
 *
 * Guarda ponteiro para o vértice de destino e para a próxima aresta da lista.
 */
typedef struct Aresta {
    struct Vertice *destino;
    struct Aresta *next;
} Aresta;

/**
 * @struct Localizacao
 * @brief Representa uma localização (linha, coluna) afetada pelo efeito nefasto.
 */
typedef struct Localizacao {
    int x;
    int y;
    struct Localizacao *next;
} Localizacao;


/**
 * Grupo: Funções de vértices
 * - Criar, inserir e listar antenas na lista ligada principal do grafo.
 */
Vertice* criarVertice(char freq, int x, int y);
void inserirVertice(Vertice **grafo, char freq, int x, int y);
void listarAntenas(Vertice *grafo);

/**
 * Grupo: Funções de adjacências
 * - Criar e gerir as ligações (arestas) entre antenas do grafo.
 */
void ligarVertices(Vertice *grafo);

/**
 * Grupo: Funções do grafo e principais
 * - Carregar, pesquisar, libertar e manipular o grafo de antenas.
 */
Vertice* carregarGrafo(const char *nomeFicheiro);
void limparVisitados(Vertice *grafo);
void dfs(Vertice *origem);
void bfs(Vertice *origem);
void caminhosEntreAntenas(Vertice *origem, Vertice *destino);
Vertice* encontrarVerticePorFreq(Vertice *grafo, char freq, int n);
void libertarGrafo(Vertice *grafo);

/**
 * Grupo: Funções para localizações (efeito nefasto)
 * - Deduzir, inserir, listar e libertar localizações afetadas pelo efeito nefasto.
 */
Localizacao* deduzirEfeitoNefasto(Vertice *grafo);
void inserirLocalizacao(Localizacao **head, int x, int y);
void listarLocalizacoes(Localizacao *locs);
void libertarLocalizacoes(Localizacao *locs);

#endif 