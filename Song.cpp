#include "Song.h"

Song::Song(int songId, int plays) : songId(songId), plays(plays), playlistCount(0) {
    if(songId < 0 || plays < 0) {
        throw std::invalid_argument("Invalid song id/plays supplied");
    }
}
int Song::getSongId() const {
    return songId;
}
int Song::getPlaylistCount() const {
    return playlistCount;
}
int Song::getPlays() const {
    return plays;
}
void Song::setPlaylistCount(int playlistCount) {
    this->playlistCount = playlistCount;
}
