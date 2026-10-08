#include "Kifu.h"

#include <algorithm>

Kifu::Kifu(const std::vector<MoveCommand>& commands)
    : mCommands(commands)
    , mCurrentIndex(-1)
{
}

std::span<MoveCommand> Kifu::GetMoveCommands()
{
    // TODO: 分岐を扱えるようにする
    if (mCurrentIndex <= -1) {
        return std::span<MoveCommand>();
    }
    std::span<MoveCommand> result(mCommands.data(), mCurrentIndex + 1);
    return result;
}

void Kifu::First()
{
    mCurrentIndex = -1;
}

void Kifu::Last()
{
    mCurrentIndex = mCommands.size() - 1;
}

void Kifu::Forward(unsigned int num)
{
    mCurrentIndex = std::min(mCurrentIndex + num, static_cast<unsigned int>(mCommands.size() - 1));
}

void Kifu::Backward(unsigned int num)
{
    mCurrentIndex = std::max(mCurrentIndex - (int)num, -1);
}
