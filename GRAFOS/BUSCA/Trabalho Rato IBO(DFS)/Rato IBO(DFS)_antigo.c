//Versão antiga porém funcional

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRANCO 0
#define CINZA 1

typedef struct Vertice{
    struct Vertice **vet_vizinhos;
    int num_vizinhos;
    int cor;
    char id[8];         //Nome
    int dist;           //Distancia
} No, *Pont;

typedef struct Guarda{
    Pont vertice;           //Aponta para o vertices
    struct Guarda *prox;    //Proximo item da lista
}Guarda, *PONT_V;

typedef struct Lista{
    struct Guarda *inicio;
    struct Guarda *fim;
}*Lista;

//Função para criar um novo vertice
Pont criar_vertice(Lista lista, char *nome){
    PONT_V aux = lista->inicio;
    Pont vertice = NULL;

    while(1){
        if(aux == NULL){                        //Se (aux == NULL), cria um novo vertice e adiciona
            vertice = malloc(sizeof(No));       
            vertice->cor = BRANCO;              
            strcpy(vertice->id, nome);         
            vertice->vet_vizinhos = malloc(sizeof(No));
            vertice->num_vizinhos = 0;
            
            PONT_V novo_vetice = malloc(sizeof(Guarda));
            novo_vetice->vertice = vertice;
            novo_vetice->prox = lista->inicio;
            lista->inicio = novo_vetice; 

            break;
        }else if(strcmp(aux->vertice->id, nome) == 0){
            vertice = aux->vertice;
            break;
        }
        aux = aux->prox;
    }
    return vertice;   
}

//Função para conectar os vertices (v1 = vertice1)
void conectar_vertices(Pont v1, Pont v2){
    v1->num_vizinhos += 1;
    v1->vet_vizinhos = realloc(v1->vet_vizinhos,sizeof(No) * v1->num_vizinhos);
    v1->vet_vizinhos[v1->num_vizinhos-1] = v2;
}

//Função para inicializar o grafo
Pont inicializar_grafo(Lista lista){
    int num_vertices, num_arestas;

    scanf("%d%d", &num_vertices, &num_arestas);

    char nome_v1[8];
    char nome_v2[8];
    Pont v1 = NULL;
    Pont v2 = NULL;

    for(int i=0; i < num_arestas; i++){
        scanf("%s", nome_v1);
        fflush(stdin);

        scanf("%s", nome_v2);
        fflush(stdin);
        
        v1 = criar_vertice(lista, nome_v1);
        v2 = criar_vertice(lista, nome_v2);
        
        //conectar vertices
        conectar_vertices(v1, v2);
        conectar_vertices(v2, v1);
    }
    
    PONT_V aux = lista->inicio;
    while(strcmp(aux->vertice->id, "Entrada") != 0){
        aux = aux->prox;
        if(aux == NULL){
            printf("Falha ao encontrar 'Entrada'!");
            exit(1);
        }
    }
    aux->vertice->cor = CINZA;
    
    return aux->vertice;
}

//Função para adicionar a pilha
void add_pilha(Lista pilha, Pont item, int posicao){
    PONT_V novo = malloc(sizeof(Guarda));

    novo->vertice = item;
    novo->prox = NULL;
    item->cor = CINZA;
    item->dist = posicao;

    if(pilha->inicio==NULL){
        pilha->inicio = novo;
        pilha->fim = novo;
    }else{
        pilha->fim->prox = novo;
        pilha->fim = novo;
    }
}

//Função para excluir a fila atual
void excluir_fila(Lista lista){
    PONT_V aux = lista->inicio;

    while(aux!=NULL){
        lista->inicio = aux->prox;
        free(aux);
        aux = lista->inicio;
    }
    lista->inicio = NULL;
}

//Função para encontrar o caminho até o destino desejado
Pont encontrar(Lista fila, char destino[8]){
    Pont posicao;

    while(fila->inicio != NULL){
        posicao = fila->inicio->vertice;

        for(int i=0;i<posicao->num_vizinhos;i++){
            if(posicao->vet_vizinhos[i]->cor==BRANCO){
                add_pilha(fila, posicao->vet_vizinhos[i], posicao->dist + 1);
            }
        }

        if(strcmp(posicao->id, destino) == 0){   //Encontrou o destino
            excluir_fila(fila);
            return(posicao);    //Retorna ponteiro da posição atual
        }

        PONT_V aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
    }
    return NULL;
}

//Função para reiniciar a lista
void reiniciar(Lista lista){
    PONT_V aux = lista->inicio;
    while(aux != NULL){
        aux->vertice->cor = BRANCO;
        aux = aux->prox;
    }
}

int main(){
    Lista lista = malloc(sizeof(struct Lista));
    lista->inicio = NULL;

    Pont entrada = inicializar_grafo(lista);     //Inicializa o grafo

    Lista aux = malloc(sizeof(struct Lista));
    aux->inicio = NULL;

    add_pilha(aux, entrada, 0);
    char destino[8] = {"*"};
    
    Pont queijo = encontrar(aux, destino);      //Começa a procurar pelo queijo
    if(queijo == NULL){
        printf("Falha ao encontrar '*'!");
        exit(1);
    }
    int distancia = queijo->dist;       //Distancia = distancia da entrada até o queijo
    reiniciar(lista);                   //Reinicia a lista
    add_pilha(aux, queijo, 0);
    
    strcpy(destino, "Saida");
    Pont saida = encontrar(aux, destino);       //Começa a procurar pela saida
    if(saida == NULL){
        printf("Falha ao encontrar 'Saida'!");
        exit(1);
    }

    distancia += saida->dist;                   //Distancia = distancia + distancia do queijo até a saida
    printf("\nDistancia percorrida no grafo: %d\n", distancia);

    return 0;
}