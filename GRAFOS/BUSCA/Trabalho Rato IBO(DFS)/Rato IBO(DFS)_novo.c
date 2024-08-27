//Versão final

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define branco 0
#define cinza 1
#define preto 2

typedef struct Vertice{
    struct Vizinho *lista_vizinhos;     //Ponteiro para a lista de vizinhos
    int cor;            //Cor do vertice
    char id[8];         //Nome
    int dist;           //Distancia
} No, *Pont;

typedef struct Vizinho{
    Pont vertice;           //Ponteiro para o vertice vizinho
    struct Vizinho *prox;   //Ponteiro para o proximo vizinho
} Vizinho;

typedef struct Guarda{
    Pont vertice;           //Aponta para o vertices
    struct Guarda *prox;    //Proximo item da lista
}Guarda, *PONT_V;

typedef struct Lista{
    struct Guarda *inicio;  //Inicio da lista
    struct Guarda *fim;     //Fim da lista
}*Lista;

// Função para criar um novo vértice
Pont criar_vertice(Lista lista, char *nome){
    PONT_V aux = lista->inicio;
    Pont vertice = NULL;

    while(1){
        if(aux == NULL){                        //Se (aux == NULL), cria um novo vértice e adiciona
            vertice = malloc(sizeof(No));       
            vertice->cor = branco;              
            strcpy(vertice->id, nome);         
            vertice->lista_vizinhos = NULL;
            
            PONT_V novo_vertice = malloc(sizeof(Guarda));
            novo_vertice->vertice = vertice;
            novo_vertice->prox = lista->inicio;
            lista->inicio = novo_vertice;   //Atualiza o inicio da lista
            break;
        }else if(strcmp(aux->vertice->id, nome) == 0){  //Se o vertice ja existe, retorna ele
            vertice = aux->vertice;
            break;
        }
        aux = aux->prox;    //Vai pro proximo item da lista
    }
    return vertice;   
}

// Função para conectar dois vértices
void conectar_vertices(Pont v1, Pont v2){
    Vizinho *novo_vizinho = malloc(sizeof(Vizinho));
    novo_vizinho->vertice = v2;     //Atribui v2 ao novo vizinho
    novo_vizinho->prox = v1->lista_vizinhos;    //O proximo é o que estava na lista de v1
    v1->lista_vizinhos = novo_vizinho;          //Atualiza a lista de vizinhos de v1
}

// Função para inicializar o grafo
Pont inicializar_grafo(Lista lista){
    int num_vertices, num_arestas;

    scanf("%d%d", &num_vertices, &num_arestas); //Le o numero de vertices e arestas

    char nome_v1[8], nome_v2[8];    //Guarda o nome dos vertices
    Pont v1 = NULL, v2 = NULL;      //Ponteiros para os mesmos

    for(int i = 0; i < num_arestas; i++){
        scanf("%s", nome_v1);
        fflush(stdin);

        scanf("%s", nome_v2);
        fflush(stdin);
        
        v1 = criar_vertice(lista, nome_v1);     //Cria v1
        v2 = criar_vertice(lista, nome_v2);     //Cria v2
        
        // Conectar vértices
        conectar_vertices(v1, v2);  //Conecta v1 a v2 por uma aresta
        conectar_vertices(v2, v1);  //  ||    v2 a v1 ||  ||     ||
    }
    
    PONT_V aux = lista->inicio;
    while(strcmp(aux->vertice->id, "Entrada") != 0){
        aux = aux->prox;
        if(aux == NULL){
            printf("\nFalha ao encontrar 'Entrada'!\n");
            exit(1);
        }
    }
    aux->vertice->cor = cinza;  //Encontra o vertice 'Entrada' e marca ele como cinza
    
    return aux->vertice;    //Retorna 'Entrada'
}

// Função para adicionar à pilha
void add_pilha(Lista pilha, Pont item, int posicao){
    PONT_V novo = malloc(sizeof(Guarda));
    novo->vertice = item;
    novo->prox = NULL;
    item->cor = cinza;
    item->dist = posicao;

    if(pilha->inicio == NULL){      //Se a pilha ta vazia, coloca o novo item como começo e fim
        pilha->inicio = novo;
        pilha->fim = novo;
    }else{                          //Se não, vai pro fim da pilha
        pilha->fim->prox = novo;
        pilha->fim = novo;
    }
}

// Função para excluir a fila atual
void excluir_fila(Lista lista){
    PONT_V aux = lista->inicio;

    while(aux != NULL){     //Vai liberando a memoria de cada item
        lista->inicio = aux->prox;
        free(aux);
        aux = lista->inicio;
    }
    lista->inicio = NULL;
}

// Função para encontrar o caminho até o destino desejado
Pont encontrar(Lista fila, char destino[8]){
    Pont posicao;

    while(fila->inicio != NULL){    //Verifica se a fila ta vazia
        posicao = fila->inicio->vertice;

        if(posicao->cor == preto) {    //Verifica se o vertice ja foi explorado
            PONT_V aux = fila->inicio;      //Coloca o vertice a ser excluido no ponteiro auxiliar
            fila->inicio = fila->inicio->prox;  //Atualiza o inicio
            free(aux);
        }

        Vizinho *vizinho_atual = posicao->lista_vizinhos;   //Vizinhos do vertice atual
        while(vizinho_atual != NULL){       //Enquanto existir vizinhos
            if(vizinho_atual->vertice->cor == branco){      //Verifica se o vizinho ja foi explorado
                add_pilha(fila, vizinho_atual->vertice, posicao->dist + 1); //Adiciona ele a fila
            }
            vizinho_atual = vizinho_atual->prox;
        }

        if(strcmp(posicao->id, destino) == 0){   //Encontrou o destino
            excluir_fila(fila); //Libera a memoria da fila
            return(posicao);    //Retorna ponteiro da posição atual
        }

        posicao->cor = preto;   //Vertice ja explorado

        PONT_V aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
    }
    return NULL;
}

// Função para reiniciar a lista
void reiniciar(Lista lista){
    PONT_V aux = lista->inicio;
    while(aux != NULL){     //Passa em todos os itens da lista colocando eles como brancos
        aux->vertice->cor = branco;
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
    char destino[8] = {"*"};    //Destino 'Queijo'
    
    Pont queijo = encontrar(aux, destino);      //Começa a procurar pelo queijo
    if(queijo == NULL){
        printf("\nFalha ao encontrar '*'!\n");
        exit(1);
    }
    int distancia = queijo->dist;       //Distancia = distancia da entrada até o queijo
    reiniciar(lista);                   //Reinicia a lista
    add_pilha(aux, queijo, 0);          //Coloca 'queijo' na lista auxiliar
    
    strcpy(destino, "Saida");       //Destino 'Saida'
    Pont saida = encontrar(aux, destino);       //Começa a procurar pela saída
    if(saida == NULL){
        printf("\nFalha ao encontrar 'Saida'!\n");
        exit(1);
    }

    distancia += saida->dist;                   //Distancia = distancia + distancia do queijo até a saída
    printf("\nDistancia percorrida no grafo: %d\n", distancia);

    return 0;
}