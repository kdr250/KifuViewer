#include "KifuReader.h"

#include <algorithm>
#include <array>
#include <string>
#include <fstream>
#include <sstream>

#include "StringConverter.h"

const std::array<std::string, 9> suji {
    "１", "２", "３", "４", "５", "６", "７", "８", "９"
};

const std::array<std::string, 9> dan {
    "一", "二", "三", "四", "五", "六", "七", "八", "九"
};

bool IsNumeric(const std::string& str)
{
    if (str.empty()) {
        return false;
    }

    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

std::shared_ptr<Kifu> KifuReader::Read(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }

    std::vector<MoveCommand> commands;

    std::stringstream ss;
    ss << file.rdbuf();
    std::string utf8 = StringConverter::Encode(ss.str(), "SHIFT_JIS", "UTF-8");

    ss.str(utf8);
    ss.clear();

    std::string line;
    while (std::getline(ss, line)) {
        std::stringstream lineStream(line);
        std::optional<MoveCommand> result = Parse(lineStream);
        if (result.has_value()) {
            commands.push_back(*result);
        }
    }

    return std::make_shared<Kifu>(commands);
}

std::optional<MoveCommand> KifuReader::Parse(std::stringstream& lineStream)
{
    std::string id, move, time;

    lineStream >> id;
    if (id.starts_with('*') || !IsNumeric(id)) {
        return std::nullopt;
    }

    lineStream >> move;
    return Parse(id, move);
}

std::optional<MoveCommand> KifuReader::Parse(const std::string& id, const std::string& move)
{
    std::vector<std::string> targets = StringConverter::Split(move);

    // destination
    unsigned char destS, destT;

    // 筋
    auto iter = std::find(suji.begin(), suji.end(), targets[0]);
    if (iter == suji.end()) {
        return std::nullopt; // TODO: 同も扱えるようにする
    }
    destS = iter - suji.begin();

    // 段
    iter = std::find(dan.begin(), dan.end(), targets[1]);
    if (iter == dan.end()) {
        return std::nullopt;
    }
    destT = iter - dan.begin();

    // 駒
    KomaType type = Koma::GetType(targets[2]);

    // 成り
    bool isNaru = false; // TODO: Not yet implemented

    // origin
    unsigned char originS, originD;
    originS = std::stoi(targets[4]) - 1;
    originD = std::stoi(targets[5]) - 1;

    // direction
    int d = std::stoi(id);
    Direction direction = d % 2 == 1 ? Direction::Black : Direction::White;

    return MoveCommand {
        .origin = std::make_pair(originS, originD),
        .destination = std::make_pair(destS, destT),
        .type = type,
        .direction = direction,
        .isNaru = isNaru,
    };
}
