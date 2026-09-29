#pragma once

#include <span>
#include <vector>

#include "MoveCommand.h"

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
