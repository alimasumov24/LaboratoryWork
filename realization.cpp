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

void BMP::GaussianFilter() {
    float kernel[3][3] = {
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
        {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}
    };

    std::vector<std::vector<Pixel>> tempData(infoHeader.height, std::vector<Pixel>(infoHeader.width));

    for (int y = 0; y < infoHeader.height; ++y) {
        for (int x = 0; x < infoHeader.width; ++x) {
            float sumRed = 0, sumGreen = 0, sumBlue = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int ny = y + ky;
                    int nx = x + kx;

                    if (ny >= 0 && ny < infoHeader.height && nx >= 0 && nx < infoHeader.width) {
                        sumRed += data[ny][nx].red * kernel[ky + 1][kx + 1];
                        sumGreen += data[ny][nx].green * kernel[ky + 1][kx + 1];
                        sumBlue += data[ny][nx].blue * kernel[ky + 1][kx + 1];
                    }
                }
            }

            tempData[y][x].red = static_cast<uint8_t>(sumRed);
            tempData[y][x].green = static_cast<uint8_t>(sumGreen);
            tempData[y][x].blue = static_cast<uint8_t>(sumBlue);
        }
    }

    data = tempData;
}