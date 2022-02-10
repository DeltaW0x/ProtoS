
#include "MaxMatrix/MaxMatrix.hpp"
#include "mbed.h"
#include <cstdint>

MaxMatrix *matrix;

const uint8_t mawL[] = {32,         8,          0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b00011111,
                        0b01111000, 0b11100000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
                        0b11100000, 0b01111000, 0b00011110, 0b00000111, 0b00000000, 0b00000000, 0b00000000,
                        0b00000001, 0b00000111, 0b00011110, 0b01111000, 0b11100000, 0b00000100, 0b00011110,
                        0b01111011, 0b11100011, 0b11111111, 0b00000000, 0b00000000, 0b00000000};

int main()
{
    PinName CS = D6;
    PinName DIN = D7;
    PinName CLK = D5;

    uint8_t maxInUse = 4;

    matrix = new MaxMatrix(DIN,CS,CLK,maxInUse);

    matrix->init();
    matrix->clear();
    matrix->setIntensity(3);
    matrix->clear();

    
    matrix->writeSprite(0,0,mawL);
}
