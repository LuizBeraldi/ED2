#include <stdio.h>
#include <stdlib.h>

typedef struct aux{
    int id, cor;        // cor = (0 = preto) || (1 = rubro)
    struct aux* pai; 
    struct aux* dir;
    struct aux* esq; 
}no, *NO;

typedef struct{
    NO raiz; // identifica determinado nó como raiz
    NO nil;  // identifica determinado nó como nulo
}RAIZ;

// função para inicializar a árvore
void inicializar(RAIZ* T){
    T->nil = (NO)malloc(sizeof(no));
    T->nil->cor = 0;        // nulo é preto
    T->raiz = T->nil;
}

// função para criar um novo nó
NO criarNovoNo(RAIZ* T, int ID){
    NO novo = (NO)malloc(sizeof(no));
    novo->id = ID;
    novo->pai = T->nil;
    novo->esq = T->nil;
    novo->dir = T->nil;
    novo->cor = 1; // o nó criado sempre sera rubro
    return novo;
}

// função para rotacionar a árvore para a esquerda
void rotacaoL(RAIZ* T, NO x){
    NO y = x->dir;
    if(y != T->nil){
        x->dir = y->esq;
        if(y->esq != T->nil){
            y->esq->pai = x;
        }

        y->pai = x->pai;

        if(x->pai == T->nil){
            T->raiz = y;
        }else if(x == x->pai->esq){
            x->pai->esq = y;
        }else{
            x->pai->dir = y;
        }

        y->esq = x;
        x->pai = y;
    }
}

// função para rotacionar a árvore para a direita
void rotacaoR(RAIZ* T, NO y){
    NO x = y->esq;
    if(x != T->nil){
        y->esq = x->dir;

        if(x->dir != T->nil){
            x->dir->pai = y;
        }

        x->pai = y->pai;

        if(y->pai == T->nil){
            T->raiz = x;
        }else if(y == y->pai->dir){
            y->pai->dir = x;
        }else{
            y->pai->esq = x;
        }

        x->dir = y;
        y->pai = x;
    }
}

// função que verifica em qual caso está a árvore após a inserção de um aluno e balanceia a arvore
void inserirCasos(RAIZ* T, NO z){
    printf("\n\nINSERINDO %d", z->id);
    while(z->pai != T->nil && z->pai->cor == 1){
        if(z->pai == z->pai->pai->esq){
            NO y = z->pai->pai->dir;
            // CASO 1
            if(y != T->nil && y->cor == 1){
                printf("\nCASO 1: Pai->PRETO; Irmao->PRETO; Avo->RUBRO");
                z->pai->cor = 0;
                y->cor = 0;
                z->pai->pai->cor = 1;
                z = z->pai->pai;
            }else{
            // CASO 2
                if(z == z->pai->dir){       // || (y->cor != 1)
                    printf("\nCASO 2: Rotaciona o pai para a esquerda");
                    z = z->pai;
                    rotacaoL(T, z);
                }
            // CASO 3
                printf("\nCASO 3: Pai->PRETO; Avo->RUBRO; Rotaciona o avo para a direita");
                z->pai->cor = 0;
                z->pai->pai->cor = 1;
                rotacaoR(T, z->pai->pai);
            }
        // Caso espelho da cláusula anterior
        }else if((z->pai == z->pai->pai->dir)){
            NO y = z->pai->pai->esq;
            // CASO 1
            if(y != T->nil && y->cor == 1){
                printf("\nCASO 1: Pai->PRETO; Irmao->PRETO; Avo->RUBRO");
                z->pai->cor = 0;
                y->cor = 0;
                z->pai->pai->cor = 1;
                z = z->pai->pai;
            }else{
            // CASO 2
                if(z == z->pai->esq){           // || (y->cor != 1)
                printf("\nCASO 2: Rotaciona o pai para a direita");
                    z = z->pai;
                    rotacaoR(T, z);
                }
            // CASO 3
                printf("\nCASO 3: Pai->PRETO; Avo->RUBRO; Rotaciona o avo para a esquerda");
                z->pai->cor = 0;
                z->pai->pai->cor = 1;
                rotacaoL(T, z->pai->pai);
            }
        }
    }
    T->raiz->cor = 0;
}

// função para inserir um aluno da árvore
void inserirAluno(RAIZ* T, int ID){
    NO z = criarNovoNo(T, ID);
    NO y = T->nil;
    NO x = T->raiz;
    while(x != T->nil){
        y = x;

        if(z->id < x->id){
            x = x->esq;
        }else{
            x = x->dir;
        }
    }
    z->pai = y;

    if(y == T->nil){
        T->raiz = z;
    }else if(z->id < y->id){
        y->esq = z;
    }else{
        y->dir = z;
    }

    z->esq = T->nil;
    z->dir = T->nil;
    z->cor = 1;         // z->cor = vermelho

    inserirCasos(T, z);
}

/* Exibe árvore em Ordem */
void exibirArvoreEmOrdem(RAIZ* T, NO x){
    if(x != T->nil){
        exibirArvoreEmOrdem(T, x->esq);

        printf("%04d ", x->id);

        exibirArvoreEmOrdem(T, x->dir);
    }
}

/* Exibe árvore em Pre Ordem */
void exibirArvorePreOrdem(RAIZ *T, NO raiz){
    if (raiz != T->nil){
        printf("%04d ", raiz->id); // Exibe a chave do nó atual

        exibirArvorePreOrdem(T, raiz->esq); // Exibe a subárvore esquerda em pré-ordem
        exibirArvorePreOrdem(T, raiz->dir); // Exibe a subárvore direita em pré-ordem
    }
}

/* Exibe árvore em Pos Ordem */
void exibirArvorePosOrdem(RAIZ *T, NO raiz){
    if (raiz != T->nil){
        exibirArvorePosOrdem(T, raiz->esq); // Exibe a subárvore esquerda em pós-ordem
        exibirArvorePosOrdem(T, raiz->dir); // Exibe a subárvore direita em pós-ordem

        printf("%04d ", raiz->id); // Exibe a chave do nó atual
    }
}

/* Exibe árvore em Pre-Ordem indicando pai de cada nó */
void exibirArvore2(NO raiz, int chavePai, RAIZ *T){
    if (raiz != T->nil){
        if(chavePai == -111){
            printf("RAIZ: %d\n", raiz->id); // Imprime o pai e a chave do nó atual
            
            // Chama a função recursivamente para exibir a subárvore esquerda, indicando o nó atual como pai
            exibirArvore2(raiz->esq, raiz->id, T);
            
            // Chama a função recursivamente para exibir a subárvore direita, indicando o nó atual como pai
            exibirArvore2(raiz->dir, raiz->id, T);
        }else{
            if(raiz->cor == 0){
                if(chavePai > raiz->id){
                    printf("Pai: %04d, Filho: %04d -> PRETO -> ESQUERDA\n", chavePai, raiz->id); // Imprime o pai e a chave do nó atual
                }else{
                    printf("Pai: %04d, Filho: %04d -> PRETO -> DIREITA\n", chavePai, raiz->id); // Imprime o pai e a chave do nó atual
                }    
            }else{
                if(chavePai > raiz->id){
                    printf("Pai: %04d, Filho: %04d -> RUBRO -> ESQUERDA\n", chavePai, raiz->id); // Imprime o pai e a chave do nó atual
                }else{
                    printf("Pai: %04d, Filho: %04d -> RUBRO -> DIREITA\n", chavePai, raiz->id); // Imprime o pai e a chave do nó atual
                }
            }
            
            // Chama a função recursivamente para exibir a subárvore esquerda, indicando o nó atual como pai
            exibirArvore2(raiz->esq, raiz->id, T);
            
            // Chama a função recursivamente para exibir a subárvore direita, indicando o nó atual como pai
            exibirArvore2(raiz->dir, raiz->id, T);
        }
        
    }
}

// função para buscar o aluno desejado
NO buscarAluno(RAIZ* T, NO x, int ID, int *custo){
    if(x == T->nil || x->id == ID){
        (*custo)++;
        return x;
    }
    (*custo)++;
    if(ID < x->id){
        return buscarAluno(T, x->esq, ID, custo);
    }
    return buscarAluno(T, x->dir, ID, custo);
}

// função que verifica em qual caso está a árvore após a remoção de um aluno e balanceia a arvore
void removerCasos(RAIZ* T, NO x){
    printf("\n\nREMOVENDO %d", x->id);
    while(x != T->raiz && x->cor == 0){
        if(x == x->pai->esq){
            NO w = x->pai->dir;
            // CASO 3.1
            if(w->cor == 1){
                printf("\nCASO 3.1: Irmao->PRETO; Pai->RUBRO; Rotaciona o pai para a esquerda");
                w->cor = 0;
                x->pai->cor = 1;
                rotacaoL(T, x->pai);
                w = x->pai->dir;
            }
            // CASO 3.2
            if(w != T->nil && (w->esq == T->nil || w->esq->cor == 0) && (w->dir == T->nil || w->dir->cor == 0)){
                printf("\nCASO 3.2: Irmao->RUBRO; Sube um nivel da arvore");
                w->cor = 1;
                x = x->pai;
            }else{
            // CASO 3.3
                if(w != T->nil && (w->dir == T->nil || w->dir->cor == 0)){
                    printf("\nCASO 3.3: Irmao->RUBRO; Sobrinho Esquerdo->PRETO; Rotaciona o irmao para a direita");
                    w->esq->cor = 0;
                    w->cor = 1;
                    rotacaoR(T, w);
                    w = x->pai->dir;
                }
            // CASO 3.4
                printf("\nCASO 3.4: Pai->PRETO; Irmao->RUBRO; Sobrinho Direito->PRETO; Rotaciona o pai para a esquerda");
                w->cor = x->pai->cor;
                x->pai->cor = 0;
                w->dir->cor = 0;
                rotacaoL(T, x->pai);
                x = T->raiz;
            }
        }else{
        // Casos espelho dos anteriores
            NO w = x->pai->esq; 
            // CASO 3.1
            if(w->cor == 1){
                printf("\nCASO 3.1: Irmao->PRETO; Pai->RUBRO; Rotaciona o pai para a direita");
                w->cor = 0;
                x->pai->cor = 1;
                rotacaoR(T, x->pai);
                w = x->pai->esq;
            }
            // CASO 3.2
            if(w != T->nil && (w->dir == T->nil || w->dir->cor == 0) && (w->esq == T->nil || w->esq->cor == 0)){
                printf("\nCASO 3.2: Irmao->RUBRO; Sube um nivel da arvore");
                w->cor = 1;
                x = x->pai;
            }else{
            // CASO 3.3
                if(w != T->nil && (w->esq == T->nil || w->esq->cor == 0)){
                    printf("\nCASO 3.3: Irmao->RUBRO; Sobrinho Direito->PRETO; Rotaciona o irmao para a esquerda");
                    w->dir->cor = 0;
                    w->cor = 1;
                    rotacaoL(T, w);
                    w = x->pai->esq;
                }
            // CASO 3.4
                printf("\nCASO 3.4: Pai->PRETO; Irmao->RUBRO; Sobrinho Esquerdo->PRETO; Rotaciona o pai para a direita");
                w->cor = x->pai->cor;
                x->pai->cor = 0;
                w->esq->cor = 0;
                rotacaoR(T, x->pai);
                x = T->raiz;
            }
        }
    }
    x->cor = 0;
} 

// função para remover um aluno da árvore
void removerAluno(RAIZ *T, RAIZ* auxT, int ID){
    NO aux = auxT->raiz;
    // nó raiz folha
    if(aux->id == ID && aux->esq == T->nil && aux->dir == T->nil && aux->pai == T->nil){
        free(aux);
        T->raiz = T->nil;
        return;
    }

    while(aux != T->nil && aux->id != ID){
        if(ID < aux->id){
            aux = aux->esq;
        }else{
            aux = aux->dir;
        }
    }

    if(aux == T->nil){
        printf("Aluno nao encontrado!\n");
        return;
    }

    // nó folha
    if(aux->esq == T->nil && aux->dir == T->nil){
        if(aux->cor == 0){
            removerCasos(T, aux);
        }
        
        if(aux == aux->pai->esq){
            aux->pai->esq = T->nil;
        }else{
            aux->pai->dir = T->nil;
        }
        free(aux);
    }else{      // nó com 1 ou 2 filhos
        NO sucessor;
        RAIZ Tsucessor;

        if(aux->esq != T->nil){
            sucessor = aux->esq;

            while (sucessor->dir != T->nil){
                sucessor = sucessor->dir;
            }

            aux->id = sucessor->id;
            sucessor->id = ID;
            Tsucessor.raiz = aux->esq;
        }else{
            sucessor = aux->dir;

            while(sucessor->esq != T->nil){
                sucessor = sucessor->esq;
            }

            aux->id = sucessor->id;
            sucessor->id = ID;
            Tsucessor.raiz = aux->dir;
        }

        removerAluno(T, &Tsucessor, ID);
    }
}  

// função para retornar o maior valor dentre dois valores
int max(int a, int b){
    return (a > b) ? a : b;
}

// função para retornar a altura total da árvore
int alturaArvore(RAIZ* T, NO x){
    if(x == T->nil){
        return -1;      // nó nulo tem altura -1
    }
    
    int alturaEsq = alturaArvore(T, x->esq);
    int alturaDir = alturaArvore(T, x->dir);
    
    return 1 + max(alturaEsq, alturaDir);
}

// função para retornar a altura total apenas dos nós negros
int alturaNosNegros(RAIZ* T, NO x){
    if(x == T->nil){
        return 0;       // uso para não contar o nó nulo que é preto
    }
    
    int altEsq = 0, altDir = 0;

    if(x->cor == 0){
        altEsq = 1 + alturaNosNegros(T, x->esq);
        altDir = 1 + alturaNosNegros(T, x->dir);
    }else{
        altEsq += alturaNosNegros(T, x->esq);
        altDir += alturaNosNegros(T, x->dir);
    }
    
    return max(altEsq, altDir);
}

// função para contar os nós negros e rubros da árvore
void contarNos(RAIZ *T, NO x, int *rubro, int *preto){
    if(x == T->nil){
        return;
    }

    if(x->cor == 1){
        (*rubro)++;
    }else{
        (*preto)++;
    }

    contarNos(T, x->esq, rubro, preto);
    contarNos(T, x->dir, rubro, preto);
}

// função para cálcular a porcentagem de nós negros e rubros na árvore
void porcentagem(RAIZ *T, NO x){
    if(x == T->nil){
        return;
    }

    int rubro = 0;
    int negro = 0;

    contarNos(T, x, &rubro, &negro);

    int total = rubro + negro;

    float percentRubro = (float)rubro / total * 100;
    float percentNegro = (float)negro / total * 100;

    printf("\nPorcentagem de Rubros: %.2f%%\nPorcentagem de Negros: %.2f%%\n", percentRubro, percentNegro);
}

// função para destruir a árvore e liberar a memória
void destruirArvore(RAIZ* T, NO x){
    if(x != T->nil){
        destruirArvore(T, x->esq);
        destruirArvore(T, x->dir);
        free(x);
    }
    // faz a raiz apontar para nulo
    T->raiz = T->nil; 
}

int main() {
    RAIZ arvore;
    int custo, ID = 10;     // ID recebe o aluno a ser buscado no sistema
    inicializar(&arvore);

    printf("\n\t\tINSERCAO\n");
    inserirAluno(&arvore, 40);
    inserirAluno(&arvore, 20);
    inserirAluno(&arvore, 80);
    inserirAluno(&arvore, 10);
    inserirAluno(&arvore, 30);
    inserirAluno(&arvore, 60);
    inserirAluno(&arvore, 90);
    inserirAluno(&arvore, 50);
    inserirAluno(&arvore, 70);
    inserirAluno(&arvore, 55);

    printf("\n\n\t\tREMOCAO\n");
    removerAluno(&arvore, &arvore, 50);
    removerAluno(&arvore, &arvore, 40);
    removerAluno(&arvore, &arvore, 70);
    //removerAluno(&arvore, &arvore, 1);

    printf("\n\n\nArvore Rubro-Negra em ordem:\n");
    exibirArvoreEmOrdem(&arvore, arvore.raiz);
    printf("\n\n");

    printf("Arvore Rubro-Negra em pre-ordem:\n");
    exibirArvorePreOrdem(&arvore, arvore.raiz);
    printf("\n\n");

    printf("Arvore Rubro-Negra em pos-ordem:\n");
    exibirArvorePosOrdem(&arvore, arvore.raiz);
    printf("\n\n");

    exibirArvore2(arvore.raiz, -111, &arvore);      // -111 serve para verificar que esse é a raiz
    printf("\n");

    NO busca = buscarAluno(&arvore, arvore.raiz, ID, &custo);
    printf("\nBuscando o aluno: %d", ID);
    if(busca != arvore.nil){
        printf("\nAluno encontrado no sistema!\nComparacoes feitas para achar o no: %d\n", custo);
    }else{
        printf("\nAluno nao encontrado no sistema!\nComparacoes feitas para tentar achar o no: %d\n", custo);
    }

    printf("\nAltura da arvore: %d\n", alturaArvore(&arvore, arvore.raiz));
    printf("Altura dos Nos Negros: %d\n", alturaNosNegros(&arvore, arvore.raiz));

    porcentagem(&arvore, arvore.raiz);

    // libera memória alocada para a árvore
    destruirArvore(&arvore, arvore.raiz);

    return 0;
}