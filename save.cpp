#include <iostream>
#include <fstream>
#include "bmp.h"
#include "save.h"


BMP::BMP(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file.");
    }

    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (header.fType != 0x4D42) {
        throw std::runtime_error("File format is not BMP.");
    }

    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    infoHeader.height = std::abs(infoHeader.height);
    infoHeader.width = std::abs(infoHeader.width);

    if (infoHeader.width == 0 || infoHeader.height == 0) {
        throw std::runtime_error("Unacceptable file size.");
    }
    file.seekg(header.offsetData, file.beg);

    data.resize(infoHeader.height, std::vector<Pixel>(infoHeader.width));

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            file.read(reinterpret_cast<char *>(&data[i][j]), sizeof(Pixel));
            if (!file) {
                throw std::runtime_error("Error reading file.");
            }
        }
    }

    file.close();
}
