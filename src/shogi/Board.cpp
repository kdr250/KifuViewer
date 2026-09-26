#include "Board.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>

void Board::Initialize()
{
    mSavedCommands.clear();
    Reset();
}

void Board::Add(const MoveCommand& command)
{
    mSavedCommands.push_back(command);
}

void Board::Add(const std::vector<MoveCommand>& commands)
{
    mSavedCommands.insert(mSavedCommands.end(), commands.begin(), commands.end());
}

void Board::Reset()
{
    mKomadaiBlack.clear();
    mKomadaiWhite.clear();

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
}

bool Board::Move(const MoveCommand& command)
{
    auto& origin = command.origin;
    auto& destination = command.destination;
    auto& type = command.type;
    bool isNaru = command.isNaru;

    // 駒台
    if (origin == MoveCommand::KOMADAI_BLACK) {
        auto iter = std::find_if(mKomadaiBlack.begin(), mKomadaiBlack.end(), [type](auto& koma) {
            return koma->Type() == type;
        });
        if (iter == mKomadaiBlack.end()) {
            std::cout << "Illegal command" << std::endl;
            return false;
        }
        if (mMasume[destination.second][destination.first]) {
            std::cout << "Illegal command" << std::endl;
            return false;
        }
        mMasume[destination.second][destination.first] = *iter;
        mKomadaiBlack.erase(iter);
        return true;
    } else if (origin == MoveCommand::KOMADAI_WHITE) {
        auto iter = std::find_if(mKomadaiWhite.begin(), mKomadaiWhite.end(), [type](auto& koma) {
            return koma->Type() == type;
        });
        if (iter == mKomadaiWhite.end()) {
            std::cout << "Illegal command" << std::endl;
            return false;
        }
        if (mMasume[destination.second][destination.first]) {
            std::cout << "Illegal command" << std::endl;
            return false;
        }
        mMasume[destination.second][destination.first] = *iter;
        mKomadaiWhite.erase(iter);
        return true;
    }

    // 盤上
    auto koma = mMasume[origin.second][origin.first];
    if (!koma || koma->Type() != type) {
        std::cout << "Illegal command" << std::endl;
        return false;
    }
    if (isNaru) {
        koma->Naru();
    }

    auto targetKoma = mMasume[destination.second][destination.first];
    if (targetKoma) {
        if (targetKoma->Direction() == command.direction) {
            std::cout << "Illegal command" << std::endl;
            return false;
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

    return true;
}

bool Board::Move(const std::vector<MoveCommand>& commands)
{
    for (auto& command : commands) {
        if (!Move(command)) {
            return false;
        }
    }
    return true;
}

bool Board::Replay()
{
    Reset();
    return Move(mSavedCommands);
}

void Board::Back()
{
    if (mSavedCommands.empty()) {
        return;
    }
    mSavedCommands.pop_back();
}

void Board::Back(int count)
{
    if (mSavedCommands.size() <= count) {
        mSavedCommands.clear();
        return;
    }
    mSavedCommands.erase(mSavedCommands.end() - count, mSavedCommands.end());
}

std::string Board::DebugString()
{
    std::stringstream ss;
    ss << std::endl;

    std::map<std::string, int> komadai;
    for (auto& koma : mKomadaiWhite) {
        komadai[koma->ToString()] += 1;
    }
    ss << "後: ";
    for (auto& [komaName, count] : komadai) {
        ss << komaName << "x" << count << " ";
    }
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

    komadai.clear();
    for (auto& koma : mKomadaiBlack) {
        komadai[koma->ToString()] += 1;
    }
    ss << "先: ";
    for (auto& [komaName, count] : komadai) {
        ss << komaName << "x" << count << " ";
    }
    ss << std::endl;

    return ss.str();
}

void Board::DebugPrint()
{
    std::cout << DebugString() << std::endl;
}
