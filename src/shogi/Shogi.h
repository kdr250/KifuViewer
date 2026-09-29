#pragma once

#include <string>

#include "Board.h"
#include "Kifu.h"

/**
 * 将棋
 */
class Shogi {
public:
    Shogi();

    std::string DebugString();
    void DebugPrint();

private:
    Board mBoard;
    std::shared_ptr<Kifu> mKifu = nullptr;
};
