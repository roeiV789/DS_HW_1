#pragma once
using namespace std;
#include "Song.h"
#include "PlaysKey.h"
#include "AVLTree.h"
#include <memory>

#define MIN_SONG_ID 0


typedef AVLTree<shared_ptr<Song>, int>::Node SongNode;
typedef AVLTree<int, PlaysKey>::Node PlaysNode;

class Playlist {
    int playlistId;
    int size; //number of songs
    AVLTree<shared_ptr<Song>, int> songs;
    AVLTree<int, PlaysKey> playsTree;

    void uniteSongs(AVLTree<shared_ptr<Song>, int> &songTree1, const AVLTree<shared_ptr<Song>, int> &songTree2);

    void unitePlays(AVLTree<int, PlaysKey> &playsTree1, const AVLTree<int, PlaysKey> &playsTree2);

public:
    explicit Playlist(int playlistId);

    ~Playlist();

    int getPlaylistId() const;

    int getSize() const;

    void setSize(int size);

    void addSong(const shared_ptr<Song> &song);

    void removeSong(int songId);

    const AVLTree<shared_ptr<Song>, int> &getSongsTree() const;

    const AVLTree<int, PlaysKey> &getPlaysTree() const;

    bool isInPlaylist(int songId) const;

    int get_song_by_plays(int plays) const;

    void decreasePlaylistCount(SongNode *song);

    void releaseAllMemory();

    void mergeIntoThis(Playlist *other);
};
