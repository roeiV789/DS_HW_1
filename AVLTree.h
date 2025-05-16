#pragma once
using namespace std;

template<class T, class K>
class AVLTree {
    struct Node {
        T data;
        K key;
        int height;
        Node* father;
        Node *left;
        Node *right;

        Node(const T &data, const K& key) : data(data), key(key), height(1), father(nullptr), left(nullptr), right(nullptr) {
        }
    };

    void updateHeight(Node *node) {
        node->height = 1 + max(node->left->height, node->right->height);
    }

    Node *root;

public:
    AVLTree() : root(nullptr) {
    }

    ~AVLTree() {
        AVLTree *temp = root;
        deleteTree(temp);
        root = nullptr;
    }

    void deleteTree(Node *head) {
        if (head == nullptr) {
            return;
        }
        deleteTree(head->left);
        deleteTree(head->right);
        delete head;
    }

    Node* rotateRight(Node* b) {
        Node* a = b->left;
        b->left = a->right;
        a->right = b;
        updateHeight(a);
        updateHeight(b);

        return a;
    }

    Node* rotateLR(Node* b) {
        b->left = rotateLeft(b->left);
        return rotateRight(b);
    }
    int getBalance(Node* node) const {
        return node->left->height - node->right->height;
    }
    int getRoot() const {
        return root;
    }

    T* search(const K& key) const{
        return searchAux(root,key);
    }
    T* searchAux(Node* cur, const K& key) const {
        if(cur == nullptr) {
            return nullptr;
        }
        if(cur->key == key) {
            return cur->data;
        }
        if(key < cur->key) {
            return searchAux(cur->left, key);
        }
        return searchAux(cur->right, key);
    }

};