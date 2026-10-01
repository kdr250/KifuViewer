#pragma once

#include <memory>
#include <optional>
#include "shogi/Kifu.h"

/**
 * 棋譜ファイル読み取り
 */
namespace KifuReader {
    std::shared_ptr<Kifu> Read(const std::string& filePath);

    std::optional<MoveCommand> Parse(std::stringstream& lineStream);
    std::optional<MoveCommand> Parse(const std::string& id, const std::string& move);
};
