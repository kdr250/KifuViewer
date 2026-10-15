#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace FileManager {

    inline std::string ProcessUploadedFile(std::string fileName)
    {
        std::string filePath = "/tmp/" + fileName;
        std::ifstream file(filePath, std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Failed to open virtual file: " << filePath << std::endl;
            return std::string();
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        return content;
    }
}
