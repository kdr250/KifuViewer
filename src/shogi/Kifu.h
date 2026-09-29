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

    std::span<MoveCommand> GetMoveCommands();

    void Forward(unsigned int num = 1);
    void Backward(unsigned int num = 1);

private:
    std::vector<MoveCommand> mCommands;
    unsigned int mCurrentIndex;
};
