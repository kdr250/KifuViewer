#pragma once

#include <array>
#include <vector>

#include "Koma.h"

/**
 * 盤
 */
class Board {
private:
    std::array<std::array<KomaRef, 9>, 9> mMasume; // マス目

    std::vector<KomaRef> mKomadaiBlack; // 先手の駒台
    std::vector<KomaRef> mKomadaiWhite; // 後手の駒台

public:
    void Reset();

    void DebugPrint();
};
