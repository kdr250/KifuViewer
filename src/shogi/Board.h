#pragma once

#include <array>
#include <span>
#include <vector>
#include <utility>

#include "Koma.h"
#include "MoveCommand.h"

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
    bool Move(const std::span<MoveCommand>& commands);

    const std::array<std::array<KomaRef, 9>, 9>& GetMasume() const;
    const std::vector<KomaRef>& GetKomadaiBlack() const;
    const std::vector<KomaRef>& GetKomadaiWhite() const;

    std::wstring ToWStringKomadaiBlack() const;
    std::wstring ToWStringKomadaiWhite() const;

    std::string DebugString();
    void DebugPrint();
};
