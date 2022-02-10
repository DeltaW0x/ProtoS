#include "mbed.h"
#include <cstdint>
#include <MaxMatrix/MaxMatrix.hpp>


const uint8_t mawL[] =      {32, 8,
                        0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b00011111, 0b01111000, 0b11100000, 0b10000000,
                        0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11100000, 0b01111000, 0b00011110, 0b00000111,
                        0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000111, 0b00011110, 0b01111000, 0b11100000,
                        0b00000100, 0b00011110, 0b01111011, 0b11100011, 0b11111111, 0b00000000, 0b00000000, 0b00000000
                       };
    




int main(){

    MaxMatrix* m = new MaxMatrix(A2,A1,A0,4);

    m->init();
    m->setIntensity(8);
    m->clear();

    while(true){
        m->writeSprite(0,0,mawL);
    }
}