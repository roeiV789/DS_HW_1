#include "Playlist.h"

Playlist::Playlist(int playlistId) : playlistId(playlistId), size(0){}

Playlist::~Playlist() {
    songs.deleteTree(songs.getRoot());
    playsTree.deleteTree(playsTree.getRoot());
}

int Playlist::getPlaylistId() const {
    return playlistId;
}

int Playlist::getSize() const{
    return size;
}

void Playlist::setSize(int size) {
    this->size = size;
}

void Playlist::addSong(const shared_ptr<Song>& song) {
    if(song) {
        int id = song->getSongId();
        songs.insert(song,id);
        playsTree.insert(id, PlaysKey(song->getPlays(),id));
        song->setPlaylistCount(song->getPlaylistCount()+1);
        size++;
    }
}

void Playlist::removeSong(int songId) {
    shared_ptr<Song> song  = *songs.search(songId);
    if (song) {
        songs.remove(songId);
        playsTree.remove(PlaysKey(song->getPlays(),songId));
        song->setPlaylistCount(song->getPlaylistCount()-1);
        size--;
    }
}

bool Playlist::isInPlaylist(int songId) const {
    return this->songs.search(songId) != nullptr;
}