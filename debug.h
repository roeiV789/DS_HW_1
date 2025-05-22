// debug.h
#pragma once

#include <cassert>
#include <iostream>

void print_playlist_contents(const Playlist *const playlist, int id) {
    assert(playlist->getSongsTree().getSize() == playlist->getPlaysTree().getSize());
    int n = playlist->getSongsTree().getSize();
    std::cout << "DEBUG" << " contents of playlist " << id << ": " << std::endl;
    auto songArr = new SongNode[n];
    auto playsArr = new PlaysNode[n];
    playlist->getSongsTree().toArray(songArr);
    playlist->getPlaysTree().toArray(playsArr);
    std::cout << "DEBUG" " songs: (songId) " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << songArr[i].key << " ";
    }
    std::cout << std::endl;

    std::cout << "DEBUG" " plays: (plays, songId) " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "(" << playsArr[i].key.getPlays() << ", "
                << playsArr[i].key.getSongId() << ")";
    }
    std::cout << std::endl;
}
