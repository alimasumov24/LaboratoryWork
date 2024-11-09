#include <iostream>
#include <fstream>
#include "bmp.h"
#include "realization.h"

int main() {
    std::cout << "Hello, please enter name of file: ";
    std::string input;
    std::getline(std::cin, input);
    std::cout << "Attempting to open file: " << input << std::endl; 

    try {
        BMP image(input); 
        BMP imageCounterClockwise = image;

        image.Rotate90();
        image.Save("output_clockwise.bmp");

        imageCounterClockwise.RotateCounter90();
        imageCounterClockwise.Save("output_counterclockwise.bmp");

        image.GaussianFilter();
        image.Save("output_gaussian.bmp");

        image.Downscale();
        image.Save("output_downscale.bmp");

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}