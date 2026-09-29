#pragma once

#include <memory>
#include "shogi/Kifu.h"

/**
 * 棋譜ファイル読み取り
 */
namespace KifuReader {
    std::shared_ptr<Kifu> Read(const std::string& filePath);

    bool IsValid(std::stringstream& lineStream);
    MoveCommand Parse(std::stringstream& lineStream);
    MoveCommand Parse(const std::string& move);
};
