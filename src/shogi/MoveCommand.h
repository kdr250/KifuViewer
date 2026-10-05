#pragma once

#include <iostream>
#include <ostream>

#include "Koma.h"

/**
 * 移動コマンド
 */
struct MoveCommand {
    std::pair<char, char> origin;
    std::pair<char, char> destination;
    KomaType type;
    Direction direction;
    bool isNaru = false;

    static constexpr std::pair<char, char> KOMADAI_BLACK = std::make_pair(CHAR_MIN, CHAR_MIN);
    static constexpr std::pair<char, char> KOMADAI_WHITE = std::make_pair(CHAR_MAX, CHAR_MAX);

    inline bool operator==(const MoveCommand& other) const
    {
        return origin == other.origin
            && destination == other.destination
            && type == other.type
            && direction == other.direction
            && isNaru == other.isNaru;
    }
};

inline std::ostream& operator<<(std::ostream& os, const MoveCommand& command)
{
    auto& [originS, originD] = command.origin;
    auto& [destinationS, destinationD] = command.destination;
    std::string komaName = Koma::ToString(command.type);
    std::string teban = ToString(command.direction);
    bool isNaru = command.isNaru;

    os << "MoveCommand { origin: { " << (int)originS << ", " << (int)originD << " }, "
       << "dest: { " << (int)destinationS << ", " << (int)destinationD << " }, "
       << "type: " << komaName << ", "
       << "direction: " << teban << ", "
       << "isNari: " << isNaru;

    return os;
}
