#pragma once

#include <span>
#include <vector>

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
};

/**
 * 棋譜
 */
class Kifu {
public:
    Kifu(const std::vector<MoveCommand>& commands);

    std::span<MoveCommand> GetCurrentCommands();

private:
    std::vector<MoveCommand> mCommands;
    int mLastIndex = -1;
};
