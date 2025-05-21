#pragma once

class PlaysKey {
    int plays;
    int songId;

public:
    PlaysKey(int plays, int songId);

    PlaysKey() = default;

    bool operator<(const PlaysKey &other) const;

    bool operator>(const PlaysKey &other) const;
    bool operator==(const PlaysKey &other) const;

    int getPlays() const;

    int getSongId() const;
};
