//
// Created by lumoreira on 29/03/20.
//

#include <iostream>

using namespace std;

typedef int Key;

typedef struct {
    Key key;
} Registry;

typedef struct el {
    Registry registry;
    struct el *next;
    struct el *previous;
} Element;

typedef struct {
    Element *head;
} Deck;

void init(Deck *d) {
    d->head = (Element *) malloc(sizeof(Element));
    d->head->next = d->head;
    d->head->previous = d->head;
}

int size(Deck *d) {
    Element *address = d->head->next;
    int size = 0;
    while (address != d->head) {
        size++;
        address = address->next;
    }
    return size;
}

void print(Deck *d) {
    Element *address = d->head->next;
    cout << "Deck " << endl;
    while (address != d->head) {
        cout << address->registry.key << endl;
        address = address->next;
    }
    cout << endl;
}

bool insertOnEnd(Deck *d, Registry r) {
    Element *address = (Element *) malloc(sizeof(Element));
    address->registry = r;

    address->next = d->head;
    address->previous = d->head->previous;
    d->head->previous = address;
    address->previous->next = address;
    return true;
}

bool removeFromStart(Deck *d, Registry *r) {
    if (d->head->next == d->head) return false;
    Element *toFree = d->head->next;
    *r = toFree->registry;

    d->head->next = toFree->next;
    toFree->next->previous = d->head;
    free(toFree);
    return true;
}

void reset(Deck *d) {

    Element *address = d->head->next;
    while (address != d->head) {
        Element *toFree = address;
        address = address->next;
        free(toFree);
    }

    d->head->next = d->head;
    d->head->previous = d->head;
}