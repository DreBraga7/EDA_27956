/**
 * @file main.c
 * @brief Ficheiro principal do projeto. Executa as funcionalidades das Fases 1 e 2.
 * @author Andre Braga
 */

#include "global.h"

/**
 * @brief Função principal do programa.
 *
 * - Carrega o grafo a partir do ficheiro "matriz.txt"
 * - Lista as antenas existentes
 * - Deduz e lista as localizações com efeito nefasto
 * - Executa pesquisa em profundidade (DFS) e largura (BFS) a partir da primeira antena 'A'
 * - Mostra todos os caminhos possíveis entre duas antenas 'A'
 * - Liberta toda a memória alocada
 *
 * @return 0 se o programa terminar corretamente
 */
int main() {
    Vertice *grafo = carregarGrafo("matriz.txt");

    // Fase 1 - funcionalidades obrigatórias
    listarAntenas(grafo);
    Localizacao *locs = deduzirEfeitoNefasto(grafo);
    listarLocalizacoes(locs);

    // Fase 2 - funcionalidades obrigatórias
    Vertice *origem = encontrarVerticePorFreq(grafo, '0', 0); // Primeira antena A
    Vertice *destino = encontrarVerticePorFreq(grafo, '0', 1); // Segunda antena A

    printf("\nProcura em profundidade (DFS):\n");
    limparVisitados(grafo);
    dfs(origem);

    printf("\nProcura em largura (BFS):\n");
    limparVisitados(grafo);
    bfs(origem);

    printf("\nTodos os caminhos possíveis entre duas antenas 0:\n");
    limparVisitados(grafo);
    caminhosEntreAntenas(origem, destino);

    libertarGrafo(grafo);
    libertarLocalizacoes(locs);

    return 0;
}