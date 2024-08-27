#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave; // Onde o valor do nó é guardado
    struct aux *esq; // Nó esquerdo da raiz
    struct aux *dir; // Nó direito da raiz
    int bal; // Fator de balanceamento
} NO, *PONT;

/* Cria um novo nó com chave=ch e retorna seu endereço */
PONT criarNovoNo(TIPOCHAVE ch){

    // Aloca memória para o novo nó
    PONT novo = malloc(sizeof(NO));

    // Verifica se a alocação de memória foi bem-sucedida
    if(novo){

        // Se a alocação foi bem-sucedida, preenche os valores do novo nó
        novo->chave = ch; // Define a chave do novo nó como 'ch'
        novo->esq = NULL; // Inicializa o ponteiro para o filho esquerdo como NULL
        novo->dir = NULL; // Inicializa o ponteiro para o filho direito como NULL
        novo->bal = 0;    // Inicializa o fator de balanceamento como 0
    }else{

        // Se a alocação de memória falhou, exibe uma mensagem de erro
        printf("\nErro ao criar o nó!\n");
    }

    // Retorna o endereço do novo nó criado
    return novo;
}


// Retorna o maior valor entre dois inteiros
int max(int a, int b){
    return (a > b) ? a : b;
}

// Retorna a altura de uma (sub-)árvore
 int altura(PONT p){
    if (p == NULL){
        return -1; // Altura de uma árvore vazia é -1
    }else{
        return 1 + max(altura(p->esq), altura(p->dir)); // Altura é o máximo entre a altura das subárvores esquerda e direita, mais 1
    }
}

// Atualiza o balanceamento total
int atualizarBalanceamentoTotal(PONT raiz){
    if(raiz){
        return (altura(raiz->dir) - altura(raiz->esq));
    }else{
        return 0;
    }
}

/* Exibe árvore Em Ordem */
void exibirArvoreEmOrdem(PONT raiz){
    if (raiz != NULL) {
        exibirArvoreEmOrdem(raiz->esq); // Exibe a subárvore esquerda em ordem

        printf("%d ", raiz->chave); // Exibe a chave do nó atual

        exibirArvoreEmOrdem(raiz->dir); // Exibe a subárvore direita em ordem
    }
}

/* Exibe árvore Pre Ordem */
void exibirArvorePreOrdem(PONT raiz){
    if (raiz != NULL) {
        printf("%d ", raiz->chave); // Exibe a chave do nó atual

        exibirArvorePreOrdem(raiz->esq); // Exibe a subárvore esquerda em pré-ordem
        exibirArvorePreOrdem(raiz->dir); // Exibe a subárvore direita em pré-ordem
    }
}

/* Exibe árvore Pos Ordem */
void exibirArvorePosOrdem(PONT raiz){
    if (raiz != NULL) {
        exibirArvorePosOrdem(raiz->esq); // Exibe a subárvore esquerda em pós-ordem
        exibirArvorePosOrdem(raiz->dir); // Exibe a subárvore direita em pós-ordem

        printf("%d ", raiz->chave); // Exibe a chave do nó atual
    }
}


/* Exibe árvore Em Ordem (com parênteses para os filhos) */
void exibirArvore(PONT raiz){
    if (raiz != NULL) {
        
        printf("("); // Imprime um parêntese aberto
        printf("%d ", raiz->chave); // Imprime a chave do nó atual
        
        exibirArvore(raiz->esq); // Chama a função recursivamente para exibir a subárvore esquerda        
        exibirArvore(raiz->dir); // Chama a função recursivamente para exibir a subárvore direita
        
        printf(")"); // Imprime um parêntese fechado
    }
}


/* Exibe árvore Pre-Ordem indicando pai de cada nó */
void exibirArvore2(PONT raiz, TIPOCHAVE chavePai){
    if (raiz != NULL) {
        
        printf("Pai: %d, Chave: %d\n", chavePai, raiz->chave); // Imprime o pai e a chave do nó atual
        
        // Chama a função recursivamente para exibir a subárvore esquerda, indicando o nó atual como pai
        exibirArvore2(raiz->esq, raiz->chave);
        
        // Chama a função recursivamente para exibir a subárvore direita, indicando o nó atual como pai
        exibirArvore2(raiz->dir, raiz->chave);
    }
}


// Verifica se árvore é AVL
bool ehAVL(PONT p){
    if (p == NULL){
        return false; // Se for nulo retorna nulo
    }

    // Calcula a altura da subárvore esquerda e da subárvore direita
    int altura_esq = altura(p->esq);
    int altura_dir = altura(p->dir);

    if(((altura_dir - altura_esq) <= 1 && (altura_dir - altura_esq) >= -1) && ehAVL(p->esq) && ehAVL(p->dir)){
        return true; // Se a AVL estiver balanceada, retorna true
    }else{
        return false; // Se a AVL não estiver balanceada, retorna nulo
    }
}

PONT rotacaoL(PONT p) {
    // p é o nó com fator de balanceamento "-2" (pende à esquerda)
    PONT u = p->esq;

    // rotação à esquerda e à direita (LR)
    if(u->bal == 1){
    PONT v = u->dir; 
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    if(v->bal == -1) p->bal = -1;
    else p->bal = 0;

    if(v->bal == 1) u->bal = -1;
    else u->bal = 0;

    v->bal = 0;

    return v;
    }
    // rotação simples esquerda (LL)
    //if(u->bal == -1){
    p->esq = u->dir; // adota filho u
    u->dir = p; // u vira nova raiz e p seu filho direito
    p->bal = 0; // atualiza fator de balanceamento
    u->bal = 0;

    return u;
    //}
}

PONT rotacaoR(PONT p) {
    // p é o nó com fator de balanceamento "2" (pende à direita)
    PONT u = p->dir;

    // rotação à direita e à esquerda (LR)
    if(u->bal == -1){
    PONT v = u->esq; 
    u->esq = v->dir;
    v->dir = u;
    p->dir = v->esq;
    v->esq = p;

    if(v->bal == 1) p->bal = 1;
    else p->bal = 0;

    if(v->bal == -1) u->bal = 1;
    else u->bal = 0;

    v->bal = 0;

    return v;
    } 

    // rotação simples esquerda (RR)
    //if(u->bal == 1){
    p->dir = u->esq; // adota filho u
    u->esq = p; // u vira nova raiz e p seu filho esquerdo
    p->bal = 0; // atualiza fator de balanceamento
    u->bal = 0;

    return u;
    //}
}

/* Retorna o endereço do nó que contém chave=ch ou NULL caso a chave não seja encontrada. Utiliza busca binária recursiva */
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
    if (raiz == NULL || raiz->chave == ch){
        return raiz;
    }else if(raiz->chave < ch){
        return buscaBinaria(ch, raiz->dir);
    }else{
        return buscaBinaria(ch, raiz->esq);
    }
}

/* Inserção AVL: raiz é inicializado com o endereço do nó raiz e *alterou com false */
PONT inserirAVL(PONT *p, TIPOCHAVE ch) {
    
    // Verifica se a árvore está vazia
    if (*p == NULL){ 
        *p = criarNovoNo(ch); // Se estiver vazia, cria um novo nó com a chave e o torna a raiz da árvore
        printf("\nNó criado, com o valor %d",ch);
    }else{
        PONT busca = buscaBinaria(ch, *p); // Realiza uma busca para verificar se a chave já existe na árvore

        if (busca != NULL) {
            printf("\nErro, a chave já existe!");

            return *p; // Retorna a raiz sem fazer alterações, já que a chave já existe
            // Se a chave não existe, determina se ela deve ser inserida na subárvore esquerda ou direita

        }else if(ch < (*p)->chave){ 
            (*p)->esq = inserirAVL(&((*p)->esq), ch); // Se for menor, insere na subárvore esquerda e atualiza o ponteiro para a esquerda
        }else if(ch > (*p)->chave) {            
            (*p)->dir = inserirAVL(&((*p)->dir), ch); // Se for maior, insere na subárvore direita e atualiza o ponteiro para a direita
        }
    }

    if(!ehAVL(*p)){
        (*p)->bal = atualizarBalanceamentoTotal(*p); // Atualiza o fator de balanceamento do nó atual

        // Verifica se o nó desbalanceou após a inserção e realiza as rotações necessárias para balancear a árvore
        if ((*p)->bal > 1) { // Se for maior que 1, chama a função rotacaoL
            *p = rotacaoR(*p);
        } else if ((*p)->bal < -1) { // Se for menor que -1, chama a função rotacaoR
            *p = rotacaoL(*p);
        }
    }

    return *p; // Retorna o endereço da raiz da árvore atualizada
}

// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL; // Inicializa o nó pai como NULL

    while (atual != NULL) {
        if (ch == atual->chave) {
            return atual; // Retorna o nó encontrado
        }
            
        *pai = atual; // Atualiza o nó pai para o nó atual

        if (ch < atual->chave){
            atual = atual->esq; // Desce para o filho esquerdo
        }else{
            atual = atual->dir; // Desce para o filho direito
        }    
    }

    return NULL; // Retorna NULL se a chave não for encontrada
}

/* Auxiliar da função excluirChave, procura a maior chave menor que a chave que será excluída */
PONT maiorAEsquerda(PONT p){
    PONT ant = p;       // cria ant e faz ele apontar para p

    // Percorre para a direita até encontrar o maior nó
    while(ant->dir != NULL){
        ant = ant->dir;     // Vai para o filho direito
    }

    return ant;     // Retorna o nó com a maior chave menor que a chave do nó passado
}

/* Exclui a chave com valor igual a ch */
PONT excluirAVL(PONT raiz, TIPOCHAVE ch){
    if(raiz == NULL){ // Se o nó não for encontrado
        printf("\nValor nao encontrado!\n"); // Mensagem de erro
        return NULL;
    }

    if(raiz->chave == ch){ // Se o nó a ser excluído for a raiz
        if((raiz->esq == NULL) && (raiz->dir == NULL)){ // Se a raiz for uma folha
            free(raiz); // Libera a memória da raiz

            printf("\nElemento %d removido!\n", ch); // Mensagem de confirmação

            return NULL; // Retorna NULL indicando que a árvore está vazia
        } else {
            if(raiz->esq != NULL && raiz->dir != NULL){ // Se a raiz tiver dois filhos
                PONT aux = maiorAEsquerda(raiz->esq); // Encontra o maior nó à esquerda da raiz

                raiz->chave = aux->chave; // Substitui a chave da raiz pela chave do nó auxiliar
                aux->chave = ch; // Troca a chave do nó auxiliar pela chave a ser excluída

                raiz->esq = excluirAVL(raiz->esq, aux->chave); // Exclui o nó com a chave 'ch' da subárvore esquerda
            } else { // Raiz com um filho
                PONT aux;

                if(raiz->esq != NULL){ // Se a raiz esquerda for diferente de NULL, o elemento está lá, então salvamos ele
                    aux = raiz->esq;
                }else{
                    aux = raiz->dir; // Se não, ele está na raiz direita, então salvamos ele
                }

                if(aux == NULL){ // nenhum filho
                    aux = raiz;
                    raiz = NULL;
                }else{  // Um filho
                    *raiz = *aux; // salva conteúdo do filho
                } 

                free(aux); // Libera a memória da raiz
                printf("\nElemento %d removido!\n", ch); // Mensagem de confirmação
            }
        }
    }else{
        if(ch < raiz->chave){ // Se a chave a ser excluída for menor que a chave da raiz
            raiz->esq = excluirAVL(raiz->esq, ch); // Exclui o nó na subárvore esquerda
        } else {
            raiz->dir = excluirAVL(raiz->dir, ch); // Exclui o nó na subárvore direita
        }
    }
    
    if(raiz == NULL){
        return raiz;
    }

    // Atualiza o fator de balanceamento
    if(!ehAVL(raiz)){
        raiz->bal = atualizarBalanceamentoTotal(raiz); // Atualiza o fator de balanceamento da raiz

        // Verifica e realiza as rotações necessárias
        if (raiz->bal > 1) { // Desbalanceamento à direita
            raiz = rotacaoR(raiz); // Realiza rotação à esquerda
        } else if (raiz->bal < -1) { // Desbalanceamento à esquerda
            raiz = rotacaoL(raiz); // Realiza rotação à direita
        }
    }

    return raiz; // Retorna a raiz atualizada
}

/* Função auxiliar na destruição (liberação da memória) de uma árvore */
void destruirAux(PONT subRaiz){
    if (subRaiz != NULL) { // Verifica se a subárvore não é vazia
        destruirAux(subRaiz->esq); // Destrói a subárvore esquerda
        destruirAux(subRaiz->dir); // Destrói a subárvore direita

        free(subRaiz); // Libera a memória do nó atual
    }
}

/* Libera toda a memória de uma árvore e coloca NULL no valor da raiz */
void destruirArvore(PONT *raiz){
    if(*raiz != NULL){
        destruirAux(*raiz); // Chama a função auxiliar para destruir a árvore
        *raiz = NULL; // Define a raiz como NULL, indicando que a árvore está vazia
    }
}

// Inicializa árvore
void inicializar(PONT *raiz){
    *raiz = NULL;
}

//funçao principal
int main() {
    int opcao, chave;
    PONT raiz;

    inicializar(&raiz);

    do {
        printf("\n\nOpções:\n");
        printf("1. Inserir elemento\n");
        printf("2. Exibir árvore em ordem\n");
        printf("3. Exibir árvore pré-ordem\n");
        printf("4. Exibir árvore pós-ordem\n");
        printf("5. Exibir árvore com parênteses\n");
        printf("6. Exibir árvore com pai de cada nó\n");
        printf("7. Excluir elemento\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nDigite a chave a ser inserida: ");
                scanf("%d", &chave);
                raiz = inserirAVL(&raiz, chave);
                break;
            case 2:
                printf("\nÁrvore AVL em ordem: ");
                exibirArvoreEmOrdem(raiz);
                printf("\n");
                break;
            case 3:
                printf("\nÁrvore AVL pré-ordem: ");
                exibirArvorePreOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("\nÁrvore AVL pós-ordem: ");
                exibirArvorePosOrdem(raiz);
                printf("\n");
                break;
            case 5:
                printf("\nÁrvore AVL com parênteses: ");
                exibirArvore(raiz);
                printf("\n");
                break;
            case 6:
                printf("\nÁrvore AVL com pai de cada nó: \n");
                exibirArvore2(raiz, -1);        // -1 indica que é a raiz
                break;
            case 7:
                printf("\nDigite a chave a ser excluída: ");
                scanf("%d", &chave);
                raiz = excluirAVL(raiz, chave);
                break;
            case 8:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    }while (opcao != 8);

    destruirArvore(&raiz);      // libera memória alocada para a árvore (remove todos os nós)

    return 0;
}