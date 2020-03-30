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
    int top;
} StaticStack;

void init(StaticStack *s) {
    s->top = -1;
};

int size(StaticStack *s) {
    return s->top + 1;
}

void print(StaticStack *s) {
    cout << "Static Stack " << endl;
    for (int i = s->top; i >= 0; i++) {
        cout << s->registry[i].key << endl;
    }
    cout << "\n" << endl;
}

bool push(StaticStack *s, Registry r) {
    if (s->top >= MAX_SIZE - 1)
        return false;

    s->top = s->top + 1;
    s->registry[s->top] = r;
    return true;
}

bool pop(StaticStack *s, Registry *r) {
    if (s->top == -1)
        return false;

    *r = s->registry[s->top];
    s->top = s->top - 1;
    return true;
}

void reset(StaticStack *s) {
    s->top = -1;
}


