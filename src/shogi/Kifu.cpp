#include "Kifu.h"

#include <algorithm>

Kifu::Kifu(const std::vector<MoveCommand>& commands)
    : mCommands(commands)
    , mLastIndex(0)
{
}

std::span<MoveCommand> Kifu::GetMoveCommands()
{
    // TODO: 分岐を扱えるようにする
    std::span<MoveCommand> result(mCommands.data(), mLastIndex + 1);
    return result;
}

void Kifu::Forward(unsigned int num)
{
    mLastIndex = std::min(mLastIndex + num, static_cast<unsigned int>(mCommands.size() - 1));
}

void Kifu::Backward(unsigned int num)
{
    mLastIndex = std::max(mLastIndex - num, (unsigned int)0);
}
