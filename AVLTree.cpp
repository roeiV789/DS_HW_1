#pragma once
#include "AVLTree.h"

#include <stdexcept>
using namespace std;

template<class T, class K>
AVLTree<T, K>::Node::Node(const T &data, const K &key)
    : data(data), key(key), height(1), left(nullptr),
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
void AVLTree<T, K>::insert(const T &data, const K &key) {
    if (root == nullptr) {
        root = new Node(data, key);
        return;
    }

    root = insertAux(root, data, key);
}


template<class T, class K>
auto AVLTree<T, K>::insertAux(Node *node, const T &data, const K &key) -> Node * {
    if (node == nullptr) {
        return new Node(data, key);
    }
    if (key < node->key) {
        node->left = insertAux(node->left, data, key);
    } else {
        node->right = insertAux(node->right, data, key);
    }
    updateHeight(node);
    return rebalance(node);
}

template<class T, class K>
auto AVLTree<T, K>::rebalance(Node *node) -> Node * {
    int balance = getBalance(node);

    // Left
    if (balance > 1)
        // Right
        if (getBalance(node->left) < 0) {
            return rotateLR(node);
            // else Left
            return rotateLeft(node);
        }

    // Right
    if (balance < -1) {
        // Left
        if (getBalance(node->right) > 0) {
            return rotateRL(node);
            // else Right
            return rotateRight(node);
        }
    }

    return node;
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
auto AVLTree<T, K>::rotateLeft(Node *b) -> Node * {
    Node *a = b->right;
    b->right = a->left;
    a->left = b;
    updateHeight(a);
    updateHeight(b);

    return a;
}

template<class T, class K>
auto AVLTree<T, K>::rotateRight(Node *b) -> Node * {
    Node *a = b->left;
    b->left = a->right;
    a->right = b;
    updateHeight(a);
    updateHeight(b);

    return a;
}

template<class T, class K>
auto AVLTree<T, K>::rotateLR(Node *b) -> Node * {
    b->left = rotateLeft(b->left);
    return rotateRight(b);
}

template<class T, class K>
auto AVLTree<T, K>::rotateRL(Node *b) -> Node * {
    b->right = rotateRight(b->right);
    return rotateLeft(b);
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
T *AVLTree<T, K>::searchAux(const Node *cur, const K &key) const {
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
