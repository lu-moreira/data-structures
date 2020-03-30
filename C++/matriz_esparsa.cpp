//
// Created by lumoreira on 29/03/20.
//

#include <iostream>

using namespace std;

typedef struct tempNode {
    float value;
    int column;
    struct tempNode *next;
} Node, *Point;

typedef struct {
    Point *a;
    int lines;
    int columns;
} SparceMatrix;

void init(SparceMatrix *matrix, int l, int c) {
    matrix->lines = l;
    matrix->columns = c;

    matrix->a = (Point *) malloc(l * sizeof(Point));

    for (int i = 0; i < l; ++i) {
        matrix->a[i] = nullptr;
    }
}

bool insert(SparceMatrix *matrix, int l, int c, float v) {
    if (l < 0 || l >= matrix->lines || c < 0 || c >= matrix->columns) {
        return false;
    }

    Point ant = nullptr;
    Point actual = matrix->a[l];

    // search
    while (actual != nullptr && actual->column < c) {
        ant = actual;
        actual = actual->next;
    }

    // quando já existe dado, necessario atualizar
    if (actual != nullptr && actual->column == c) {
        // should remove it
        if (v == 0) {

            // é xq estamos no primeiro item
            if (ant == nullptr) {
                matrix->a[l] = actual->next;
            } else {
                ant->next = actual->next;
            }
            free(actual);
        } else {
            actual->value = v;
        }
    } else {
        Point n = (Point) malloc(sizeof(Node));
        n->column = c;
        n->value = v;
        n->next = actual;

        if (ant == nullptr) {
            matrix->a[l] = n;
        } else {
            ant->next = n;
        }
    }

    return true;
}

float find(SparceMatrix *matrix, int l, int c) {
    if (l < 0 || l >= matrix->lines || c < 0 || c >= matrix->columns) {
        return 0;
    }

    Point actual = matrix->a[l];
    while (actual != nullptr && actual->column < c) {
        actual = actual->next;
    }

    if (actual != nullptr && actual->column == c) {
        return actual->value;
    }
    return 0;
}
