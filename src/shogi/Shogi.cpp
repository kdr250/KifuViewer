#include "Shogi.h"

Shogi::Shogi()
{
    mBoard.Reset();
}

std::string Shogi::DebugString()
{
    return mBoard.DebugString();
}

void Shogi::DebugPrint()
{
    mBoard.DebugPrint();
}
