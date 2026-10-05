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

static std::pair<char, char> PREVIOUS_DESTINATION = std::make_pair(0, 0);

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
    // direction
    int d = std::stoi(id);
    Direction direction = d % 2 == 1 ? Direction::Black : Direction::White;

    std::vector<std::string> targets = StringConverter::Split(move);
    auto iter = targets.begin();

    if (*iter == "詰") {
        return std::nullopt;
    }

    // destination
    std::pair<char, char> destination;
    {
        if (*iter == "同") {
            destination = PREVIOUS_DESTINATION;
            iter += 2;
        } else {
            // 筋
            auto it = std::find(suji.begin(), suji.end(), *iter);
            if (it == suji.end()) {
                std::cout << "Illegal destination suji: id = " << id << ", move = " << move << std::endl;
                return std::nullopt;
            }
            destination.first = it - suji.begin();
            iter++;

            // 段
            it = std::find(dan.begin(), dan.end(), *iter);
            if (it == dan.end()) {
                std::cout << "Illegal destination dan: id = " << id << ", move = " << move << std::endl;
                return std::nullopt;
            }
            destination.second = it - dan.begin();
            iter++;

            PREVIOUS_DESTINATION = destination;
        }
    }

    // 駒
    std::string koma = *iter;
    if (koma == "成") {
        iter++;
        koma += *iter;
    }
    KomaType type = Koma::GetType(koma);
    iter++;

    // 上下右左直は無視
    if (*iter == "上" || *iter == "下" || *iter == "右" || *iter == "左" || *iter == "直") {
        iter++;
    }

    // 駒台
    std::pair<char, char> origin;
    if (*iter == "打") {
        origin = direction == Direction::Black ? MoveCommand::KOMADAI_BLACK : MoveCommand::KOMADAI_WHITE;
        iter++;
    }

    // 成り
    bool isNaru = false;
    if (iter != targets.end() && *iter == "成") {
        isNaru = true;
        iter++;
    }

    // origin
    if (origin != MoveCommand::KOMADAI_BLACK && origin != MoveCommand::KOMADAI_WHITE) {
        while (*iter != "(") {
            iter++;
        }

        iter++; // `(` の分
        origin.first = std::stoi(*iter) - 1;
        iter++;
        origin.second = std::stoi(*iter) - 1;
    }

    return MoveCommand {
        .origin = origin,
        .destination = destination,
        .type = type,
        .direction = direction,
        .isNaru = isNaru,
    };
}

const std::pair<char, char>& KifuReader::PreviousDestination()
{
    return PREVIOUS_DESTINATION;
}
