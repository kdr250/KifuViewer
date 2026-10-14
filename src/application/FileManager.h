#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace FileManager {

    inline void ProcessUploadedFile(std::string fileName)
    {
        std::string filePath = "/tmp/" + fileName;
        std::ifstream file(filePath, std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Failed to open virtual file: " << filePath << std::endl;
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        std::cout << "--- C++ Received File Content ---" << std::endl;
        std::cout << content << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }
}
