#pragma once

#include <memory>
#include <optional>
#include "shogi/Kifu.h"

/**
 * 棋譜ファイル読み取り
 */
namespace KifuReader {
    std::shared_ptr<Kifu> ReadFromFile(const std::string& filePath);
    std::shared_ptr<Kifu> Read(const std::string& content);
    std::shared_ptr<Kifu> Read(std::stringstream& ss);

    std::vector<MoveCommand> ParseAll(std::stringstream& stream);
    std::optional<MoveCommand> Parse(std::stringstream& lineStream);
    std::optional<MoveCommand> Parse(const std::string& id, const std::string& move);

    const std::pair<char, char>& PreviousDestination();
};
