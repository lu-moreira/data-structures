//
// Created by lumoreira on 28/03/20.
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
    Point start;
} DynamicLinkedList;

void init(DynamicLinkedList *l) {
    l->start = nullptr;
}

int size(DynamicLinkedList *l) {
    Point address = l->start;
    int size = 0;
    while (address != nullptr) {
        size++;
        address = address->next;
    }
    return size;
}

void print(DynamicLinkedList *l) {
    Point address = l->start;
    cout << "DynamicLinkedList " << endl;
    while (address != nullptr) {
        cout << address->r.key << endl;
        address = address->next;
    }
    cout << "\n" << endl;
}

Point linearSearch(DynamicLinkedList *l, Key k) {
    Point address = l->start;
    while (address != nullptr) {
        if (address->r.key == k)
            return address;
        address = address->next;
    }
    return nullptr;
}

Point sortedLinearSearch(DynamicLinkedList *l, Key k) {
    Point address = l->start;
    while (address != nullptr && address->r.key < k) {
        address = address->next;
    }
    if (address != nullptr && address->r.key == k) {
        return address;
    }
    return nullptr;
}

Point linearSearchExc(DynamicLinkedList *l, Key k, Point *previous) {
    *previous = nullptr;
    Point actual = l->start;
    while (actual != nullptr && actual->r.key < k) {
        *previous = actual;
        actual = actual->next;
    }
    if (actual != nullptr && actual->r.key == k) {
        return actual;
    }

    return nullptr;
}

bool sortedInsert(DynamicLinkedList *l, Registry r) {
    Key k = r.key;
    Point previous, i;
    i = linearSearchExc(l, k, &previous);

    // we will not insert elements with the same key
    if (i != nullptr)
        return false;

    i = (Point) malloc(sizeof(Element));
    i->r = r;
    if (previous == nullptr) {
        i->next = l->start;
        l->start = i;
    } else {
        i->next = previous->next;
        previous->next = i;
    }

    return true;
}

bool remove(DynamicLinkedList *l, Key k) {
    Point previous, i;
    i = linearSearchExc(l, k, &previous);

    if (i == nullptr)
        return false;

    if (previous == nullptr)
        l->start = i->next;
    else
        previous->next = i->next;

    free(i);
    return true;
}

void reset(DynamicLinkedList *l) {
    Point address = l->start;
    while (address != nullptr) {
        Point toFree = address;
        address = address->next;
        free(toFree);
    }
    l->start = nullptr;
}