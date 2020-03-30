//
// Created by lumoreira on 29/03/20.
//

#include <iostream>

using namespace std;

typedef int Key;

typedef struct node {
    Key key;
    struct node *left, *right;
} Node, *Point;

Point init() {
    return nullptr;
}

Point createNode(Key k) {
    Point node = (Point) malloc(sizeof(Node));
    node->key = k;
    node->right = nullptr;
    node->left = nullptr;
    return node;
}

Point insert(Point root, Point node) {
    if (root == nullptr)
        return node;

    if (root->key < node->key)
        root->left = insert(root->left, node);
    else
        root->right = insert(root->right, node);

    return root;
}

// recursive search, consumes much memory
Point search(Point root, Key k) {
    if (root == nullptr) return nullptr;
    if (root->key == k) return root;
    if (root->key < k) {
        return search(root->right, k);
    }
    return search(root->left, k);
}

int size(Point root) {
    return !root ? 0 : size(root->left) + 1 + size(root->right);
}

void print(Point root) {
    if (root == nullptr) {
        return;
    }

    cout << root->key << "(";
    print(root->left);
    print(root->right);
    cout << ")" << endl;
}

Point searchNode(Point root, Key k, Point *rootOfResultNode) {
    Point actual = root;
    *rootOfResultNode = nullptr;
    while (actual) {
        if (actual->key == k) {
            return actual;
        }
        *rootOfResultNode = actual;
        if (k < actual->key) {
            actual = actual->left;
        } else {
            actual = actual->right;
        }
    }
    return nullptr;
}

Point removeNode(Point raiz, Key k) {
    // q é o promovido
    Point pai, no, p, q;
    no = searchNode(raiz, k, &pai);

    if (no == nullptr) return raiz;

    if (!no->left || !no->right) {
        // quando tem 1 filho
        if (!no->left) {
            q = no->right;
        }else{
            q = no->left;
        }
    }else {
        // quando tem 2 filhos
        p = no;
        q = no->left;
        while(q->right) {
            p = q;
            q = q->right;
        }

        if (p != no) {
            p->right = q->left;
            q->left = no->left;
        }
    }

    if (!pai){
        free(no);
        return q;
    }

    if (k < pai->key) {
        pai->left = q;
    } else {
        pai->right = q;
    }

    free(no);
    return raiz;
}