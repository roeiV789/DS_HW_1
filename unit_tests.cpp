#include <cassert>
#include <iostream>
using namespace std;
#include "AVLTree.h"
#define DUMMY_DATA 0

void avl_tree_test_1();

void avl_tree_test_2();

int main(){
    avl_tree_test_1();
    avl_tree_test_2();
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
    int *arr1 = new int[4];
    tree.insert(DUMMY_DATA, 3);
    tree.insert(DUMMY_DATA, 4);
    tree.insert(DUMMY_DATA, 5);
    tree.insert(DUMMY_DATA, 6);
    if(tree.getRoot()->left) {
        cout << "there is a node on the left";
    }
    cout << tree.toArray(arr1) << endl;

    cout << arr1[0] << endl;
    cout << arr1[1] << endl;
    cout << arr1[2] << endl;
    cout << arr1[3] << endl;
    assert(arr1[0] == 3);
    assert(arr1[1] == 4);
    assert(arr1[2] == 5);
    assert(arr1[3] == 6);
    delete[] arr1;

    int *arr2 = new int[3];
    tree.remove(5);
    tree.toArray(arr2);
    cout << arr2[0] << endl;
    cout << arr2[1] << endl;
    cout << arr2[2] << endl;

    delete[] arr2;

}
