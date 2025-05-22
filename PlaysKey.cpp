#include "PlaysKey.h"

PlaysKey::PlaysKey(int plays, int songId) : plays(plays), songId(songId) {
}

bool PlaysKey::operator<(const PlaysKey &other) const {
    if (plays < other.getPlays()) {
        return true;
    }
    if (plays > other.getPlays()) {
        return false;
    }
    return songId < other.getSongId();
}

bool PlaysKey::operator>(const PlaysKey &other) const {
    return other < *this;
}

bool PlaysKey::operator==(const PlaysKey &other) const {
    return plays == other.plays && songId == other.songId;
}

int PlaysKey::getPlays() const {
    return plays;
}

int PlaysKey::getSongId() const {
    return songId;
}
