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

const std::array<std::array<KomaRef, 9>, 9>& Shogi::GetMasume() const
{
    return mBoard.GetMasume();
}

const std::vector<KomaRef>& Shogi::GetKomadaiBlack() const
{
    return mBoard.GetKomadaiBlack();
}

const std::vector<KomaRef>& Shogi::GetKomadaiWhite() const
{
    return mBoard.GetKomadaiWhite();
}

std::wstring Shogi::ToWStringKomadaiBlack() const
{
    return mBoard.ToWStringKomadaiBlack();
}

std::wstring Shogi::ToWStringKomadaiWhite() const
{
    return mBoard.ToWStringKomadaiWhite();
}

std::string Shogi::DebugString()
{
    return mBoard.DebugString();
}

void Shogi::DebugPrint()
{
    mBoard.DebugPrint();
}
