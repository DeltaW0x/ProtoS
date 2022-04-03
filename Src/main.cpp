#include "mbed.h"
#include <MaxMatrix/MaxMatrix.hpp>
#include <chrono>
#include <cstdint>


/*const uint8_t noseLeft[] = {8, 8,
                         0b00000000,
                         0b01111111,
                         0b11111110,
                         0b11000000,
                         0b11000000,
                         0b10000000,
                         0b00000000,
                         0b00000000
                        };

const uint8_t mawL[] =    {32, 8,
                        0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b00011111, 0b01111000, 0b11100000, 0b10000000,
                        0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11100000, 0b01111000, 0b00011110, 0b00000111,
                        0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000111, 0b00011110, 0b01111000, 0b11100000,
                        0b00000100, 0b00011110, 0b01111011, 0b11100011, 0b11111111, 0b00000000, 0b00000000, 0b00000000
                       };

const uint8_t EyeL[] =    {16, 8,
                        0b00000000, 0b00000111, 0b00011111, 0b01111111, 0b11100000, 0b10000000, 0b00000000, 0b00000000,
                        0b11110000, 0b11111100, 0b11111110, 0b11111111, 0b00001111, 0b00000110, 0b00000000, 0b00000000
                       };
*/

const uint8_t square[] =    {8, 8,
                        0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
                        0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111
                       };




#define t 2ms
int main()
{
    MaxMatrix *m = new MaxMatrix(A7, A5, A6, 2);
    Timer fast;
    m->init();

    m->clear();

    while (true)
    {
       // m->writeSprite(0, 0, EyeL);

       for (int i = 0; i < 16; i++){
           fast.start();

           do{
           m->setIntensity(15-i);
           m->writeSprite(0, 0, square);
           ThisThread::sleep_for(t);
           m->clear();
           m->setIntensity(i);
           m->writeSprite(8, 0, square);
           ThisThread::sleep_for(t);
           m->clear();
           }while(fast.elapsed_time() < 50ms);
         fast.stop();
         fast.reset();
       }
       
       for (int i = 0; i < 16; i ++){
           fast.start();

           do{
           m->setIntensity(i);
           m->writeSprite(0, 0, square);
           ThisThread::sleep_for(t);
           m->clear();
           m->setIntensity(15-i);
           m->writeSprite(8, 0, square);
           ThisThread::sleep_for(t);
           m->clear();
           }while(fast.elapsed_time() < 50ms);
         fast.stop();
         fast.reset();
       }
       
    }
}