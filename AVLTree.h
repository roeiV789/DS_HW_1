#pragma once
using namespace std;

template<class T, class K>
class AVLTree {
    struct Node {
        T data;
        K key;
        int height;
        Node *left;
        Node *right;

        Node(const T &data, const K &key);
    };

    void updateHeight(Node *node);

    T *searchAux(const Node *cur, const K &key) const;

    Node *insertAux(Node *node, const T &data, const K &key);

    int toArrayAux(Node *node, K *array, int index);

    auto rebalance(Node *node) -> Node *;

    Node *root;

    int n;

public:
    AVLTree();

    ~AVLTree();

    void insert(const T &data, const K &key);

    void deleteTree(Node *head);

    Node *rotateRight(Node *b);

    Node *rotateLR(Node *b);

    Node *rotateLeft(Node *b);

    Node *rotateRL(Node *b);

    int getBalance(Node *node) const;

    int getRoot() const;


    void toArray(K *array);

    T *search(const K &key) const;
};
