#pragma once
#include <stdexcept>

class Song {
    int songId;
    int plays;
    int playlistCount;
public:
    Song(int songId, int plays);

    int getSongId() const;

    int getPlaylistCount() const;

    int getPlays() const;

    void setPlaylistCount(int playlistCount);

};
