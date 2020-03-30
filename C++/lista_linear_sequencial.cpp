//
// Created by lumoreira on 28/03/20.
//
/*
 * Lista Linear Sequencial
 */


#include <iostream>

#define MAX 50

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX + 1]; // Arranjo de registros // esse +1 seria para poder armazenar o sentinela.
    int count;
} LISTA;

void inicializaLista(LISTA *l) {
    l->count = 0;
}

void reinicializaLista(LISTA *l) {
    l->count = 0;
}

int count(LISTA *l) {
    return l->count;
}

void printLista(LISTA *l) {
    int i;
    printf("Lista: ");
    for (i = 0; i < l->count; i++) {
        printf(" %d ", l->A[i].chave);
    }
}

// indexOf()
int buscaSequencial(LISTA *l, TIPOCHAVE ch) {
    int i = 0;
    while (i < l->count) {
        if (ch == l->A[i].chave) return i;
        else i++;
    }
    return -1;
}

bool insert(LISTA *l, REGISTRO r, int index) {
    int j;
    if ((l->count == MAX) || (index < 0) || (index > l->count)) {
        return false;
    }

    for (j = l->count; j > index; j--) {
        l->A[j] = l->A[j - 1];
    }

    l->A[index] = r;
    l->count++;
    return true;
}

bool deleteElem(LISTA *l, TIPOCHAVE ch) {
    int pos, j;
    pos = buscaSequencial(l, ch);
    if (pos == -1) {
        return false;
    }

    for (j = pos; j < l->count; j++)
        l->A[j] = l->A[j + 1];

    l->count--;
    return true;
}

// useful for binarySearch
bool insertAndSort(LISTA *l, REGISTRO r) {
    if (l->count == MAX) return false;

    int pos = l->count;
    while (pos > 0 && l->A[pos - 1].chave > r.chave) {
        l->A[pos] = l->A[pos - 1];
        pos--;
    }
    l->A[pos] = r;
    l->count++;

    return true;
}

// sentinela???
int buscaSentinela(LISTA *l, TIPOCHAVE ch) {
    int i = 0;
    l->A[l->count].chave = ch;
    while (l->A[i].chave != ch) i++;
    if (i == l->count) return -1;
    return i;
}

int binarySearch(LISTA *l, TIPOCHAVE ch) {
    int left, right, middle;
    left = 0;
    right = l->count - 1;
    while (left <= right) {
        middle = ((left + right) / 2);
        if (l->A[middle].chave == ch) return middle;
        else {
            if (l->A[middle].chave < ch) left = middle + 1;
            else right = middle - 1;
        }
    }
    return -1;
}