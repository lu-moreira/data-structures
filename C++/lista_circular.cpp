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

typedef Element *Point;

typedef struct {
    Point head;
} CircularLinkedList;

void init(CircularLinkedList *l) {
    l->head = (Point) malloc(sizeof(Element));
    l->head->next = l->head;
}

int size(CircularLinkedList *l) {
    Point address = l->head->next;
    int size = 0;
    while (address != l->head) {
        size++;
        address = address->next;
    }
    return size;
}

void print(CircularLinkedList *l) {
    Point address = l->head->next;
    cout << "CircularLinkedList " << endl;
    while (address != l->head) {
        cout << address->r.key << endl;
        address = address->next;
    }
    cout << "\n" << endl;
}

Point searchBySentinel(CircularLinkedList *l, Key k) {
    Point address = l->head->next;
    l->head->r.key = k;
    while (address->r.key != k) {
        address = address->next;
    }

    if (address != l->head)
        return address;

    return nullptr;
}

Point sortedSearchBySentinel(CircularLinkedList *l, Key k) {
    Point address = l->head->next;
    l->head->r.key = k;
    while (address->r.key < k) {
        address = address->next;
    }

    if (address != l->head && address->r.key == k)
        return address;

    return nullptr;
}

Point linearSearch(CircularLinkedList *l, Key k) {
    Point address = l->head->next;
    while (address != l->head) {
        if (address->r.key == k)
            return address;
        address = address->next;
    }
    return nullptr;
}

Point linearSearchExc(CircularLinkedList *l, Key k, Point *previous) {
    *previous = l->head;
    Point actual = l->head->next;
    l->head->r.key = k;
    while (actual->r.key < k) {
        *previous = actual;
        actual = actual->next;
    }
    if (actual != l->head && actual->r.key == k) {
        return actual;
    }

    return nullptr;
}

bool sortedInsert(CircularLinkedList *l, Registry r) {
    Point previous, i;
    i = linearSearchExc(l, r.key, &previous);

    // we will not insert elements with the same key
    if (i != nullptr)
        return false;

    i = (Point) malloc(sizeof(Element));
    i->r = r;
    i->next = previous->next;
    previous->next = i;

    return true;
}

bool remove(CircularLinkedList *l, Key k) {
    Point previous, i;
    i = linearSearchExc(l, k, &previous);

    if (i == nullptr)
        return false;

    previous->next = i->next;
    free(i);

    return true;
}

void reset(CircularLinkedList *l) {
    Point address = l->head->next;
    while (address != l->head) {
        Point toFree = address;
        address = address->next;
        free(toFree);
    }
    l->head->next = l->head;
}