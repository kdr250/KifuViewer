#include "Shogi.h"

Shogi::Shogi()
{
    mBoard.Reset();
}

void Shogi::SetKifu(const std::shared_ptr<Kifu>& kifu)
{
    mKifu = kifu;
}

void Shogi::First()
{
    if (mKifu == nullptr) {
        return;
    }
    mKifu->First();
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

void Shogi::Last()
{
    if (mKifu == nullptr) {
        return;
    }
    mKifu->Last();
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

void Shogi::Forward(unsigned int num)
{
    if (mKifu == nullptr) {
        return;
    }
    mKifu->Forward(num);
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

void Shogi::Backward(unsigned int num)
{
    if (mKifu == nullptr) {
        return;
    }
    mKifu->Backward(num);
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

std::string Shogi::DebugString()
{
    return mBoard.DebugString();
}

void Shogi::DebugPrint()
{
    mBoard.DebugPrint();
}
