#ifndef REALIZATION_H
#define REALIZATION_H

#include <string>
#include "bmp.h"

class BMP {
public:
    BMP(const std::string &filename);
    ~BMP() = default;
    void Save(const std::string &filename); 
    
private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    
    std::vector<std::vector<Pixel>> data; 
};

#endif // REALIZATION_H