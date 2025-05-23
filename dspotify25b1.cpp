// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b1.h"
#include "debug.h"


DSpotify::DSpotify() = default;

DSpotify::~DSpotify() {
    songTree.deleteTree();
    playlistTree.deleteTree();
}

StatusType DSpotify::add_playlist(int playlistId) {
    if (playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if (!playlistTree.found(playlistId)) {
            playlistTree.insert(make_shared<Playlist>(playlistId), playlistId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::delete_playlist(int playlistId) {
    if (playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    bool found;
    auto playlist = playlistTree.search(playlistId, found);
    if (!found || playlist->getSize() > 0) {
        return StatusType::FAILURE;
    }

    try {
        playlistTree.remove(playlistId);
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::add_song(int songId, int plays) {
    if (plays < 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if (!songTree.found(songId)) {
            shared_ptr<Song> newSong = make_shared<Song>(songId, plays);
            songTree.insert(newSong, songId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::add_to_playlist(int playlistId, int songId) {
    if (playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    bool found;
    auto song = songTree.search(songId, found);
    if (!found) {
        return StatusType::FAILURE;
    }
    auto playlist = playlistTree.search(playlistId, found);
    if (!found) {
        return StatusType::FAILURE;
    }
    if (playlist->isInPlaylist(songId))
        return StatusType::FAILURE;

    try {
        playlist->addSong(song);
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DSpotify::delete_song(int songId) {
    if (songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        bool found;
        auto res = songTree.search(songId, found);
        if (found && res->getPlaylistCount() == 0) {
            songTree.remove(songId);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::remove_from_playlist(int playlistId, int songId) {
    if (playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    bool found;
    auto playlist = playlistTree.search(playlistId, found);
    if (!found || !playlist->isInPlaylist(songId)) {
        return StatusType::FAILURE;
    }
    playlist->removeSong(songId);
    return StatusType::SUCCESS;
}

output_t<int> DSpotify::get_plays(int songId) {
    if (songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        bool found;
        auto res = songTree.search(songId, found);
        if (found) {
            return res->getPlays();
        }
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::get_num_songs(int playlistId) {
    if (playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        bool found;
        auto res = playlistTree.search(playlistId, found);
        if (found) {
            print_playlist_contents(res.get(), playlistId);
            return res->getSize();
        }
        return StatusType::FAILURE;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::get_by_plays(int playlistId, int plays) {
    if (plays < 0 || playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        bool found;
        auto res = playlistTree.search(playlistId, found);
        if (!found) {
            return StatusType::FAILURE;
        }
        int closestPlays = res->get_song_by_plays(plays);
        if (closestPlays < 0) {
            return StatusType::FAILURE;
        }
        return closestPlays;
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::unite_playlists(int playlistId1, int playlistId2) {
    if (playlistId1 <= 0 || playlistId2 <= 0 || playlistId1 == playlistId2) {
        return StatusType::INVALID_INPUT;
    }

    bool found;
    auto playlist1 = playlistTree.search(playlistId1, found);
    if (!found)
        return StatusType::FAILURE;
    auto playlist2 = playlistTree.search(playlistId2, found);
    if (!found)
        return StatusType::FAILURE;
    try {
        print_playlist_contents(playlist1.get(), playlistId1);
        print_playlist_contents(playlist2.get(), playlistId2);
        playlist1->mergeIntoThis(playlist2);
        delete_playlist(playlistId2);
    } catch (const std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
