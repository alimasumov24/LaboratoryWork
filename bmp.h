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
    uint32_t offData{0};     
};

struct BMPInfoHeader {
    uint32_t size{0};            
    int32_t width{0};            
    int32_t height{0};                                       
    uint16_t planes{1};          
    uint16_t biCount{0};        
    uint32_t compression{0};     
    uint32_t sizeImage{0};       
    int32_t xPixelsPerMeter{0};  
    int32_t yPixelsPerMeter{0};  
    uint32_t colorsUsed{0};      
    uint32_t colorsImportant{0}; 
};


#endif // BMP_H