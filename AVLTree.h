#pragma once
#include <algorithm>
#include <cmath>

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

    int toArray(Node *array);

    Node *removeAux(Node *node, const K &key);

    int toArrayAux(Node *node, K *array, int index);

    auto rebalance(Node *node) -> Node *;

    Node *root;
    int n;

public:
    AVLTree();

    ~AVLTree();

    void merge(const AVLTree &another);

    void remove(const K &key);

    void insert(const T &data, const K &key);

    void deleteTree(Node *head);

    Node *rotateRight(Node *b);

    Node *rotateLR(Node *b);

    Node *rotateLeft(Node *b);

    Node *rotateRL(Node *b);

    int getBalance(Node *node) const;

    Node *getRoot() const;

    int toArrayAux(Node *node, Node *array, int index);

    int toArray(K *array);

    T *search(const K &key) const;

    int getSize() const;
};

template<class T, class K>
AVLTree<T, K>::Node::Node(const T &data, const K &key)
    : data(data), key(key), height(1), left(nullptr),
      right(nullptr) {
}

template<class T, class K>
void AVLTree<T, K>::updateHeight(Node *node) {
    int currHeight = 0;
    if (node->left != nullptr)
        currHeight = node->left->height;
    if (node->right != nullptr && node->right->height > currHeight)
        currHeight = node->right->height;
    node->height = 1 + currHeight;
}


template<class T, class K>
AVLTree<T, K>::AVLTree() : root(nullptr) {
}

template<class T, class K>
AVLTree<T, K>::~AVLTree() {
    deleteTree(root);
    root = nullptr;
}

template<class T, class K>
void AVLTree<T, K>::insert(const T &data, const K &key) {
    // increase node counter
    ++(this->n);
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
int AVLTree<T, K>::toArray(Node *array) {
    return toArrayAux(root, array, 0);
}

template<class T, class K>
int AVLTree<T, K>::toArrayAux(Node *node, Node *array, int index) {
    if (node == nullptr) {
        return index;
    }
    index = toArrayAux(node->left, array, index);
    array[index++] = Node(node->data, node->key);
    index = toArrayAux(node->right, array, index);
    return index;
}

// as this function is primarily used for testing, it's ok to skip checking if the array is big enough
template<class T, class K>
int AVLTree<T, K>::toArray(K *array) {
    return toArrayAux(root, array, 0);
}

template<class T, class K>
int AVLTree<T, K>::toArrayAux(Node *node, K *array, int index) {
    if (node == nullptr) {
        return index;
    }
    index = toArrayAux(node->left, array, index);
    array[index++] = node->key;
    index = toArrayAux(node->right, array, index);
    return index;
}

template<class T, class K>
auto AVLTree<T, K>::rebalance(Node *node) -> Node * {
    int balance = getBalance(node);

    // where is the problem?
    // Left
    if (balance > 1) {
        // Right
        if (getBalance(node->left) < 0)
            return rotateLR(node);
        // or Left
        return rotateRight(node);
    }

    // Right
    if (balance < -1) {
        // Left
        if (getBalance(node->right) > 0)
            return rotateRL(node);
        // or Right
        return rotateLeft(node);
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
typename AVLTree<T, K>::Node *AVLTree<T, K>::rotateRight(Node *b) {
    Node *a = b->left;
    b->left = a->right;
    a->right = b;
    updateHeight(b);
    updateHeight(a);

    return a;
}

template<class T, class K>
auto AVLTree<T, K>::rotateLR(Node *b) -> Node * {
    b->left = rotateLeft(b->left);
    return rotateRight(b);
}

template<class T, class K>
typename AVLTree<T, K>::Node *AVLTree<T, K>::rotateLeft(Node *b) {
    Node *a = b->right;
    b->right = a->left;
    a->left = b;
    updateHeight(b);
    updateHeight(a);

    return a;
}

template<class T, class K>
typename AVLTree<T, K>::Node *AVLTree<T, K>::rotateRL(Node *b) {
    b->right = rotateRight(b->right);
    return rotateLeft(b);
}

template<class T, class K>
int AVLTree<T, K>::getBalance(Node *node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

template<class T, class K>
typename AVLTree<T, K>::Node *AVLTree<T, K>::getRoot() const {
    return root;
}

template<class T, class K>
T *AVLTree<T, K>::search(const K &key) const {
    return searchAux(root, key);
}

template<class T, class K>
int AVLTree<T, K>::getSize() const {
    return n;
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

template<class T, class K>
void AVLTree<T, K>::remove(const K &key) {
    if (root != nullptr) {
        root = removeAux(root, key);
    }
}

template<class T, class K>
auto AVLTree<T, K>::removeAux(Node *node, const K &key) -> Node * {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        // decrease node counter
        --(this->n);
        //leaf case
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        //one left son
        if (!node->right) {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        //one right son
        if (!node->left) {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        //two sons case - getting min node in tree
        Node *temp = node->right;
        while (temp->left) {
            temp = temp->left;
        }
        node->key = temp->key;
        node->data = temp->data;
        node->right = removeAux(node->right, temp->key);
    } else if (key < node->key) {
        node->left = removeAux(node->left, key);
    } else {
        node->right = removeAux(node->right, key);
    }
    updateHeight(node);
    return rebalance(node);
}

template<class T, class K>
void AVLTree<T, K>::merge(const AVLTree &another) {
    // WIP! NOT FINISHED!!
    Node *thisArr = new Node[this->getSize()];
    Node *anotherArr = new Node[another.getSize()];
    Node *result = new Node[this->getSize() + another.getSize()];
    // toArray returns a sorted array as it traverses inorder
    this->toArray(thisArr);
    another.toArray(anotherArr);
    Array(anotherArr);
    int i = 0, j = 0;
    int resIndex = 0;
    while (i < this->getSize() && j < another.getSize()) {
        if (thisArr[i].key < anotherArr[j].key) {
            result[resIndex++] = thisArr[i++];
        } else if (thisArr[i].key > anotherArr[j].key) {
            result[resIndex++] = anotherArr[j++];
        } else {
            result[resIndex++] = thisArr[i++];
            j++;
        }
    }

    if (i < this->getSize()) {
        while (i < this->getSize()) {
            result[resIndex++] = thisArr[i++];
        }
    } else if (j < another.getSize()) {
        while (j < another.getSize()) {
            result[resIndex++] = anotherArr[j++];
        }
    }
}
