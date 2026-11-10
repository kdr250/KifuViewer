#include "Shogi.h"

Shogi::Shogi()
{
    mBoard.Reset();
}

void Shogi::SetKifu(const std::shared_ptr<Kifu>& kifu)
{
    mKifu = kifu;
    mBoard.Reset();
}

bool Shogi::HasKifu() const
{
    return mKifu != nullptr;
}

void Shogi::First()
{
    if (mKifu) {
        mKifu->First();
    }
    mBoard.Reset();
}

void Shogi::Last()
{
    if (mKifu == nullptr || mKifu->Empty()) {
        return;
    }
    mKifu->Last();
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

void Shogi::MoveTo(int index)
{
    if (mKifu == nullptr || mKifu->Empty()) {
        return;
    }
    mKifu->SetCurrentIndex(index);
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

int Shogi::GetCurrentKifuIndex()
{
    if (mKifu == nullptr || mKifu->Empty()) {
        return -1;
    }
    return mKifu->GetCurrentIndex();
}

std::vector<std::string> Shogi::GetKifuStrings()
{
    if (mKifu == nullptr || mKifu->Empty()) {
        return std::vector<std::string>();
    }
    return mKifu->ToDisplayStrings();
}

void Shogi::Forward(unsigned int num)
{
    if (mKifu == nullptr || mKifu->Empty()) {
        return;
    }
    mKifu->Forward(num);
    std::span<MoveCommand> commands = mKifu->GetMoveCommands();
    mBoard.Reset();
    mBoard.Move(commands);
}

void Shogi::Backward(unsigned int num)
{
    if (mKifu == nullptr || mKifu->Empty()) {
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
