//
// Created by lumoreira on 29/03/20.
//

#include <iostream>

using namespace std;

#define MAX_SIZE 50

typedef int Key;

typedef struct {
    Key key;
} Registry;

typedef struct {
    Registry registry[MAX_SIZE];
    int firstIndex;
    int quantity;
} StaticQueue;

void init(StaticQueue *q) {
    q->firstIndex = 0;
    q->quantity = 0;
}

int size(StaticQueue *q) {
    return q->quantity;
}

void print(StaticQueue *q) {
    cout << "Static Queue " << endl;
    int i = q->firstIndex;
    int temp;
    for (temp = 0; temp < q->quantity; temp++) {
        cout << q->registry[i].key << endl;
        i = (i + 1) % MAX_SIZE;
    }
    cout << endl;
}

bool insert(StaticQueue *q, Registry r) {
    if (q->quantity >= MAX_SIZE) return false;
    int index = (q->firstIndex + q->quantity) % MAX_SIZE;
    q->registry[index] = r;
    q->quantity++;
    return true;
}

bool remove(StaticQueue *q, Registry *r) {
    if (q->quantity == 0) return false;
    *r = q->registry[q->firstIndex];
    q->firstIndex = (q->firstIndex + 1) % MAX_SIZE;
    q->quantity--;
    return true;
}

void reset(StaticQueue *q) {
    init(q);
}