#pragma once
using namespace std;

template<class T, class K>
class AVLTree {
    struct Node {
        T data;
        K key;
        int height;
        Node *father;
        Node *left;
        Node *right;

        Node(const T &data, const K &key);
    };

    void updateHeight(Node *node);

    Node *root;

public:
    AVLTree();

    ~AVLTree();

    void deleteTree(Node *head);

    Node *rotateRight(Node *b);

    Node *rotateLR(Node *b);

    Node *rotateLeft(Node *b);

    Node *rotateRL(Node *b);

    int getBalance(Node *node) const;

    int getRoot() const;

    T *search(const K &key) const;

    T *searchAux(Node *cur, const K &key) const;
};
