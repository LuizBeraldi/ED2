#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **matriz;
    int num_vertices;
    int num_arestas;
} Grafo;

// Função para inicializar um grafo
Grafo *inicializarGrafo(int num_vertices) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    grafo->num_vertices = num_vertices;
    grafo->num_arestas = 0;

    grafo->matriz = (int **)malloc(num_vertices * sizeof(int *));
    if (grafo->matriz == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    for (int i = 0; i < num_vertices; i++) {
        grafo->matriz[i] = (int *)malloc(num_vertices * sizeof(int));
        if (grafo->matriz[i] == NULL) {
            printf("Erro de alocacao de memoria\n");
            exit(1);
        }
        for (int j = 0; j < num_vertices; j++) {
            grafo->matriz[i][j] = 0; // Inicializa todas as arestas com peso 0
        }
    }

    return grafo;
}

// Função para imprimir um grafo
void imprimirGrafo(Grafo *grafo) {
    printf("\nMatriz de Adjacencia:\n");

    printf("    ");
    for(int j = 0; j < grafo->num_vertices; j++) {
        printf("v%d ", j + 1);
    }
    printf("\n    ---------------\n");

    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("v%d |", i + 1);
        for (int j = 0; j < grafo->num_vertices; j++) {
            printf("%2d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para liberar a memória de um grafo
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}

// Função para inserir uma aresta
void inserirAresta(Grafo *grafo, int vertice_origem, int vertice_destino, int peso) {
    if(vertice_origem < 1 || vertice_origem > grafo->num_vertices || vertice_destino < 1 || vertice_destino > grafo->num_vertices){
        printf("\nERRO, valor invalido!\n");
        exit(1);
    }
    grafo->matriz[vertice_origem-1][vertice_destino-1] = peso;
    grafo->num_arestas++;
}

// Função para verificar se uma aresta existe
void existeAresta(Grafo *grafo, int vertice_origem, int vertice_destino) {
    if(vertice_origem < 1 || vertice_origem > grafo->num_vertices || vertice_destino < 1 || vertice_destino > grafo->num_vertices){
        printf("\nERRO, valor invalido!\n");
        exit(1);
    }
    printf("\nExiste a aresta entre [%d] e [%d]: ", vertice_origem, vertice_destino);
    if(grafo->matriz[vertice_origem-1][vertice_destino-1] != 0){
        printf("Sim");
    }else{
        printf("Nao");
    }
}

// Função para retornar o número de vértices
void numeroVertices(Grafo *grafo) {
    printf("\nNumero de vertices: %d\n", grafo->num_vertices);
}

// Função para retornar o número de arestas
void numeroArestas(Grafo *grafo) {
    printf("Numero de arestas: %d\n", grafo->num_arestas);
}

void possuiVizinhos(Grafo *grafo, int vertice){
    if(vertice < 1 || vertice > grafo->num_vertices){
        printf("\nERRO, valor invalido!\n");
        exit(1);
    }

    printf("O vertice [%d] possui vizinhos? ", vertice);
    if(vertice == 5){
        if(grafo->matriz[vertice-1][vertice-2] != 0){
            printf("Sim\n");
            return;
        }
        if(grafo->matriz[vertice-2][vertice-1] != 0){
            printf("Sim\n");
            return;
        }
    }else if(vertice == 1){
        if(grafo->matriz[vertice-1][vertice] != 0){
            printf("Sim\n");
            return;
        }
        if(grafo->matriz[vertice][vertice-1] != 0){
            printf("Sim\n");
            return;
        }
    }else{
        if(grafo->matriz[vertice-1][vertice-2] != 0){
            printf("Sim\n");
            return;
        }
        if(grafo->matriz[vertice-2][vertice-1] != 0){
            printf("Sim\n");
            return;
        }
        if(grafo->matriz[vertice-1][vertice] != 0){
            printf("Sim\n");
            return;
        }
        if(grafo->matriz[vertice][vertice-1] != 0){
            printf("Sim\n");
            return;
        }
    }
    printf("Nao\n");
}

// Função para retornar o grau de um vértice
void grauVertice(Grafo *grafo, int vertice) {
    if(vertice < 0 || vertice > grafo->num_vertices){
        printf("\nERRO, valor invalido!\n");
        exit(1);
    }

    int grau = 0;
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->matriz[vertice-1][i] != 0) {
            grau++;
            if((vertice-1) == i){
                grau++;
            }
        }
    }
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (grafo->matriz[i][vertice-1] != 0) {
            if((vertice-1) == i){
                grau--;
            }
            grau++;
        }
    }

    printf("\nGrau do vertice [%d]: %d\n", vertice, grau);
}

// Função para remover uma aresta
void removerAresta(Grafo *grafo, int vertice_origem, int vertice_destino) {
    if(vertice_origem < 1 || vertice_origem > grafo->num_vertices || vertice_destino < 1 || vertice_destino > grafo->num_vertices){
        printf("\nERRO, valor invalido!\n");
        exit(1);
    }

    if(grafo->matriz[vertice_origem-1][vertice_destino-1] == 0){
        printf("\nA aresta nao existe!\n");
    }else{
        grafo->matriz[vertice_origem-1][vertice_destino-1] = 0;
        grafo->num_arestas--;
        printf("\nAresta entre [%d] e [%d] foi excluida com sucesso!\n", vertice_origem, vertice_destino); 

        imprimirGrafo(grafo); // Imprime o grafo
        numeroVertices(grafo); // Imprime o número de vertices
        numeroArestas(grafo); // Imprime o número de arestas
    }
}

int main() {
    Grafo *grafo = inicializarGrafo(5); // Inicializa o grafo

    inserirAresta(grafo, 1, 1, 1); // (grafo, vertice de origem, vertice de destino, peso)
    inserirAresta(grafo, 2, 2, 1);
    inserirAresta(grafo, 3, 3, 1);
    inserirAresta(grafo, 4, 4, 1);
    inserirAresta(grafo, 4, 3, 1);
    inserirAresta(grafo, 4, 5, 1);

    imprimirGrafo(grafo); // Imprime o grafo

    numeroVertices(grafo); // Imprime o número de vertices
    numeroArestas(grafo); // Imprime o número de arestas

    removerAresta(grafo, 1, 1); // Exclui a aresta desejada

    existeAresta(grafo, 1, 2); // Imprime se existe uma aresta entre um vértice incial e um vértice fina
    grauVertice(grafo, 1); // Imprime o grau do vértice
    possuiVizinhos(grafo, 5); // Verifica se o vértice possui vizinhos

    /* Posições verificadas para achar vizinhos
       v = vertice

                |(v-1,v)|
        |(v,v-1)|   v   |(v,v+1)|
                |(v+1,v)|
    */

    liberarGrafo(grafo); // Da free no grafo

    return 0;
}