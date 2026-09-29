#pragma once

#include <array>
#include <vector>
#include <utility>

#include "Koma.h"
#include "Kifu.h"

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

    bool Move(const MoveCommand& command);
    bool Move(const std::vector<MoveCommand>& commands);

    std::string DebugString();
    void DebugPrint();
};
