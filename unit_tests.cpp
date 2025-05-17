#include <cassert>

#include "AVLTree.h"
#define DUMMY_DATA 0

void avl_tree_test_1();

void avl_tree_test_2();

void run_unit_tests() {
    avl_tree_test_1();
}

void avl_tree_test_1() {
    AVLTree<int, int> tree;
    // basic insertion without rotations
    int *arr1 = new int[3];
    tree.insert(DUMMY_DATA, 2);
    tree.insert(DUMMY_DATA, 3);
    tree.insert(DUMMY_DATA, 1);
    tree.toArray(arr1);
    assert(arr1[0] == 2);
    assert(arr1[1] == 1);
    assert(arr1[2] == 3);
    delete arr1;

    // insertions that trigger an LL rotation
    tree.insert(DUMMY_DATA, 0);
    tree.insert(DUMMY_DATA, -1);
    int *arr2 = new int[5];
    tree.toArray(arr2);
    assert(arr2[0] == 2);
    assert(arr2[1] == 0);
    assert(arr2[2] == 3);
    assert(arr2[3] == -1);
    assert(arr2[4] == 1);
}
