#pragma once

#include <array>
#include <vector>
#include <span>
#include <utility>

#include "Koma.h"

struct MoveCommand {
    std::pair<char, char> origin;
    std::pair<char, char> destination;
    KomaType type;
    Direction direction;
    bool isNaru = false;

    static constexpr std::pair<char, char> KOMADAI_BLACK = std::make_pair(CHAR_MIN, CHAR_MIN);
    static constexpr std::pair<char, char> KOMADAI_WHITE = std::make_pair(CHAR_MAX, CHAR_MAX);
};

/**
 * 盤
 */
class Board {
private:
    std::array<std::array<KomaRef, 9>, 9> mMasume; // マス目

    std::vector<KomaRef> mKomadaiBlack; // 先手の駒台
    std::vector<KomaRef> mKomadaiWhite; // 後手の駒台

    std::vector<MoveCommand> mSavedCommands;

public:
    void Initialize();

    void Push(const MoveCommand& command);
    void Push(const std::vector<MoveCommand>& commands);

    void Pop();
    void Pop(unsigned int count);

    bool Replay();
    bool Replay(unsigned int limit);

    void Back();
    void Back(unsigned int count);

    std::string DebugString();
    void DebugPrint();

private:
    void Reset();

    bool Move(const MoveCommand& command);
    bool Move(const std::span<MoveCommand>& commands);
};
