#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef int TIPOPESO;

typedef struct adj {
    int vertice;
    TIPOPESO peso;
    struct adj* prox;
} Adjacencia;

typedef struct {
    Adjacencia *cab;
} Vertice;

typedef struct {
    int vertices;
    int arestas;
    Vertice *adj;
} Grafo;

void inicializarBF(Grafo *grafo, int *d, int *p, int s) {
    for(int v = 0; v < grafo->vertices; v++) {
        d[v] = INT_MAX/2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxar(Grafo* grafo, int *d, int *p, int u, int v) {
    Adjacencia *adj = grafo->adj[u].cab;
    while(adj && adj->vertice != v) 
        adj = adj->prox;

    if(adj) {
        if(d[v] > d[u] + adj->peso) {
            d[v] = d[u] + adj->peso;
            p[v] = u;
        }
    }
}

int *bellmanFord(Grafo *grafo, int s) {
    int *d = malloc(grafo->vertices * sizeof(int));
    int p[grafo->vertices];
    inicializarBF(grafo, d, p, s);

    for(int i = 1; i <= grafo->vertices - 1; i++) {
        for(int u = 0; u < grafo->vertices; u++) {
            Adjacencia *adj = grafo->adj[u].cab;
            while(adj) {
                relaxar(grafo, d, p, u, adj->vertice);
                adj = adj->prox;
            }
        }
    }

    for(int u = 0; u < grafo->vertices; u++) {
        Adjacencia *adj = grafo->adj[u].cab;
        while(adj) {
            if(d[adj->vertice] > d[u] + adj->peso) { 
                free(d);
                return NULL;
            }
            adj = adj->prox;
        }
    }

    return d;
}