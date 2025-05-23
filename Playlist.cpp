#include "Playlist.h"

#include "debug.h"

Playlist::Playlist(int playlistId) : playlistId(playlistId), size(0) {
}

Playlist::~Playlist() {
    songs.deleteTree();
    playsTree.deleteTree();
}

int Playlist::getPlaylistId() const {
    return playlistId;
}

int Playlist::getSize() const {
    return size;
}

void Playlist::setSize(int size) {
    this->size = size;
}

void Playlist::addSong(const shared_ptr<Song> &song) {
    print_playlist_contents(this, this->playlistId);
    if (song) {
        int id = song->getSongId();
        songs.insert(song, id);
        playsTree.insert(id, PlaysKey(song->getPlays(), id));
        song->setPlaylistCount(song->getPlaylistCount() + 1);
        size++;
    }
}

void Playlist::removeSong(int songId) {
    print_playlist_contents(this, this->playlistId);
    bool found;
    shared_ptr<Song> song = songs.search(songId, found);
    if (found) {
        songs.remove(songId);
        playsTree.remove(PlaysKey(song->getPlays(), songId));
        song->setPlaylistCount(song->getPlaylistCount() - 1);
        size--;
    }
}


const AVLTree<shared_ptr<Song>, int> &Playlist::getSongsTree() const {
    return songs;
}

const AVLTree<int, PlaysKey> &Playlist::getPlaysTree() const {
    return playsTree;
}

bool Playlist::isInPlaylist(int songId) const {
    return this->songs.found(songId);
}

//returns the song id of the song with the same number of plays or greater with id as a tie breaker
int Playlist::get_song_by_plays(int plays) const {
    if (this->size == 0)
        return -1;

    PlaysKey key(plays,MIN_SONG_ID);
    bool found = false;
    int songId = playsTree.findGreaterOrEqual(key, found);
    return found ? songId : -1;
}

void Playlist::decreaseDuplicatePlaylistCount(const AVLTree<shared_ptr<Song>, int> &songTree1,
                                              const AVLTree<shared_ptr<Song>, int> &songTree2) {
    auto arr1 = new SongNode[songTree1.getSize()];
    auto arr2 = new SongNode[songTree2.getSize()];
    songTree1.toArray(arr1);
    songTree2.toArray(arr2);
    int i = 0, j = 0;
    while (i < songTree1.getSize() && j < songTree2.getSize()) {
        if (arr1[i].key < arr2[j].key) {
            i++;
        } else if (arr1[i].key > arr2[j].key) {
            j++;
        } else {
            shared_ptr<Song> song = arr1[i].data;
            song->setPlaylistCount(song->getPlaylistCount() - 1);
            i++;
            j++;
        }
    }
    delete[] arr1;
    delete[] arr2;
}

void Playlist::releaseAllMemory() {
    songs.deleteTree();
    playsTree.deleteTree();
    size = 0;
}

void Playlist::mergeIntoThis(shared_ptr<Playlist> other) {
    if (other->size == 0) {
        return;
    }
    decreaseDuplicatePlaylistCount(this->songs, other->songs);
    uniteSongs(this->songs, other->songs);
    unitePlays(this->playsTree, other->playsTree);
    this->size = this->songs.getSize();
    other->releaseAllMemory();
}

void Playlist::uniteSongs(AVLTree<shared_ptr<Song>, int> &songTree1, const AVLTree<shared_ptr<Song>, int> &songTree2) {
    int n = songTree1.getSize() + songTree2.getSize();
    auto data = new SongNode[n];
    for (int i = 0; i < n; i++) {
        data[i] = SongNode(nullptr, -1);
    }
    songTree1.mergeToArray(songTree2, data);
    int size = 0;
    while (data[size].key != -1 && size < n) {
        size++;
    }
    songTree1.recreateFromArray(data, size);
    delete[] data;
}

void Playlist::unitePlays(AVLTree<int, PlaysKey> &playsTree1, const AVLTree<int, PlaysKey> &playsTree2) {
    int n = playsTree1.getSize() + playsTree2.getSize();
    auto data = new PlaysNode[n];
    for (int i = 0; i < n; i++) {
        data[i] = PlaysNode(-1, PlaysKey());
    }
    playsTree1.mergeToArray(playsTree2, data);
    int size = 0;
    while (data[size].data != -1 && size < n) {
        size++;
    }
    playsTree1.recreateFromArray(data, size);
    delete[] data;
}
