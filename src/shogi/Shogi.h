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

    void SetKifu(const std::shared_ptr<Kifu>& kifu);

    void First();
    void Last();

    void Forward(unsigned int num = 1);
    void Backward(unsigned int num = 1);

    std::string DebugString();
    void DebugPrint();

private:
    Board mBoard;
    std::shared_ptr<Kifu> mKifu = nullptr;
};
