#pragma once
#include "song.h"
#include "PlaysKey.h"
#include "AVLTree.h"
#include <memory>

class Playlist {
    int playlistId;
    int size; //number of songs
    AVLTree<shared_ptr<Song>,int> songs;
    AVLTree<int,PlaysKey> playsTree;

public:
    explicit Playlist(int playlistId);

    ~Playlist();

    int getPlaylistId() const;

    int getSize() const;

    void setSize(int size);
};
