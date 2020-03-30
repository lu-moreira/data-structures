//
// Created by lumoreira on 29/03/20.
//

#include <iostream>

using namespace std;

typedef int Key;

typedef struct {
    Key key;
} Registry;

typedef struct aux {
    Registry r;
    struct aux *next;
} Element;

typedef struct {
    Element *top;
} DynamicStack;

void init(DynamicStack *s) {
    s->top = nullptr;
};

int size(DynamicStack *s) {
    int size = 0;
    Element *address = s->top;
    while (address != nullptr) {
        size++;
        address = address->next;
    }
    return size;
}

bool isEmpty(DynamicStack *s) {
    return s->top == nullptr;
}

void print(DynamicStack *s) {
    cout << "Dynamic Stack " << endl;

    Element *address = s->top;
    while (address != nullptr) {
        cout << address->r.key << endl;
        address = address->next;
    }

    cout << "\n" << endl;
}

bool push(DynamicStack *s, Registry r) {
    Element *n = (Element *) malloc(sizeof(Element));
    n->r = r;
    n->next = s->top;
    s->top = n;
    return true;
}

bool pop(DynamicStack *s, Registry *r) {
    if (s->top == nullptr)
        return false;

    *r = s->top->r;

    Element *toFree = s->top;
    s->top = s->top->next;
    free(toFree);

    return true;
}

void reset(DynamicStack *s) {
    Element *toFree;
    Element *address = s->top;
    while (address != nullptr) {
        toFree = address;
        address = address->next;
        free(toFree);
    }
    s->top = nullptr;
}


