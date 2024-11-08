#include <iostream>
#include <fstream>
#include "bmp.h"
#include "realization.h"


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

void BMP::Save(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error saving file."); 
    }

    file.write(reinterpret_cast<const char *>(&header), sizeof(header));
    file.write(reinterpret_cast<const char *>(&infoHeader), sizeof(infoHeader));

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            file.write(reinterpret_cast<const char *>(&data[i][j]), sizeof(Pixel));
        }
    }
    file.close();
}

void BMP::Rotate90() {
    std::vector<std::vector<Pixel>> rotatedData(infoHeader.width, std::vector<Pixel>(infoHeader.height));

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            rotatedData[j][infoHeader.height - i - 1] = data[i][j];
        }
    }

    data = rotatedData;
    std::swap(infoHeader.width, infoHeader.height);
}

void BMP::RotateCounter90() {
    std::vector<std::vector<Pixel>> rotatedData(infoHeader.width, std::vector<Pixel>(infoHeader.height));

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            rotatedData[infoHeader.width - j - 1][i] = data[i][j];
        }
    }

    data = rotatedData;
    std::swap(infoHeader.width, infoHeader.height);
}