#pragma once
#include "AVLTree.h"
using namespace std;

template<class T, class K>
AVLTree<T, K>::Node::Node(const T &data, const K &key)
    : data(data), key(key), height(1), father(nullptr), left(nullptr),
      right(nullptr) {
}

template<class T, class K>
void AVLTree<T, K>::updateHeight(Node *node) {
    node->height = 1 + max(node->left->height, node->right->height);
}


template<class T, class K>
AVLTree<T, K>::AVLTree() : root(nullptr) {
}

template<class T, class K>
AVLTree<T, K>::~AVLTree() {
    AVLTree *temp = root;
    deleteTree(temp);
    root = nullptr;
}

template<class T, class K>
void AVLTree<T, K>::deleteTree(Node *head) {
    if (head == nullptr) {
        return;
    }
    deleteTree(head->left);
    deleteTree(head->right);
    delete head;
}

template<class T, class K>
typename AVLTree<T, K>::Node *AVLTree<T, K>::rotateRight(Node *b) {
    Node *a = b->left;
    b->left = a->right;
    a->right = b;
    updateHeight(a);
    updateHeight(b);

    return a;
}

template<class T, class K>
typename AVLTree<T, K>::Node *AVLTree<T, K>::rotateLR(Node *b) {
    b->left = rotateLeft(b->left);
    return rotateRight(b);
}

template<class T, class K>
int AVLTree<T, K>::getBalance(Node *node) const {
    return node->left->height - node->right->height;
}

template<class T, class K>
int AVLTree<T, K>::getRoot() const {
    return root;
}

template<class T, class K>
T *AVLTree<T, K>::search(const K &key) const {
    return searchAux(root, key);
}

template<class T, class K>
T *AVLTree<T, K>::searchAux(Node *cur, const K &key) const {
    if (cur == nullptr) {
        return nullptr;
    }
    if (cur->key == key) {
        return cur->data;
    }
    if (key < cur->key) {
        return searchAux(cur->left, key);
    }
    return searchAux(cur->right, key);
}
