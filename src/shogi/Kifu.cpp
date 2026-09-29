#include "Kifu.h"

Kifu::Kifu(const std::vector<MoveCommand>& commands)
    : mCommands(commands)
    , mLastIndex(commands.size() - 1)
{
}

std::span<MoveCommand> Kifu::GetCurrentCommands()
{
    // TODO: 分岐を扱えるようにする
    std::span<MoveCommand> result(mCommands.data(), mLastIndex + 1);
    return result;
}
