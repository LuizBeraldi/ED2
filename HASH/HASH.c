#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 31  // Definição do tamanho da tabela hash, escolhido como o número primo mais próximo de 15 * 2

typedef struct{
    int id;
    char descricao[200];
    float preco;
} Produto;

typedef struct aux{
    struct aux *prox;
    Produto produto;
} No;

typedef struct{
    No* inicio;
} Lista;

//HASH COM ENCADEAMENTO SEPARADO, usando o metodo da divisao
void inicializarLista(Lista* l) {
    l->inicio = NULL;
}

void inserirLista(Lista* l, Produto produto){
    No* novo = malloc(sizeof(No));
    novo->produto = produto;
    novo->prox = l->inicio; // Faz o novo nó apontar para o início da lista
    l->inicio = novo; // Atualiza o início da lista para o novo nó
}

int buscarLista(Lista* l, int id){
    No *aux = l->inicio;  // Cria um nó auxiliar para percorrer a lista

    while(aux && aux->produto.id != id){ // Percorre a lista enquanto não chegar ao final ou encontrar o ID
        aux = aux->prox;
    }

    if(aux){
        return aux->produto.id;
    }else{ // se nao achou, retorna -1
        return -1;
    }
}

//Imprimir apenas os com valor
void imprimirLista(Lista* l, int i){
    No* aux = l->inicio;  // Cria um nó auxiliar para percorrer a lista
    
    if(aux){
        printf("Posicao [%2d] = ", i); // Posicao [n] = ch ch ch
        while(aux){
            printf("%2d ", aux->produto.id);
            aux = aux->prox;
        }
        printf("\n");
    }
}

//Imprimir todos
/* void imprimirLista(Lista* l){
    No* aux = l->inicio;

    while(aux){
        printf("%2d ", aux->produto.id);
        aux = aux->prox;
    }
} */

void inicializarSeparado(Lista hash[]){
    for(int i=0; i< TAM; i++){
        inicializarLista(&hash[i]); // vazio == null
    }
}

int espalharSeparado(int id){
    return id % TAM; // resto da divisao de id por TAM
}

void inserirSeparado(Lista hash[], Produto produto) {
    int index = espalharSeparado(produto.id); // Calcula o índice da tabela hash para o produto
    inserirLista(&hash[index], produto);  // Insere o produto na lista encadeada correspondente
}

int buscarSeparado(Lista hash[], int id) {
    int index = espalharSeparado(id);  // Calcula o índice da tabela hash para o ID
    return buscarLista(&hash[index], id); // Realiza a busca na lista encadeada correspondente
}

//Imprimir apenas os com valor
void imprimirSeparado(Lista hash[]){
    printf("\n\tHASH ENCADEAMENTO SEPARADO\n");
    for(int i=0; i < TAM; i++){
        imprimirLista(&hash[i], i);
    }
}

//Imprimir todos
/* void imprimirSeparado(Lista hash[]){
    for(int i=0; i < TAM; i++) {
        printf("[%2d] = ", i);
        imprimirLista(&hash[i]);
        printf("\n");
    }
} */

void removerSeparado(Lista hash[], int id){
    int index = espalharSeparado(id);  // Calcula o índice da tabela hash para o ID
    No *atual = hash[index].inicio;  // Aponta para o início da lista encadeada correspondente
    No *anterior = NULL;  // Aponta para o nó anterior ao atual

    while(atual != NULL && atual->produto.id != id){ // Percorre a lista até encontrar o nó com o ID desejado
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("\nO id [%d] nao existe no Hash Separado!\n", id);
        return;
    }

    if (anterior == NULL) { // Se o nó a ser removido é o primeiro da lista
        hash[index].inicio = atual->prox; // Atualiza o início da lista
    } else {
        anterior->prox = atual->prox; // Remove o nó atual da lista
    }
    printf("\n'%s' com id [%d] excluido no Hash Separado!\n", atual->produto.descricao, id);
    free(atual);
}

void destruirLista(Lista* l){
    No* atual = l->inicio;
    No* proximo = NULL;

    while (atual) { // Percorre a lista
        proximo = atual->prox; // Guarda o próximo nó
        free(atual);  // Libera a memória ocupada pelo nó atual
        atual = proximo;  // Avança para o próximo nó
    }
    l->inicio = NULL; 
}

void destruirSeparado(Lista hash[]){
    for (int i = 0; i < TAM; i++) {  // Percorre todas as posições da tabela hash
        destruirLista(&hash[i]);  // Libera a memória ocupada pelas listas encadeadas
    }
}

//HASH COM ENCADEAMENTO ABERTO, usando os metodos da dobra e duplo hash
void inicializarAberto(Produto hash[]){
    for(int i=0; i< TAM; i++){
        hash[i].id = -1; // -1 == vazio
    }
}

char soma(char a, char b){
    int soma = (a - '0') + (b - '0');  // Converte caracteres para inteiros e realiza a soma
    return (soma % 10) + '0'; // Retorna o dígito da unidade da soma convertido para caractere
}

int converte(char *str){
    int num = 0;
    for (int i = 0; str[i] != '\0'; ++i) {  // Percorre a string
        num = num * 10 + str[i] - '0';  // Converte os caracteres para inteiros e calcula o número
    }
    return num; // Retorna o número convertido
}

int espalharAberto(int id){
    int i, t = 2; // Define o tamanho da dobra como 2
    char idStr[6]; // No maximo 6
    char temp[6];
    sprintf(idStr, "%d", id);
    int tam = strlen(idStr); // Calcula o tamanho da string
    strcpy(temp, idStr);  // Copia a string do ID para a string temporária

    for (i = 0; i < (tam / t) - 1; i++) {  // Realiza a dobra
        for (int j = 0; j < t; ++j) {  // Percorre os caracteres da string
            temp[(i * t) + j + t] = soma(temp[(i * t) + j + t], temp[((i * t) + j + t) - ((2 * j) + 1)]);  // Realiza a operação de soma
        }
    }
    return converte(&temp[i * t]);  // Retorna o resultado convertido
}

int passoHash(int id){
    return 1 + (id % (TAM - 1)); // Calcula o passo
}

void inserirAberto(Produto hash[], Produto produto){
    int index = espalharAberto(produto.id); // Calcula o índice da tabela hash para o produto
    int passo = passoHash(produto.id);  // Calcula o passo para a função de hash

    while(hash[index].id != -1){
        index = (index + passo) % TAM;
    }
    hash[index] = produto; // Insere o produto na posição encontrada
}

int buscarAberto(Produto hash[], int id){
    int index = espalharAberto(id); // Calcula o índice da tabela hash para o ID
    int passo = passoHash(id);  // Calcula o passo para a função de hash

    while(hash[index].id != -1){
        if(hash[index].id == id){
            return index;
        }
        index = (index + passo) % TAM;
    }
    return -1;  // Retorna -1 se o produto não for encontrado
}

//Imprimir apenas os com valor
void imprimirAberto(Produto hash[]){
    printf("\n\tHASH ENCADEAMENTO ABERTO\n");
    for(int i=0; i < TAM; i++){
        if(hash[i].id != -1){
            printf("Posicao [%2d] = %2d\n", i, hash[i].id); // Posicao [n] = ch
        }
    }
} 

//Imprimir todos
/* void imprimirAberto(Produto hash[]){
    for(int i=0; i < TAM; i++){
        if(hash[i].id == -1){
            printf("Posicao [%2d] = \n", i);
        }else{
            printf("Posicao [%2d] = %2d\n", i, hash[i].id);
        }
    }
} */

void removerAberto(Produto hash[], int id){
    int index = buscarAberto(hash, id); // Busca o produto na tabela hash
    if(index == -1) { // Se o produto não for encontrado
        printf("O id [%d] nao existe no Hash Aberto!\n", id);
        return;
    }
    hash[index].id = -1; // Marca a posição como vazia
    printf("'%s' com id [%d] excluido no Hash Aberto!\n", hash[index].descricao, id);
}

void cadastrarProduto(int id, char descricao[], float preco, Produto hashAberto[], Lista hashSeparado[]){
    Produto novo;
    novo.id = id;
    strcpy(novo.descricao, descricao);
    novo.preco = preco;

    if(preco <= 200){ // se o preço for menor ou igual a 200 reais, o produto vai para o encadeamento separado
        inserirSeparado(hashSeparado, novo);
    }else{ // caso contrario, ele vai para o encadeamento aberto
        inserirAberto(hashAberto, novo);
    }
}

int main(){
    Lista hashSeparado[TAM];
    Produto hashAberto[TAM];

    inicializarSeparado(hashSeparado);
    inicializarAberto(hashAberto);

    // inserçao de produtos na tabela hash
    cadastrarProduto(5, "Produto 1", 9.87, hashAberto, hashSeparado);

    cadastrarProduto(15, "Produto 2", 21.90, hashAberto, hashSeparado);

    cadastrarProduto(4, "Produto 3", 35.61, hashAberto, hashSeparado);

    cadastrarProduto(30, "Produto 4", 57.99, hashAberto, hashSeparado);

    cadastrarProduto(40, "Produto 5", 18.00, hashAberto, hashSeparado);

    cadastrarProduto(40, "Produto 6", 212.45, hashAberto, hashSeparado);

    cadastrarProduto(4, "Produto 7", 26.99, hashAberto, hashSeparado);

    cadastrarProduto(4, "Produto 8", 250.89, hashAberto, hashSeparado);

    cadastrarProduto(4, "Produto 9", 201.00, hashAberto, hashSeparado);

    // imprimir tabela hash
    imprimirSeparado(hashSeparado);
    imprimirAberto(hashAberto);

    // remover um produto
    int idRemover = 40;
    removerSeparado(hashSeparado, idRemover);
    removerAberto(hashAberto, idRemover);

    //imprimir tabela hash após remoção
    imprimirSeparado(hashSeparado);
    imprimirAberto(hashAberto);

    destruirSeparado(hashSeparado);

    return 0;
}