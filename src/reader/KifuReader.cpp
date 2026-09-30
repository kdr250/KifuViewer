#include "KifuReader.h"

#include <algorithm>
#include <array>
#include <string>
#include <fstream>
#include <sstream>

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

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        if (!IsValid(lineStream)) {
            continue;
        }
        MoveCommand command = Parse(line);
    }

    return std::make_shared<Kifu>(commands);
}

bool KifuReader::IsValid(std::stringstream& lineStream)
{
    std::string id;
    while (!lineStream.eof()) {
        lineStream >> id;
        if (!IsNumeric(id)) {
            return false;
        }
    }

    return true;
}

MoveCommand KifuReader::Parse(std::stringstream& lineStream)
{
    std::string id, move, time;

    while (!lineStream.eof()) {
        lineStream >> id >> move >> time;
    }

    return Parse(move);
}

MoveCommand KifuReader::Parse(const std::string& move)
{
    MoveCommand result;
    // TODO: parse move into command

    // Example
    // #include <iostream>
    // #include <string>
    // #include <locale>
    // int main()
    // {
    //     std::setlocale(LC_ALL, "");
    //     std::wstring str = L"7六歩";
    //     for (wchar_t ch : str) {
    //         std::wcout << ch << std::endl;
    //     }
    //     return 0;
    // }

    return MoveCommand();
}
