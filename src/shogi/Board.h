#pragma once

#include <array>
#include <vector>
#include <utility>

#include "Koma.h"

// TODO: handle komadai and nari or etc..
struct MoveCommand {
    std::pair<char, char> origin;
    std::pair<char, char> destination;
    KomaType type;
    Direction direction;
};

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

    void Move(const MoveCommand& command);
    void Move(const std::vector<MoveCommand>& commands);

    std::string DebugString();
    void DebugPrint();
};
