#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int pid;
    int prioridade;
    int tempoEspera;
} Heap, *Processo;

Heap addProcesso(int *pid, int prioridade, int tempoEspera){
    Heap processo;
    processo.pid = *pid;
    processo.prioridade = prioridade;
    processo.tempoEspera = tempoEspera;
    (*pid)++;

    return processo;
}

int heapVazio(int n) {
    return (n <= 0) ? 1 : 0;        // retorna 1 se o heap estiver vazio, caso contrário retorna 0
}

int pai(int i){
    return i/2;
}

int esq(int i){
    return (i*2);
}

int dir(int i){
    return (i*2+1);
}

void trocar(Processo i, Processo j){
    Heap aux = *i;
    *i = *j;
    *j = aux;
}

void subirMax(Processo heap, int i){
    int j = pai(i);

    if(j >= 1){
        if(heap[i].prioridade > heap[j].prioridade){
            //faz a subida
            trocar(&heap[i], &heap[j]);

            subirMax(heap, j);
        }
    }
}

void subirMin(Processo heap, int i){
    int j = pai(i);

    if(j >= 1){
        if(heap[i].tempoEspera < heap[j].tempoEspera){
            //faz a subida
            trocar(&heap[i],&heap[j]);

            subirMin(heap, j);
        }
    }
}

void descerMax(Processo heap, int i, int n){
    // descobre quem é o maior filho de i
    int e = esq(i);
    int d = dir(i);
    int maior = i;

    if(e <= n && heap[e].prioridade > heap[i].prioridade){
        maior = e;
    }

    if(d <= n && heap[d].prioridade > heap[maior].prioridade){
        maior = d;
    }

    if(maior != i){
        // faz a descida trocando com o maior filho
        trocar(&heap[i],&heap[maior]);

        descerMax(heap, maior, n);
    }
}

void descerMin(Processo heap, int i, int n){
    // descobre quem é o maior filho de i
    int e = esq(i);
    int d = dir(i);
    int menor = i;

    if(e <= n && heap[e].tempoEspera < heap[i].tempoEspera){
        menor = e;
    }

    if(d <= n && heap[d].tempoEspera < heap[menor].tempoEspera){
        menor = d;
    }

    if(menor != i){
        // faz a descida trocando com o maior filho
        trocar(&heap[i],&heap[menor]);

        descerMin(heap, menor, n);
    }
}

void constroi_heap_maximo(Processo heap, int n){
    int j = (n/2);

    for(int i = j; i >= 1; i--){
        descerMax(heap, i, n);
    }
}

void constroi_heap_minimo(Processo heap, int n){
    int j = (n/2);

    for(int i = j; i >= 1; i--){
        descerMin(heap, i, n);
    }
}

void inserirProcessoMax(Processo* heap, Heap processo, int* tam){
    // aumenta o tamanho do vetor
    *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tam + 2));
    (*tam)++;
    (*heap)[*tam] = processo;

    subirMax(*heap, *tam);
}

void inserirProcessoMin(Processo* heap, Heap processo, int* tam){
    // aumenta o tamanho do vetor
    *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tam + 2));
    (*tam)++;
    (*heap)[*tam] = processo;

    subirMin(*heap, *tam);
}

void imprimirProcessoMax(Processo heapMax, int n){
    printf("\n\tHEAP MAX (Prioridade)");
    printf("\nPrioridade:\n");
    for(int i = 1; i <= n; i++){
        printf("%d ", heapMax[i].prioridade);
    }

    printf("\nTempo de espera:\n");
    for(int i = 1; i <= n; i++){
        printf("%d ", heapMax[i].tempoEspera);
    }
    printf("\n");
}

void imprimirProcessoMin(Processo heapMin, int n){
    printf("\n\tHEAP MIN (Tempo de espera)");
    printf("\nPrioridade:\n");
    for(int i = 1; i <= n; i++){
        printf("%d ", heapMin[i].prioridade);
    }

    printf("\nTempo de espera:\n");
    for(int i = 1; i <= n; i++){
        printf("%d ", heapMin[i].tempoEspera);
    }
    printf("\n");
}

void removerProcessoTopoMax(Processo *heap, int *tam){
    if(!heapVazio(*tam)) {
        (*heap)[1] = (*heap)[*tam];
        (*tam)--;
        // diminui tamanho do vetor
        *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tam + 1));

        descerMax(*heap, 1, *tam);
    }
}

void removerProcessoTopoMin(Processo *heap, int *tam){
    if(!heapVazio(*tam)) {
        (*heap)[1] = (*heap)[*tam];
        (*tam)--;
        // diminui tamanho do vetor
        *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tam + 1));

        descerMin(*heap, 1, *tam);
    }
}

int main(){
    int tamMax = 0, tamMin = 0, id = 1;

    Heap processo;
    Processo heapMax = (Processo)malloc(sizeof(Heap));
    Processo heapMin = (Processo)malloc(sizeof(Heap));

    processo = addProcesso(&id, 50, 1);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    processo = addProcesso(&id, 30, 9);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    processo = addProcesso(&id, 90, 8);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    processo = addProcesso(&id, 10, 2);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    processo = addProcesso(&id, 20, 8);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    processo = addProcesso(&id, 70, 4);
    inserirProcessoMax(&heapMax, processo, &tamMax);
    inserirProcessoMin(&heapMin, processo, &tamMin);

    removerProcessoTopoMax(&heapMax, &tamMax);
    removerProcessoTopoMin(&heapMin, &tamMin);

    imprimirProcessoMax(heapMax, tamMax);
    imprimirProcessoMin(heapMin, tamMax);

    return 0;
}