#include <cassert>

#include "AVLTree.h"

void avl_tree_test_1();

void avl_tree_test_2();

void run_unit_tests() {
    avl_tree_test_1();
}

void avl_tree_test_1() {
    AVLTree<int, int> tree;
    int *arr1 = new int[3];
    tree.insert(0, 2);
    tree.insert(1, 3);
    tree.insert(2, 1);
    tree.toArray(arr1);
    assert(arr1[0] == 2);
    assert(arr1[1] == 1);
    assert(arr1[2] == 3);
    delete arr1;
}

