#include <cassert>
#include <iostream>

#include "dspotify25b1.h"
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

void avl_tree_test_7();

void dspotify_test_1();

void dspotify_test_2();

void dspotify_test_3();

void dspotify_test_4();

void dspotify_test_5();

void dspotify_test_6();

void dspotify_test_7();

void dspotify_test_8();

int run_unit_tests() {
    // AVLTree tests
    avl_tree_test_1();
    avl_tree_test_2();
    avl_tree_test_3();
    avl_tree_test_4();
    avl_tree_test_5();
    avl_tree_test_6();
    avl_tree_test_7();

    // DSpotify tests
    dspotify_test_1();
    dspotify_test_2();
    dspotify_test_3();
    dspotify_test_4();
    dspotify_test_5();
    dspotify_test_6();
    dspotify_test_7();
    dspotify_test_8();
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
    bool found1;
    tree.search(2, found1);
    assert(found1 == true);
    bool found2;
    tree.search(8, found2);
    assert(found2 == false);
}

void avl_tree_test_5() {
    // merge test 1: two trees with different set of keys s.t. the total number of elements is even
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
    delete[] dest;
    int *arr1 = new int[6];
    tree1.toArray(arr1);
    assert(tree1.getSize() == 6);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    assert(arr1[5] == 6);
    delete[] arr1;
}

void avl_tree_test_6() {
    // merge test 2: two trees with different set of keys s.t. the total number of elements is odd
    AVLTree<int, int> tree1;
    tree1.insert(DUMMY_DATA, 1);
    tree1.insert(DUMMY_DATA, 2);
    tree1.insert(DUMMY_DATA, 3);

    AVLTree<int, int> tree2;
    tree2.insert(DUMMY_DATA, 4);
    tree2.insert(DUMMY_DATA, 5);

    Node *dest = new Node[5];
    tree1.mergeToArray(tree2, dest);
    assert(dest[0].key == 1);
    assert(dest[1].key == 2);
    assert(dest[2].key == 3);
    assert(dest[3].key == 4);
    assert(dest[4].key == 5);


    tree1.recreateFromArray(dest, 5);
    delete[] dest;
    int *arr1 = new int[5];
    tree1.toArray(arr1);
    assert(tree1.getSize() == 5);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    delete[] arr1;
}

void avl_tree_test_7() {
    // merge test 3: two trees with intersecting set of keys
    AVLTree<int, int> tree1;
    tree1.insert(DUMMY_DATA, 1);
    tree1.insert(DUMMY_DATA, 2);
    tree1.insert(DUMMY_DATA, 3);
    tree1.insert(DUMMY_DATA, 4);

    AVLTree<int, int> tree2;
    tree2.insert(DUMMY_DATA, 2);
    tree2.insert(DUMMY_DATA, 3);
    tree2.insert(DUMMY_DATA, 5);

    Node *dest = new Node[5];
    tree1.mergeToArray(tree2, dest);
    assert(dest[0].key == 1);
    assert(dest[1].key == 2);
    assert(dest[2].key == 3);
    assert(dest[3].key == 4);
    assert(dest[4].key == 5);

    tree1.recreateFromArray(dest, 5);
    delete[] dest;
    int *arr1 = new int[5];
    tree1.toArray(arr1);
    assert(tree1.getSize() == 5);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);
    delete[] arr1;
}

void dspotify_test_1() {
    DSpotify d;
    const int PLAYLIST_ID = 42;
    d.add_playlist(PLAYLIST_ID);
    d.add_song(1, 10);
    d.add_song(2, 15);
    d.add_song(3, 20);
    d.add_song(4, 15);

    d.add_to_playlist(PLAYLIST_ID, 1);
    d.add_to_playlist(PLAYLIST_ID, 2);
    d.add_to_playlist(PLAYLIST_ID, 4);

    assert(d.get_by_plays(PLAYLIST_ID, 13).ans() == 2);
    assert(d.get_by_plays(PLAYLIST_ID, 15).ans() == 2);
    assert(d.get_by_plays(PLAYLIST_ID, 16).status() == StatusType::FAILURE);
}

void dspotify_test_2() {
    DSpotify d;
    const int PLAYLIST_ID1 = 10;
    const int PLAYLIST_ID2 = 20;
    const int PLAYLIST_ID3 = 30;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    //checking add_playlist functionality - trying to add a playlist that already exists
    assert(d.add_playlist(PLAYLIST_ID1)==StatusType::FAILURE);
    assert(d.add_playlist(-1)==StatusType::INVALID_INPUT);
    //checking add song functionality
    d.add_song(1, 1);
    d.add_song(2, 2);
    d.add_song(3, 3);
    d.add_song(4, 3);
    d.add_song(5, 3);
    assert(d.add_song(6,3)==StatusType::SUCCESS);
    assert(d.add_song(5,4)==StatusType::FAILURE);
    assert(d.add_song(8,-1)==StatusType::INVALID_INPUT);
    assert(d.add_song(0,5)==StatusType::INVALID_INPUT);
    //checking delete playlist functionality
    assert(d.delete_playlist(-1)==StatusType::INVALID_INPUT);
    assert(d.delete_playlist(PLAYLIST_ID1)==StatusType::SUCCESS);
    assert(d.delete_playlist(PLAYLIST_ID1)==StatusType::FAILURE);
    d.add_to_playlist(PLAYLIST_ID2, 1);
    assert(d.delete_playlist(PLAYLIST_ID2)==StatusType::FAILURE);
    //checking delete song functionality
    assert(d.delete_song(1)==StatusType::FAILURE);
    assert(d.delete_song(2)==StatusType::SUCCESS);
    assert(d.delete_song(0)==StatusType::INVALID_INPUT);
}

void dspotify_test_3() {
    DSpotify d;
    const int PLAYLIST_ID1 = 10;
    const int PLAYLIST_ID2 = 20;
    const int PLAYLIST_ID3 = 30;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(1, 1);
    d.add_song(2, 2);
    d.add_song(3, 3);
    d.add_song(4, 3);
    d.add_song(5, 3);
    //checking add_to_playlist functionality
    assert(d.add_to_playlist(PLAYLIST_ID1,1)==StatusType::SUCCESS);
    assert(d.add_to_playlist(PLAYLIST_ID1,2)==StatusType::SUCCESS);
    assert(d.add_to_playlist(PLAYLIST_ID1,3)==StatusType::SUCCESS);
    assert(d.add_to_playlist(PLAYLIST_ID1,4)==StatusType::SUCCESS);
    assert(d.add_to_playlist(PLAYLIST_ID1,1)==StatusType::FAILURE);
    assert(d.add_to_playlist(0,1)==StatusType::INVALID_INPUT);
    assert(d.add_to_playlist(1,0)==StatusType::INVALID_INPUT);
    //checking it doesnt have a problem adding a song to two different playlists
    assert(d.add_to_playlist(PLAYLIST_ID2,1)==StatusType::SUCCESS);
    //checking that delete song cant delete songs that have been added
    assert(d.delete_song(1)==StatusType::FAILURE);
    assert(d.delete_song(5)==StatusType::SUCCESS);
}

void dspotify_test_4() {
    DSpotify d;
    const int PLAYLIST_ID1 = 10;
    const int PLAYLIST_ID2 = 20;
    const int PLAYLIST_ID3 = 30;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(1, 1);
    d.add_song(2, 2);
    d.add_song(3, 3);
    d.add_song(4, 3);
    d.add_song(5, 3);
    d.add_to_playlist(PLAYLIST_ID1, 1);
    d.add_to_playlist(PLAYLIST_ID1, 2);
    d.add_to_playlist(PLAYLIST_ID1, 3);
    d.add_to_playlist(PLAYLIST_ID1, 4);
    //checking get_plays functionality
    assert(d.get_plays(1).ans()==1);
    assert(d.get_plays(2).status()==StatusType::SUCCESS);
    assert(d.get_plays(6).status()==StatusType::FAILURE);
    assert(d.get_plays(0).status()==StatusType::INVALID_INPUT);
    //checking get_num_songs functionality
    assert(d.get_num_songs(PLAYLIST_ID1).ans() == 4);
    assert(d.get_num_songs(PLAYLIST_ID1).status()==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==0);
    assert(d.get_num_songs(PLAYLIST_ID2).status()==StatusType::SUCCESS);
    assert(d.get_num_songs(1000).status()==StatusType::FAILURE);
    assert(d.get_num_songs(PLAYLIST_ID3).ans()==0);
    d.add_to_playlist(PLAYLIST_ID2, 5);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==1);
}

void dspotify_test_5() {
    DSpotify d;
    const int PLAYLIST_ID1 = 10;
    const int PLAYLIST_ID2 = 20;
    const int PLAYLIST_ID3 = 30;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(1, 1);
    d.add_song(2, 2);
    d.add_song(3, 3);
    d.add_song(4, 3);
    d.add_song(5, 3);
    d.add_to_playlist(PLAYLIST_ID1, 1);
    d.add_to_playlist(PLAYLIST_ID1, 2);
    d.add_to_playlist(PLAYLIST_ID1, 3);
    d.add_to_playlist(PLAYLIST_ID1, 4);
    d.add_to_playlist(PLAYLIST_ID1, 5);
    //checking get_by_plays functionality
    assert(d.get_by_plays(PLAYLIST_ID1,3).ans()==3);
    assert(d.get_by_plays(PLAYLIST_ID1,3).status()==StatusType::SUCCESS);
    assert(d.get_by_plays(PLAYLIST_ID1,4).status()==StatusType::FAILURE);
    assert(d.get_by_plays(40,3).status()==StatusType::FAILURE);
    assert(d.get_by_plays(PLAYLIST_ID1,2).ans()==2);
    assert(d.get_by_plays(0,3).status()==StatusType::INVALID_INPUT);
    assert(d.get_by_plays(PLAYLIST_ID1,-1).status()==StatusType::INVALID_INPUT);
    d.add_song(6, 4);
    d.add_to_playlist(PLAYLIST_ID1, 6);
    assert(d.get_by_plays(PLAYLIST_ID1,4).status()==StatusType::SUCCESS);
    assert(d.get_by_plays(PLAYLIST_ID1,4).ans()==6);
}

//this test checks remove_from_playlist
void dspotify_test_6() {
    DSpotify d;
    const int PLAYLIST_ID1 = 100;
    const int PLAYLIST_ID2 = 200;
    const int PLAYLIST_ID3 = 300;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(10, 20);
    d.add_song(11, 21);
    d.add_song(12, 22);
    d.add_song(13, 22);
    d.add_song(14, 22);
    d.add_song(15, 23);
    d.add_to_playlist(PLAYLIST_ID1, 10);
    d.add_to_playlist(PLAYLIST_ID2, 11);
    d.add_to_playlist(PLAYLIST_ID2, 12);
    d.add_to_playlist(PLAYLIST_ID2, 13);
    d.add_to_playlist(PLAYLIST_ID2, 14);
    d.add_to_playlist(PLAYLIST_ID3, 15);
    assert(d.remove_from_playlist(PLAYLIST_ID1,10)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID1).ans()==0);
    assert(d.delete_playlist(PLAYLIST_ID1)==StatusType::SUCCESS);
    d.remove_from_playlist(PLAYLIST_ID2, 11);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==3);
    assert(d.remove_from_playlist(PLAYLIST_ID1,10)==StatusType::FAILURE);
    assert(d.remove_from_playlist(PLAYLIST_ID2,15)==StatusType::FAILURE);
    assert(d.remove_from_playlist(0,15)==StatusType::INVALID_INPUT);
    assert(d.remove_from_playlist(PLAYLIST_ID3,0)==StatusType::INVALID_INPUT);
}

// unite_playlists test 1: basic test + playlists do not intersect
void dspotify_test_7() {
    DSpotify d;
    const int PLAYLIST_ID1 = 100;
    const int PLAYLIST_ID2 = 200;
    const int PLAYLIST_ID3 = 300;
    const int PLAYLIST_ID5 = 500;
    const int PLAYLIST_ID6 = 600;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(10, 20);
    d.add_song(11, 21);
    d.add_song(12, 22);
    d.add_song(13, 22);
    d.add_song(14, 22);
    d.add_song(15, 23);
    d.add_to_playlist(PLAYLIST_ID1, 10);
    d.add_to_playlist(PLAYLIST_ID2, 11);
    d.add_to_playlist(PLAYLIST_ID2, 12);
    d.add_to_playlist(PLAYLIST_ID2, 13);
    d.add_to_playlist(PLAYLIST_ID2, 14);
    d.add_to_playlist(PLAYLIST_ID3, 15);
    assert(d.unite_playlists(0,1)==StatusType::INVALID_INPUT);
    assert(d.unite_playlists(1,0)==StatusType::INVALID_INPUT);
    assert(d.unite_playlists(400,PLAYLIST_ID1)==StatusType::FAILURE);
    //this playlist id doesn't exist so should return failure
    assert(d.unite_playlists(PLAYLIST_ID1,400)==StatusType::FAILURE);
    //this playlist id doesn't exist so should return failure
    assert(d.unite_playlists(PLAYLIST_ID1,PLAYLIST_ID2)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID1).ans()==5);
    assert(d.get_num_songs(PLAYLIST_ID2).status()==StatusType::FAILURE); //playlist2 should be deleted from tree
    assert(d.add_to_playlist(PLAYLIST_ID1,12)==StatusType::FAILURE); //song already in playlist because unite
    //checking unite with empty playlist from both sides
    d.add_playlist(PLAYLIST_ID5);
    assert(d.unite_playlists(PLAYLIST_ID1,PLAYLIST_ID5)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID1).ans()==5);
    assert(d.get_num_songs(PLAYLIST_ID5).status()==StatusType::FAILURE); //playlist deleted so should return failure
    d.add_playlist(PLAYLIST_ID6);
    assert(d.unite_playlists(PLAYLIST_ID6,PLAYLIST_ID1)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID6).ans()==5);
    assert(d.get_num_songs(PLAYLIST_ID1).status()==StatusType::FAILURE); //playlist deleted so should return failure
}

// unite_playlists test 2: playlists can intersect
void dspotify_test_8() {
    DSpotify d;
    const int PLAYLIST_ID1 = 100;
    const int PLAYLIST_ID2 = 200;
    const int PLAYLIST_ID3 = 300;
    d.add_playlist(PLAYLIST_ID1);
    d.add_playlist(PLAYLIST_ID2);
    d.add_playlist(PLAYLIST_ID3);
    d.add_song(10, 20);
    d.add_song(11, 21);
    d.add_song(12, 22);
    d.add_song(13, 22);
    d.add_song(14, 22);
    d.add_song(15, 23);
    d.add_song(16, 22);
    d.add_song(17, 23);
    d.add_to_playlist(PLAYLIST_ID1, 10);
    d.add_to_playlist(PLAYLIST_ID1, 11);
    d.add_to_playlist(PLAYLIST_ID1, 12);
    d.add_to_playlist(PLAYLIST_ID1, 13);
    d.add_to_playlist(PLAYLIST_ID2, 13);
    d.add_to_playlist(PLAYLIST_ID2, 14);
    d.add_to_playlist(PLAYLIST_ID2, 15);
    d.add_to_playlist(PLAYLIST_ID3, 14);
    d.add_to_playlist(PLAYLIST_ID3, 15);
    d.add_to_playlist(PLAYLIST_ID3, 16);
    d.add_to_playlist(PLAYLIST_ID3, 17);

    assert(d.unite_playlists(PLAYLIST_ID1,PLAYLIST_ID2)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID1).ans()==6);
    assert(d.get_num_songs(PLAYLIST_ID2).status()==StatusType::FAILURE);
    assert(d.add_playlist(PLAYLIST_ID2) == StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==0);
    assert(d.unite_playlists(PLAYLIST_ID2,PLAYLIST_ID1)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID1).status()==StatusType::FAILURE);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==6);
    assert(d.unite_playlists(PLAYLIST_ID2,PLAYLIST_ID3)==StatusType::SUCCESS);
    assert(d.get_num_songs(PLAYLIST_ID2).ans()==8);
    assert(d.get_num_songs(PLAYLIST_ID3).status()==StatusType::FAILURE);
}
