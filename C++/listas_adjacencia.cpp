#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int BOOL;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    // cabeca da lista
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

GRAFO *criaGrafo(int v) {
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *) malloc(v*sizeof(VERTICE));

    int i;
    for ( i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    
    return(g);
}

ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return(temp);
}

// Cria Aresta dirigida, mas como é uma função geral, pode-se utilizar 2 vezes para grafos não dirigidos
BOOL criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
    if (!gr) 
        return(false);
    if ((vf<0)|| (vf >= gr->vertices)) 
        return(false);
    if ((vi < 0)|| (vi >= gr->vertices))
        return(false);

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return(true);
}

void imprime(GRAFO *gr) {
    printf("Vertices: %d, Arestas: %d.\n", gr->vertices, gr->arestas);
    int i;
    for ( i = 0; i < gr->vertices; i++)
    {
        printf("v%d ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad) {
            printf("---%d---> v%d ", ad->peso, ad->vertice);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int main(void) {
    GRAFO *gr = criaGrafo(5);

    criaAresta(gr, 0, 1, 2);
    criaAresta(gr, 1, 0, 2);
    criaAresta(gr, 1, 2, 4);
    criaAresta(gr, 2, 1, 4);
    criaAresta(gr, 2, 0, 12);
    criaAresta(gr, 0, 2, 12);    
    criaAresta(gr, 2, 4, 40);
    criaAresta(gr, 4, 2, 40);
    criaAresta(gr, 3, 1, 3);
    criaAresta(gr, 3, 1, 3);
    criaAresta(gr, 4, 3, 8);
    criaAresta(gr, 3, 4, 8);

    imprime(gr);
}