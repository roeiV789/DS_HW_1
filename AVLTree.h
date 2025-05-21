#pragma once


template<class T, class K>
class AVLTree {
public:
    struct Node {
        T data;
        K key;
        int height;
        Node *left;
        Node *right;

        Node(const T &data, const K &key);

        Node() = default;
    };

    AVLTree();

    void recreateFromArray(const Node *data_raw, int data_size);

    ~AVLTree();

    bool found(const K &key) const;

    void mergeToArray(const AVLTree &another, Node *destination) const;

    void remove(const K &key);

    void insert(const T &data, const K &key);

    void deleteTree(Node *head);

    Node *rotateRight(Node *b);

    Node *rotateLR(Node *b);

    Node *rotateLeft(Node *b);

    Node *rotateRL(Node *b);

    int getBalance(Node *node) const;

    Node *getRoot() const;

    int toArray(Node *array) const;

    int toArray(K *array) const;

    T search(const K &key, bool &found) const;

    int getSize() const;

    //function returns the father of the node with the key or the last node that isnt null in the search route
    T findGreaterOrEqual(const K &key, bool &found) const;

private:
    void updateHeight(Node *node);

    T searchAux(const Node *cur, const K &key, bool &found) const;

    Node *insertAux(Node *node, const T &data, const K &key);

    Node *removeAux(Node *node, const K &key);

    int toArrayAux(Node *node, Node *array, int index) const;

    int toArrayAux(Node *node, K *array, int index) const;

    auto rebalance(Node *node) -> Node *;

    Node *createFromArrayAux(Node *curr, const Node *data, int begin, int end);

    auto findGreaterOrEqualAux(const K &key, Node *current, Node *closest) const -> Node *;

    Node *root;
    int n;
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
AVLTree<T, K>::AVLTree() : root(nullptr), n(0) {
}

template<class T, class K>
void AVLTree<T, K>::recreateFromArray(const Node *data, int size) {
    if (data == nullptr || size <= 0)
        throw std::logic_error("this should not happen");
    deleteTree(root);
    this->n = size;
    root = createFromArrayAux(root, data, 0, size - 1);
    delete[] data;
}

template<class T, class K>
auto AVLTree<T, K>::createFromArrayAux(Node *curr, const Node *data, int begin, int end) -> Node * {
    int mid = (begin + end) / 2;
    curr = new Node(data[mid].data, data[mid].key);
    if (begin < mid) {
        curr->left = createFromArrayAux(curr->left, data, begin, mid - 1);
    }
    if (mid < end) {
        curr->right = createFromArrayAux(curr->right, data, mid + 1, end);
    }
    updateHeight(curr);
    return curr;
}

template<class T, class K>
AVLTree<T, K>::~AVLTree() {
    deleteTree(root);
    root = nullptr;
}

template<class T, class K>
bool AVLTree<T, K>::found(const K &key) const {
    bool found;
    searchAux(root, key, found);
    return found;
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
int AVLTree<T, K>::toArray(Node *array) const {
    return toArrayAux(root, array, 0);
}

template<class T, class K>
int AVLTree<T, K>::toArrayAux(Node *node, Node *array, int index) const {
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
int AVLTree<T, K>::toArray(K *array) const {
    return toArrayAux(root, array, 0);
}

template<class T, class K>
int AVLTree<T, K>::toArrayAux(Node *node, K *array, int index) const {
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
    head->left = nullptr;
    head->right = nullptr;
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
int AVLTree<T, K>::getSize() const {
    return n;
}

template<class T, class K>
T AVLTree<T, K>::search(const K &key, bool &found) const {
    return searchAux(root, key, found);
}

template<class T, class K>
T AVLTree<T, K>::searchAux(const Node *cur, const K &key, bool &found) const {
    if (cur == nullptr) {
        found = false;
        return T();
    }
    if (cur->key == key) {
        found = true;
        return cur->data;
    }
    if (key < cur->key) {
        return searchAux(cur->left, key, found);
    }
    return searchAux(cur->right, key, found);
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

// this function modifies destination to be a SORTED array of UNIQUE elements.
// it modifies first n(this) + n(another) elements of destination and leaves rest of the elements unchanged
template<class T, class K>
void AVLTree<T, K>::mergeToArray(const AVLTree &another, Node *destination) const {
    Node *thisArr = new Node[this->getSize()];
    Node *anotherArr = new Node[another.getSize()];
    // toArray returns a sorted array as it traverses inorder
    this->toArray(thisArr);
    another.toArray(anotherArr);
    int i = 0, j = 0;
    int resIndex = 0;
    while (i < this->getSize() && j < another.getSize()) {
        if (thisArr[i].key < anotherArr[j].key) {
            destination[resIndex++] = thisArr[i++];
        } else if (thisArr[i].key > anotherArr[j].key) {
            destination[resIndex++] = anotherArr[j++];
        } else {
            destination[resIndex++] = thisArr[i++];
            j++;
        }
    }

    if (i < this->getSize()) {
        while (i < this->getSize()) {
            destination[resIndex++] = thisArr[i++];
        }
    } else if (j < another.getSize()) {
        while (j < another.getSize()) {
            destination[resIndex++] = anotherArr[j++];
        }
    }

    delete[] thisArr;
    delete[] anotherArr;
}

template<class T, class K>
T AVLTree<T, K>::findGreaterOrEqual(const K &key, bool &found) const {
    Node *closest = findGreaterOrEqualAux(key, root, nullptr);
    if (closest == nullptr) {
        found = false;
        return T();
    }
    found = true;
    return closest->data;
}

template<class T, class K>
auto AVLTree<T, K>::findGreaterOrEqualAux(const K &key,
                                          Node *current,
                                          Node *closest) const -> Node * {
    if (!current) {
        return closest;
    }
    if (key < current->key) {
        closest = current;
        return findGreaterOrEqualAux(key, current->left, closest);
    }
    return findGreaterOrEqualAux(key, current->right, closest);
}
