# Projeto EDA_27956

Trabalho prático de Estruturas de Dados Avançadas (Fase 1 e 2).
Licenciatura em Engenharia de Sistemas Informáticos — IPCA.

## Objetivo

Este projeto modela uma rede de antenas a partir de uma matriz, utilizando **listas ligadas** (Fase 1) e **grafos** (Fase 2).  
Permite calcular localizações com efeito nefasto, realizar pesquisas por profundidade (DFS), largura (BFS) e todos os caminhos possíveis entre antenas de mesma frequência.

## Estrutura do Projeto

```
├── main.c            # Função principal do programa
├── grafos.c          # Algoritmos principais e pesquisa (DFS, BFS, caminhos, etc)
├── vertices.c        # Criação, inserção e listagem de antenas
├── adjacencias.c     # Criação e gestão de arestas (ligações)
├── global.h          # Definições de estruturas e cabeçalhos
├── matriz.txt        # Matriz de entrada (exemplo do enunciado)
├── Makefile          # Compilação simples
├── README.md         # Este ficheiro
```

## Como compilar e executar

1. **Compilar:**  
   ```bash
   make
   ```
   Ou manualmente:
   ```bash
   gcc main.c grafos.c vertices.c adjacencias.c -o fase2
   ```

2. **Executar:**  
   ```bash
   ./fase2
   ```

## Funcionalidades

- Leitura de matriz de antenas (`matriz.txt`)
- Representação em grafo (cada antena é um vértice, ligações entre frequências iguais)
- Cálculo de localizações com efeito nefasto
- Pesquisa em profundidade (DFS) e largura (BFS)
- Listagem de todos os caminhos possíveis entre duas antenas da mesma frequência
- Libertação da memória (sem fugas)

## Nota

- **A funcionalidade de interseções de arestas entre diferentes frequências não foi implementada**, pois, segundo o modelo utilizado, apenas existem arestas entre antenas da mesma frequência.

## Autoria

- André Braga — 27956  
- Docente: Luís Ferreira
