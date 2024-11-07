#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t fType{0x4D42};  
    uint32_t fSize{0};       
    uint16_t reserved1{0};      
    uint16_t reserved2{0};      
    uint32_t offsetData{0};     
};

struct BMPInfoHeader {
    uint32_t size{0};            
    int32_t width{0};            
    int32_t height{0};                             
    uint16_t planes{1};          
    uint16_t bitCount{0};        
    uint32_t compression{0};     
    uint32_t sizeImage{0};       
    int32_t xPixelsPerMeter{0};  
    int32_t yPixelsPerMeter{0};  
    uint32_t colorsUsed{0};      
    uint32_t colorsImportant{0}; 
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

class BMPImage {
public:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<Pixel> pixels;

    BMPImage(int32_t width, int32_t height) {
        infoHeader.width = width;
        infoHeader.height = height;
        pixels.resize(width * height);
    }

    Pixel& getPixel(int32_t x, int32_t y) {
        return pixels[y * infoHeader.width + x];
    }

    const Pixel& getPixel(int32_t x, int32_t y) const {
        return pixels[y * infoHeader.width + x];
    }
};

#endif // BMP_H