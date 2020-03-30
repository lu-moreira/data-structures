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
} Element, *Point;

typedef struct {
    Point start;
    Point end;
} DynamicQueue;

void init(DynamicQueue *d) {
    d->start = nullptr;
    d->end = nullptr;
}

int size(DynamicQueue *d) {
    int size = 0;
    Point address = d->start;
    while (address != nullptr) {
        size++;
        address = address->next;
    }
    return size;
}

void reset(DynamicQueue *d) {
    Point address = d->start;
    while (address != nullptr) {
        Point toFree = address;
        address = address->next;
        free(toFree);
    }
    init(d);
}

void print(DynamicQueue *d) {
    cout << "Dynamic Queue " << endl;
    Point address = d->start;
    while (address != nullptr) {
        cout << address->r.key << endl;
        address = address->next;
    }
    cout << endl;
}

// insert is on the end
bool insert(DynamicQueue *q, Registry r) {
    Point el = (Point) malloc(sizeof(Element));
    el->r = r;
    el->next = nullptr;

    if (q->start == nullptr)
        q->start = el;
    else
        q->end->next = el;

    q->end = el;

    return true;
}

// remove is on the start
bool remove(DynamicQueue *q, Registry *r) {
    if (q->start == nullptr)
        return false;

    *r = q->start->r;

    Point toFree = q->start;
    q->start = q->start->next;
    free(toFree);

    if (q->start == nullptr)
        q->end = nullptr;

    return true;
}