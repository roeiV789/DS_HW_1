#include <cassert>
#include <iostream>
using namespace std;
#include "AVLTree.h"
#define DUMMY_DATA 0
typedef AVLTree<int, int>::Node Node;

void avl_tree_test_1();

void avl_tree_test_2();

void avl_tree_test_3();

void avl_tree_test_4();

void avl_tree_test_5();

void avl_tree_test_6();

int main() {
    avl_tree_test_1();
    avl_tree_test_2();
    avl_tree_test_3();
    avl_tree_test_4();
    avl_tree_test_5();
    avl_tree_test_6();
    cout << "ALL TESTS PASSED" << endl;
    return 0;
}

void avl_tree_test_1() {
    AVLTree<int, int> tree;
    // basic insertion without rotations
    int *arr1 = new int[3];
    tree.insert(DUMMY_DATA, 2);
    tree.insert(DUMMY_DATA, 3);
    tree.insert(DUMMY_DATA, 1);
    tree.toArray(arr1);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    delete[] arr1;

    // insertions that trigger an LL rotation
    tree.insert(DUMMY_DATA, 0);
    tree.insert(DUMMY_DATA, -1);
    int *arr2 = new int[5];
    tree.toArray(arr2);
    assert(arr2[0] == -1);
    assert(arr2[1] == 0);
    assert(arr2[2] == 1);
    assert(arr2[3] == 2);
    assert(arr2[4] == 3);
    delete[] arr2;

    // insertions that trigger an RR rotation
    tree.insert(DUMMY_DATA, 4);
    tree.insert(DUMMY_DATA, 5);
    int *arr3 = new int[7];
    tree.toArray(arr3);
    assert(arr3[0] == -1);
    assert(arr3[1] == 0);
    assert(arr3[2] == 1);
    assert(arr3[3] == 2);
    assert(arr3[4] == 3);
    assert(arr3[5] == 4);
    assert(arr3[6] == 5);
    delete[] arr3;

    // insertions that trigger a LR rotation
    tree.insert(DUMMY_DATA, -3);
    tree.insert(DUMMY_DATA, -2);
    int *arr4 = new int[9];
    tree.toArray(arr4);
    assert(arr4[0] == -3);
    assert(arr4[1] == -2);
    assert(arr4[2] == -1);
    assert(arr4[3] == 0);
    assert(arr4[4] == 1);
    assert(arr4[5] == 2);
    assert(arr4[6] == 3);
    assert(arr4[7] == 4);
    assert(arr4[8] == 5);
    delete[] arr4;

    // insertions that trigger a RL rotation
    tree.insert(DUMMY_DATA, 7);
    tree.insert(DUMMY_DATA, 6);
    int *arr5 = new int[11];
    tree.toArray(arr5);
    assert(arr5[0] == -3);
    assert(arr5[1] == -2);
    assert(arr5[2] == -1);
    assert(arr5[3] == 0);
    assert(arr5[4] == 1);
    assert(arr5[5] == 2);
    assert(arr5[6] == 3);
    assert(arr5[7] == 4);
    assert(arr5[8] == 5);
    assert(arr5[9] == 6);
    assert(arr5[10] == 7);
    delete[] arr5;
}

void avl_tree_test_2() {
    AVLTree<int, int> tree;
    // basic insertion without rotations
    int *arr1 = new int[7];
    tree.insert(DUMMY_DATA, 1);
    tree.insert(DUMMY_DATA, 2);
    tree.insert(DUMMY_DATA, 3);
    tree.insert(DUMMY_DATA, 4);
    tree.insert(DUMMY_DATA, 5);
    tree.insert(DUMMY_DATA, 6);
    tree.insert(DUMMY_DATA, 7);
    tree.toArray(arr1);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    assert(arr1[5] == 6);
    assert(arr1[6] == 7);
    delete[] arr1;

    int *arr2 = new int[5];
    tree.remove(2);
    tree.remove(4);
    tree.toArray(arr2);

    assert(arr2[0]==1);
    assert(arr2[1]==3);
    assert(arr2[2]==5);
    assert(arr2[3]==6);
    assert(arr2[4]==7);
    delete[] arr2;
}

void avl_tree_test_3() {
    AVLTree<int, int> tree;
    int *arr1 = new int[2];
    tree.insert(DUMMY_DATA, 2);
    tree.insert(DUMMY_DATA, 3);
    tree.toArray(arr1);
    assert(arr1[0] == 2);
    assert(arr1[1] == 3);
    delete[] arr1;

    //edge case of removing last two nodes
    tree.remove(2);
    int *arr2 = new int[1];
    tree.toArray(arr2);
    assert(arr2[0] == 3);
    delete[] arr2;
    tree.remove(3);
    assert(tree.getRoot() == nullptr);
}

void avl_tree_test_4() {
    AVLTree<int, int> tree;

    int *arr1 = new int[7];
    tree.insert(DUMMY_DATA, 1);
    tree.insert(DUMMY_DATA, 2);
    tree.insert(DUMMY_DATA, 3);
    tree.insert(DUMMY_DATA, 4);
    tree.insert(DUMMY_DATA, 5);
    tree.insert(DUMMY_DATA, 6);
    tree.insert(DUMMY_DATA, 7);
    tree.toArray(arr1);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    assert(arr1[5] == 6);
    assert(arr1[6] == 7);
    delete[] arr1;
    if (tree.search(2)) {
        cout << "test 4: success" << endl;
    } else {
        cout << "test 4: failed" << endl;
    }
    if (tree.search(8)) {
        cout << "test 4: failed" << endl;
    } else {
        cout << "test 4: success" << endl;
    }
}

void avl_tree_test_5() {
    // case 1: two trees with different set of keys s.t. the total number of elements is even
    AVLTree<int, int> tree1;
    tree1.insert(DUMMY_DATA, 1);
    tree1.insert(DUMMY_DATA, 2);
    tree1.insert(DUMMY_DATA, 3);

    AVLTree<int, int> tree2;
    tree2.insert(DUMMY_DATA, 4);
    tree2.insert(DUMMY_DATA, 5);
    tree2.insert(DUMMY_DATA, 6);

    Node *dest = new Node[6];
    tree1.mergeToArray(tree2, dest);
    assert(dest[0].key == 1);
    assert(dest[1].key == 2);
    assert(dest[2].key == 3);
    assert(dest[3].key == 4);
    assert(dest[4].key == 5);
    assert(dest[5].key == 6);

    tree1.recreateFromArray(dest, 6);
    int *arr1 = new int[6];
    tree1.toArray(arr1);
    assert(tree1.getSize() == 6);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    assert(arr1[5] == 6);
}

void avl_tree_test_6() {
    // case 1: two trees with different set of keys s.t. the total number of elements is odd
    AVLTree<int, int> tree1;
    tree1.insert(DUMMY_DATA, 1);
    tree1.insert(DUMMY_DATA, 2);
    tree1.insert(DUMMY_DATA, 3);

    AVLTree<int, int> tree2;
    tree1.insert(DUMMY_DATA, 4);
    tree1.insert(DUMMY_DATA, 5);


    // case 2: trees with intersecting set of keys
}
