#pragma once

#include <string>
#include <vector>

namespace StringConverter {
    std::string Encode(const std::string& input, std::string inputCode, std::string outputCode);

    size_t GetUTF8CharLength(unsigned char loadingByte);

    std::vector<std::string> Split(const std::string& utf8Str);
}
