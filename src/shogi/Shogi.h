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
    bool HasKifu() const;

    void First();
    void Last();

    void Forward(unsigned int num = 1);
    void Backward(unsigned int num = 1);

    void MoveTo(int index);
    int GetCurrentKifuIndex();

    std::vector<std::string> GetKifuStrings();

    const std::array<std::array<KomaRef, 9>, 9>& GetMasume() const;
    const std::vector<KomaRef>& GetKomadaiBlack() const;
    const std::vector<KomaRef>& GetKomadaiWhite() const;

    std::wstring ToWStringKomadaiBlack() const;
    std::wstring ToWStringKomadaiWhite() const;

    std::string DebugString();
    void DebugPrint();

private:
    Board mBoard;
    std::shared_ptr<Kifu> mKifu = nullptr;
};
