#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int BOOL;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    // cabeca da lista
    int Key;
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

void profundidade(GRAFO *g) {
    int cor[g->vertices];
    int u;
    for (u = 0; g->vertices; u++) {
        cor[u] = BRANCO;
    }
    for (u = 0; g->vertices; u++) {
        // reinicio
        // visita em profundidade
        if (cor[u] == BRANCO)
            visitaP(g, u, cor);
    }
}

// assim percorre o grafo
void visitaP(GRAFO *g, int u, int *cor) {
    cor[u] = AMARELO;
    ADJACENCIA *v = g->adj[u].cab;
    while (v)
    {
        // somente os vertices nao visitados
        if (cor[v->vertice] == BRANCO)
            visitaP(g, v->vertice, cor);
        v = v->prox;
    }
    cor[u] = VERMELHO;    
}

// busca em profundidade
void buscaEmProfundidade(GRAFO *g, int u, int *cor, int key) {
    cor[u] = AMARELO;
    ADJACENCIA *v = g->adj[u].cab;
    if (g->adj[u].Key == key) {
    }

    while (v)
    {
        // somente os vertices nao visitados
        if (cor[v->vertice] == BRANCO)
            buscaEmProfundidade(g, v->vertice, cor, key);
        v = v->prox;
    }
    cor[u] = VERMELHO;    
}


