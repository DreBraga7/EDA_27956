/**
 * @file grafos.c
 * @brief Implementação das funções principais do grafo e algoritmos de pesquisa.
 *
 * Contém funções para carregar o grafo a partir da matriz, executar DFS e BFS, encontrar caminhos,
 * gerir localizações com efeito nefasto e libertar a memória.
 * 
 * @author Andre Braga
 */

#include "global.h"

/**
 * @brief Carrega o grafo a partir do ficheiro matriz.txt.
 *
 * Lê a matriz do ficheiro linha a linha e cria um vértice para cada antena (carácter diferente de '.' ou ' ').
 * Liga todas as antenas da mesma frequência através da função ligarVertices.
 *
 * @param nomeFicheiro Nome do ficheiro a ler (ex: "matriz.txt").
 * @return Ponteiro para o grafo criado.
 */
Vertice* carregarGrafo(const char *nomeFicheiro) {
    FILE *f = fopen(nomeFicheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    Vertice *grafo = NULL;
    char linha[256];
    int row = 0;

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;
        for (int col = 0; linha[col]; col++) {
            char c = linha[col];
            if (c != '.' && c != ' ')
                inserirVertice(&grafo, c, row, col);
        }
        row++;
    }
    fclose(f);
    ligarVertices(grafo);
    return grafo;
}

/**
 * @brief Limpa o campo 'visitado' de todos os vértices do grafo.
 * @param grafo Ponteiro para o início da lista de vértices.
 */
void limparVisitados(Vertice *grafo) {
    for (; grafo; grafo = grafo->next){
        grafo->visitado = 0;
    }
}

/**
 * @brief Procura em profundidade (DFS) a partir do vértice de origem.
 *
 * Visita todos os vértices ligados recursivamente, marcando cada um como visitado e imprimindo no ecrã.
 *
 * @param origem Ponteiro para o vértice de início.
 */
void dfs(Vertice *origem) {
    if (!origem || origem->visitado) return;
    origem->visitado = 1;
    printf("DFS Visitado: (%d, %d) [%c]\n", origem->x, origem->y, origem->freq);
    for (Aresta *a = origem->adjacentes; a; a = a->next){
        dfs(a->destino);
    }
}

/**
 * @brief Procura em largura (BFS) a partir do vértice de origem.
 *
 * Utiliza uma fila para visitar todos os vértices ligados por níveis, marcando cada um como visitado e imprimindo.
 *
 * @param origem Ponteiro para o vértice de início.
 */
void bfs(Vertice *origem) {
    Vertice *fila[100];
    int inicio = 0, fim = 0;
    origem->visitado = 1;
    fila[fim++] = origem;
    while (inicio < fim) {
        Vertice *v = fila[inicio++];
        printf("BFS Visitado: (%d, %d) [%c]\n", v->x, v->y, v->freq);
        for (Aresta *a = v->adjacentes; a; a = a->next) {
            if (!a->destino->visitado) {
                a->destino->visitado = 1;
                fila[fim++] = a->destino;
            }
        }
    }
}

/**
 * @brief Função auxiliar recursiva para encontrar todos os caminhos entre duas antenas.
 *
 * @param atual Vértice atual no caminho.
 * @param destino Vértice de destino.
 * @param caminho Array de inteiros com o percurso atual.
 * @param passo Posição atual no array.
 */
void caminhosRec(Vertice *atual, Vertice *destino, int caminho[], int passo) {
    if (!atual || atual->visitado) return;
    atual->visitado = 1;
    caminho[passo++] = atual->x * 100 + atual->y;
    if (atual == destino) {
        printf("Caminho encontrado: ");
        for (int i = 0; i < passo; i++)
            printf("(%d, %d) ", caminho[i] / 100, caminho[i] % 100);
        printf("\n");
    } else {
        for (Aresta *a = atual->adjacentes; a; a = a->next)
            caminhosRec(a->destino, destino, caminho, passo);
    }
    atual->visitado = 0;
}

/**
 * @brief Encontra e imprime todos os caminhos possíveis entre duas antenas.
 *
 * @param origem Ponteiro para o vértice de origem.
 * @param destino Ponteiro para o vértice destino.
 */
void caminhosEntreAntenas(Vertice *origem, Vertice *destino) {
    int caminho[100];
    caminhosRec(origem, destino, caminho, 0);
}

/**
 * @brief Procura o n-ésimo vértice de determinada frequência.
 *
 * @param grafo Ponteiro para a lista ligada de vértices.
 * @param freq Frequência desejada.
 * @param n Índice da ocorrência (0 = primeira).
 * @return Ponteiro para o vértice encontrado ou NULL.
 */
Vertice* encontrarVerticePorFreq(Vertice *grafo, char freq, int n) {
    int count = 0;
    for (; grafo; grafo = grafo->next)
        if (grafo->freq == freq && count++ == n)
            return grafo;
    return NULL;
}

/**
 * @brief Liberta toda a memória ocupada pelo grafo (vértices e arestas).
 * @param grafo Ponteiro para o início da lista de vértices.
 */
void libertarGrafo(Vertice *grafo) {
    while (grafo) {
        Aresta *a = grafo->adjacentes;
        while (a) {
            Aresta *tempA = a;
            a = a->next;
            free(tempA);
        }
        Vertice *tempV = grafo;
        grafo = grafo->next;
        free(tempV);
    }
}

/**
 * @brief Deduz as localizações com efeito nefasto com base nas antenas do grafo.
 *
 * Para cada par de antenas com a mesma frequência, calcula as localizações com efeito nefasto usando as fórmulas L1 = 2*A - B e L2 = 2*B - A.
 *
 * @param grafo Ponteiro para a lista ligada de vértices.
 * @return Lista ligada de localizações com efeito nefasto.
 */
Localizacao* deduzirEfeitoNefasto(Vertice *grafo) {
    Localizacao *locs = NULL;
    for (Vertice *v1 = grafo; v1; v1 = v1->next) {
        for (Vertice *v2 = v1->next; v2; v2 = v2->next) {
            if (v1->freq == v2->freq) {
                int x1 = 2 * v1->x - v2->x;
                int y1 = 2 * v1->y - v2->y;
                int x2 = 2 * v2->x - v1->x;
                int y2 = 2 * v2->y - v1->y;
                inserirLocalizacao(&locs, x1, y1);
                inserirLocalizacao(&locs, x2, y2);
            }
        }
    }
    return locs;
}

/**
 * @brief Insere uma localização (linha, coluna) na lista ligada de localizações.
 *
 * @param head Ponteiro para o início da lista ligada.
 * @param x Linha da localização.
 * @param y Coluna da localização.
 */
void inserirLocalizacao(Localizacao **head, int x, int y) {
    Localizacao *nova = malloc(sizeof(Localizacao));
    nova->x = x;
    nova->y = y;
    nova->next = *head;
    *head = nova;
}

/**
 * @brief Lista todas as localizações com efeito nefasto.
 * @param locs Ponteiro para a lista ligada de localizações.
 */
void listarLocalizacoes(Localizacao *locs) {
    printf("Localizações com efeito nefasto:\n");
    for (Localizacao *l = locs; l; l = l->next)
        printf("(%d, %d)\n", l->x, l->y);
}

/**
 * @brief Liberta toda a memória ocupada pela lista de localizações.
 * @param locs Ponteiro para o início da lista ligada de localizações.
 */
void libertarLocalizacoes(Localizacao *locs) {
    while (locs) {
        Localizacao *temp = locs;
        locs = locs->next;
        free(temp);
    }
}