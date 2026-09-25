#include "Board.h"

#include <sstream>
#include <iostream>

void Board::Reset()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            mMasume[i][j] = nullptr;
        }
    }

    // 後手側
    mMasume[0][0] = Koma::New(KomaType::Kyo, Direction::White);
    mMasume[0][1] = Koma::New(KomaType::Keima, Direction::White);
    mMasume[0][2] = Koma::New(KomaType::Gin, Direction::White);
    mMasume[0][3] = Koma::New(KomaType::Kin, Direction::White);
    mMasume[0][4] = Koma::New(KomaType::Gyoku, Direction::White);
    mMasume[0][5] = Koma::New(KomaType::Kin, Direction::White);
    mMasume[0][6] = Koma::New(KomaType::Gin, Direction::White);
    mMasume[0][7] = Koma::New(KomaType::Keima, Direction::White);
    mMasume[0][8] = Koma::New(KomaType::Kyo, Direction::White);

    mMasume[1][1] = Koma::New(KomaType::Kaku, Direction::White);
    mMasume[1][7] = Koma::New(KomaType::Hisha, Direction::White);

    mMasume[2][0] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][1] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][2] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][3] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][4] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][5] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][6] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][7] = Koma::New(KomaType::Fu, Direction::White);
    mMasume[2][8] = Koma::New(KomaType::Fu, Direction::White);

    // 先手側
    mMasume[6][0] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][1] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][2] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][3] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][4] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][5] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][6] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][7] = Koma::New(KomaType::Fu, Direction::Black);
    mMasume[6][8] = Koma::New(KomaType::Fu, Direction::Black);

    mMasume[7][1] = Koma::New(KomaType::Hisha, Direction::Black);
    mMasume[7][7] = Koma::New(KomaType::Kaku, Direction::Black);

    mMasume[8][0] = Koma::New(KomaType::Kyo, Direction::Black);
    mMasume[8][1] = Koma::New(KomaType::Keima, Direction::Black);
    mMasume[8][2] = Koma::New(KomaType::Gin, Direction::Black);
    mMasume[8][3] = Koma::New(KomaType::Kin, Direction::Black);
    mMasume[8][4] = Koma::New(KomaType::Gyoku, Direction::Black);
    mMasume[8][5] = Koma::New(KomaType::Kin, Direction::Black);
    mMasume[8][6] = Koma::New(KomaType::Gin, Direction::Black);
    mMasume[8][7] = Koma::New(KomaType::Keima, Direction::Black);
    mMasume[8][8] = Koma::New(KomaType::Kyo, Direction::Black);

    mKomadaiBlack.clear();
    mKomadaiWhite.clear();
}

void Board::Move(const MoveCommand& command)
{
    auto& origin = command.origin;
    auto& destination = command.destination;
    auto& type = command.type;

    auto koma = mMasume[origin.second][origin.first];
    if (!koma || koma->Type() != type) {
        std::cout << "Illegal command" << std::endl;
        return;
    }

    auto targetKoma = mMasume[destination.second][destination.first];
    if (targetKoma) {
        if (targetKoma->Direction() == command.direction) {
            std::cout << "Illegal command" << std::endl;
            return;
        }
        targetKoma->Toru();
        if (command.direction == Direction::Black) {
            mKomadaiBlack.push_back(targetKoma);
        } else {
            mKomadaiWhite.push_back(targetKoma);
        }
    }

    mMasume[origin.second][origin.first] = nullptr;
    mMasume[destination.second][destination.first] = koma;
}

std::string Board::DebugString()
{
    std::stringstream ss;

    ss << std::endl;
    ss << "ーーーーーーーーーーーーーーーーーー" << std::endl;
    for (int i = 0; i < 9; ++i) {
        ss << "｜";
        for (int j = 8; j >= 0; --j) {
            auto koma = mMasume[i][j];
            if (koma) {
                ss << koma->ToString();
            } else {
                ss << "　";
            }
            ss << "｜";
        }
        ss << std::endl;
        ss << "ーーーーーーーーーーーーーーーーーー" << std::endl;
    }
    return ss.str();
}

void Board::DebugPrint()
{
    std::cout << DebugString() << std::endl;
}
