/*----------------------------------------------------------------------------*/
/* UFPR – Bacharelado em Ciência da Computação                                */
/* CI057: Algoritmos e Estruturas de dados III, 2sem/2013                     */
/* Aluno: Marfan Fragoso Veras Junior - GRR20113754                           */
/*----------------------------------------------------------------------------*/

#include "libArvRN.h"

/*----------------------------------------------------------------------------*/
/* aloca espaço na memoria para um novo nodo                                  */
/*----------------------------------------------------------------------------*/
Apontador arvRN_criaNodo ( int k, Apontador esq, Apontador dir, Apontador pai ) {
    Apontador p;
    p = malloc (sizeof (*p));
    p->chave = k;
    p->esq = esq;
    p->dir = dir;
    p->pai = pai;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* aloca espaço para as variaveis globais "nodonull" e "raiz"                 */
/*----------------------------------------------------------------------------*/
void arvRN_inicializa (void){
    nodonull = arvRN_criaNodo (0, NULL, NULL, NULL);
    nodonull->cor = BLACK;
    raiz = nodonull;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Faz a rotacao a Esquerda                                                   */ 
/*----------------------------------------------------------------------------*/
Apontador arvRN_rotEsq (Apontador r, Apontador p) {
    Apontador y = p->dir;
    p->dir = y->esq;
    if (y->esq != nodonull)
        y->esq->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->esq = p;
    p->pai = y;
    return r;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Faz a rotacao a Direita                                                    */ 
/*----------------------------------------------------------------------------*/
Apontador arvRN_rotDir (Apontador r, Apontador p) {
    Apontador y = p->esq;
    p->esq = y->dir;
    if (y->dir != nodonull)
        y->dir->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->dir = p;
    p->pai = y;
    return r;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Ajusta as cores dos nodos apos uma inserçao                                */ 
/*----------------------------------------------------------------------------*/
Apontador  arvRN_arrumaInsere ( Apontador r, Apontador p ){
    Apontador tio;
    while (p->pai->cor == RED ) {
        if (p->pai == p->pai->pai->esq) {  /* insercao na subarv.esq */
            tio = p->pai->pai->dir;
            if (tio->cor == RED) {           /* cor a dir. do avo é  vermelho */
                p->pai->cor = BLACK;        /* Caso 1 */
                tio->cor = BLACK;
                p->pai->pai->cor = RED;
                p = p->pai->pai;
            }
            else {                       /* cor a dir. do avo é preto */
                if (p == p->pai->dir){        /* desbal. na subarv.dir do filho esq */
                    p = p->pai;               /* Caso 2: esq­dir */  
                    r = arvRN_rotEsq(r, p);
                }else {
                p->pai->cor = BLACK;        /* Caso 3  esq­esq*/
                p->pai->pai->cor = RED;
                r = arvRN_rotDir(r, p->pai->pai ); }
            }
        }
        else{  
            tio = p->pai->pai->esq;
            if (tio->cor == RED) {           /* cor a dir. do avo é  vermelho */
                p->pai->cor = BLACK;        /* Caso 1 */
                tio->cor = BLACK;
                p->pai->pai->cor = RED;
                p = p->pai->pai;
            }
            else {                       /* cor a dir. do avo é preto */
                if (p == p->pai->esq){        /* desbal. na subarv.dir do filho esq */
                    p = p->pai;               /* Caso 2: esq­dir */  
                    r = arvRN_rotDir(r, p);
                }else {
                p->pai->cor = BLACK;        /* Caso 3  esq­esq*/
                p->pai->pai->cor = RED;
                r = arvRN_rotEsq(r, p->pai->pai);}
            }
        } 
    }
    r->cor = BLACK;
    return r;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Insere uma chave na arvore RN                                              */
/*----------------------------------------------------------------------------*/ 
Apontador arvRN_insere (Apontador p, int k) {
    Apontador novo = arvRN_criaNodo (k, nodonull, nodonull, nodonull);

    Apontador x = p;
    Apontador paix = nodonull;

    while (x != nodonull){ //busca o pai do nodo novo
        paix = x;
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    novo->pai = paix;
    if (paix == nodonull) //arvore vazia
        p = novo;
    else if (k < paix->chave)
        paix->esq = novo;
    else 
        paix->dir = novo;
    novo->cor = RED;
    p =  arvRN_arrumaInsere (p, novo);
    return p;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Imprime a chave e sua cor com percurso em ordem                            */ 
/*----------------------------------------------------------------------------*/
void arvRN_imprimeEmOrdem (Apontador p) {
    if (p == nodonull)
        return;
    arvRN_imprimeEmOrdem (p->esq);
    if (p->cor == BLACK)
        printf ("Chave: %d | Cor: BLACK\n", p->chave);
    else
        printf ("Chave: %d | Cor: RED\n", p->chave);
    arvRN_imprimeEmOrdem (p->dir);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Imprime a chave e sua cor com percurso em pre-ordem                        */ 
/*----------------------------------------------------------------------------*/
void arvRN_imprimePreOrdem (Apontador p) {
    if (p == nodonull)
        return;
    if (p->cor == BLACK)
        printf ("Chave: %d | Cor: BLACK\n", p->chave);
    else
        printf ("Chave: %d | Cor: RED\n", p->chave);
    arvRN_imprimePreOrdem (p->esq);
    arvRN_imprimePreOrdem (p->dir);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Imprime a chave e sua cor com percurso em pos-ordem                        */ 
/*----------------------------------------------------------------------------*/
void arvRN_imprimePosOrdem (Apontador p) {
    if (p == nodonull)
        return;
    arvRN_imprimePosOrdem (p->esq);
    arvRN_imprimePosOrdem (p->dir);
    if (p->cor == BLACK)
        printf ("Chave: %d | Cor: BLACK\n", p->chave);
    else
        printf ("Chave: %d | Cor: RED\n", p->chave);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Encontra o nodo com a chave imediatamente maior que a chave do nodo p      */ 
/*----------------------------------------------------------------------------*/
Apontador arvRN_sucessor (Apontador p) {
    Apontador aux;
    if (p->dir == nodonull)
        return nodonull;
    aux = p->dir;
    while (aux->esq != nodonull){
        aux = aux->esq;
    }
    return aux;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Ajusta as cores dos nodos apos uma remoçao                                 */ 
/*----------------------------------------------------------------------------*/
void arvRN_arrumaRem (Apontador T, Apontador x) {
    Apontador w;
    while (x != T && x->cor == BLACK) {
        if (x == x->pai->esq) {
            w = x->pai->dir;
            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                arvRN_rotEsq (T, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == BLACK && w->dir->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            else if (w->dir->cor == BLACK){
                w->esq->cor = BLACK;
                w->cor = RED;
                arvRN_rotDir (T, w);
                w = x->pai->dir;
            }
            w->cor = x->pai->cor;
            x->pai->cor = BLACK;
            w->dir->cor = BLACK;
            arvRN_rotEsq (T, x->pai);
            x = T;
        }
        else {
            w = x->pai->esq;
            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                arvRN_rotDir (T, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == BLACK && w->esq->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            else if (w->esq->cor == BLACK){
                w->dir->cor = BLACK;
                w->cor = RED;
                arvRN_rotEsq (T, w);
                w = x->pai->esq;
            }
            w->cor = x->pai->cor;
            x->pai->cor = BLACK;
            w->esq->cor = BLACK;
            arvRN_rotDir (T, x->pai);
            x = T;
        }
    }
    x->cor = BLACK;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Remove um nodo da arvore RN                                                */ 
/*----------------------------------------------------------------------------*/
void arvRN_remove (Apontador r, Apontador nodok) { 
    Apontador nodoRem, filho;
    if (nodok == nodonull)
        return;
    if (nodok->esq == nodonull || nodok->dir == nodonull)
    /* se nodok tem 0 ou 1 filho, remove nodok */
        nodoRem = nodok;                               
    else                           /* senão remove o Sucessor */
        nodoRem = arvRN_sucessor (nodok); /* neste caso o nodoRem não tem filho esq */  
    if (nodoRem->esq != nodonull)
        filho = nodoRem->esq;
    else
        filho = nodoRem->dir;
    filho->pai = nodoRem->pai;
    if (nodoRem->pai == nodonull)
        r = filho;
    else if (nodoRem == nodoRem->pai->esq)
        nodoRem->pai->esq = filho;
    else
        nodoRem->pai->dir = filho;
    if (nodok != nodoRem) /* copia chave e dados do nodoRem para nodok */
        nodok->chave = nodoRem->chave;
    if (nodoRem == raiz){
        raiz = nodonull;
        return;
    }
    free(nodoRem);
    if (nodoRem->cor == BLACK)
        arvRN_arrumaRem (r, filho);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Busca o nodo que contem a chave k                                          */ 
/*----------------------------------------------------------------------------*/
Apontador arvRN_busca (Apontador p, int k) {
    if (p == nodonull)
        return nodonull;
    if (p->chave == k)        
        return p;
    else if (k < p->chave)
        return arvRN_busca (p->esq, k);
    else
        return arvRN_busca (p->dir, k);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
// desaloca todos os nodos exceto a raiz, que passa a apontar para nonull   
/*----------------------------------------------------------------------------*/
void arvRN_destroi (Apontador p) {
    if (p == nodonull)
        return;
    arvRN_destroi (p->esq);
    arvRN_destroi (p->dir);
    free (p);
}
/*----------------------------------------------------------------------------*/
