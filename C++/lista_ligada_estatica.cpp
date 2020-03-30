//
// Created by lumoreira on 28/03/20.
//
#include <iostream>

#define MAX 50
#define INVALID -1

using namespace std;

typedef int TypeKey;

typedef struct {
    TypeKey key;
} Registry;

typedef struct {
    Registry r;
    int next;
} Element;

typedef struct {
    Element el[MAX];
    int start;
    int firstElementAvailable;
} LinkedList;

void init(LinkedList *l) {
    for (int i = 0; i < MAX - 1; ++i) {
        l->el[i].next = i + 1;
    }
    l->el[MAX - 1].next = INVALID;
    l->start = INVALID;
    l->firstElementAvailable = 0;
}

void reInit(LinkedList *l) {
    init(l);
}

int size(LinkedList *l) {
    int i = l->start;
    int size = 0;
    while (i != INVALID) {
        size++;
        i = l->el[i].next;
    }
    return size;
}

void print(LinkedList *l) {
    int i = l->start;
    cout << "LinkedList: " << endl;
    while (i != INVALID) {
        cout << l->el[i].r.key << endl;
        i = l->el[i].next;
    }
    cout << "\n" << endl;
}

int sortedLinearSearch(LinkedList *l, TypeKey key) {
    int i = l->start;
    while (i != INVALID && l->el[i].r.key < key)
        i = l->el[i].next;

    if (i != INVALID && l->el[i].r.key == key)
        return i;

    return INVALID;
}

int getEl(LinkedList *l) {
    int result = l->firstElementAvailable;
    if (l->firstElementAvailable != INVALID) {
        l->firstElementAvailable = l->el[l->firstElementAvailable].next;
    }
    return result;
}

void returnEl(LinkedList *l, int i) {
    l->el[i].next = l->firstElementAvailable;
    l->firstElementAvailable = i;
}

bool sortedAdd(LinkedList *l, Registry r) {
    if (l->firstElementAvailable == INVALID) return false;
    int previous = INVALID;
    int i = l->start;
    TypeKey k = r.key;
    while ((i != INVALID) && (l->el[i].r.key < k)) {
        previous = i;
        i = l->el[i].next;
    }

    // if is duplicated key, we don't insert
    if (i != INVALID && l->el[i].r.key == k) return false;

    i = getEl(l);
    l->el[i].r = r;

    if (previous == INVALID) {
        l->el[i].next = l->start;
        l->start = i;
    } else {
        l->el[i].next = l->el[previous].next;
        l->el[previous].next = i;
    }
    return true;
}

bool remove(LinkedList *l, TypeKey k) {
    int previous = INVALID;
    int i = l->start;
    while ((i != INVALID) && (l->el[i].r.key < k)) {
        previous = i;
        i = l->el[i].next;
    }

    if (i == INVALID || l->el[i].r.key != k) {
        return false;
    }

    if (previous == INVALID) {
        l->start = l->el[i].next;
    } else {
        l->el[previous].next = l->el[i].next;
    }

    returnEl(l, i);

    return true;
}

