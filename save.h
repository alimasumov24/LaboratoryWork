#ifndef SAVE_H
#define SAVE_H

#include <string>
#include "bmp.h"

class BMP {
public:
    BMP(const std::string &filename);
    ~BMP() = default;
    void Save(const std::string &filename);
    void Rotate90();
    void RotateCounter90();
    void GaussianFilter();

private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<std::vector<Pixel>> data; 
};

#endif // SAVE_H