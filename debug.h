// debug.h
#pragma once

#include <cassert>
#include <fstream>
#include <iostream>

inline void print_playlist_contents(const Playlist *const playlist, int id) {
#ifndef NDEBUG
    std::ofstream outfile("debug.txt", std::ios::app); // opens for writing, truncates if exists
    if (playlist->getSongsTree().getSize() != playlist->getPlaysTree().getSize()) {
        outfile << "WARNING " << "!!!tree sizes do not match for the playlist below!!!" << std::endl;
    }
    int n = max(playlist->getSongsTree().getSize(), playlist->getPlaysTree().getSize());
    outfile << "DEBUG" << " contents of playlist " << id << ": " << std::endl;
    auto songArr = new SongNode[n];
    auto playsArr = new PlaysNode[n];
    playlist->getSongsTree().toArray(songArr);
    playlist->getPlaysTree().toArray(playsArr);
    outfile << "DEBUG" " songs: (songId) " << std::endl;
    for (int i = 0; i < n; i++) {
        outfile << songArr[i].key << " ";
    }
    outfile << std::endl;

    outfile << "DEBUG" " plays: (plays, songId) " << std::endl;
    for (int i = 0; i < n; i++) {
        outfile << "(" << playsArr[i].key.getPlays() << ", "
                << playsArr[i].key.getSongId() << "), ";
    }
    outfile << std::endl;
#endif
}
