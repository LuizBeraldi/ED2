#include <stdio.h>
#define MAX 100

typedef struct{
    int u, v, peso;
}Aresta;

int cmp(const void *a, const void *b){
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso;
}

void kruskal(Aresta E[], Aresta A[], int nAresta, int nVertice){
    int C[MAX];
    int cont = 0, k;

    qsort(E, nAresta, sizeof(Aresta), cmp);

    for(int i=0; i < nVertice; i++){
        C[i] = i;
    }

    for(int i=0; i < nAresta; i++){
        if(C[E[i].u] != C[E[i].v]){
            A[cont++] = E[i];
            k = C[E[i].u];
            for(int j=0; j < nVertice; j++){
                if(C[j] == k){
                    C[j] = C[E[i].v];
                }
            }
        }
    }
}