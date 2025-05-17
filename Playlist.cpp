#include "Playlist.h"

Playlist::Playlist(int playlistId) : playlistId(playlistId), size(0){}

Playlist::~Playlist() {

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