// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b1.h"


DSpotify::DSpotify() = default;

DSpotify::~DSpotify(){

}

StatusType DSpotify::add_playlist(int playlistId){
    if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if(!playlistTree.search(playlistId)) {
            auto playlist = new Playlist(playlistId);
            playlistTree.insert(playlist, playlistId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::delete_playlist(int playlistId){
    return StatusType::FAILURE;
}

StatusType DSpotify::add_song(int songId, int plays) {
    if(plays < 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if(!songTree.search(songId)) {
            shared_ptr<Song> newSong = make_shared<Song>(songId, plays);
            songTree.insert(newSong, songId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::add_to_playlist(int playlistId, int songId){
    return StatusType::FAILURE;
}

StatusType DSpotify::delete_song(int songId){
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        auto res = songTree.search(songId);
        if((*res)->getPlaylistCount()==0) {
            songTree.remove(songId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::remove_from_playlist(int playlistId, int songId){
    return StatusType::FAILURE;
}

output_t<int> DSpotify::get_plays(int songId) {
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        auto res = songTree.search(songId);
        if(res) {
            return output_t<int>((*res)->getPlays());
        }
        return StatusType::FAILURE;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }

}

output_t<int> DSpotify::get_num_songs(int playlistId){
    return 0;
}

output_t<int> DSpotify::get_by_plays(int playlistId, int plays){
    if(plays < 0 || playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        auto res = playlistTree.search(playlistId);
        if(!res) {
            return StatusType::FAILURE;
        }
        int closestPlays = (*res)->get_song_by_plays(plays);
        if(closestPlays < 0) {
            return StatusType::FAILURE;
        }
        return output_t<int>(closestPlays);
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::unite_playlists(int playlistId1, int playlistId2){
    return StatusType::FAILURE;
}
