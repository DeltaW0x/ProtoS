#pragma once

#include <stdint.h>

#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08
#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0a
#define max7219_reg_scanLimit   0x0b
#define max7219_reg_shutdown    0x0c
#define max7219_reg_displayTest 0x0f

class MaxMatrix{

    public:

        MaxMatrix(uint8_t data, uint8_t load, uint8_t clock, uint8_t num);

        void init();
        void clear();

        void setCommand(uint8_t command, uint8_t value);
        void setIntensity(uint8_t intensity);
        void setColumn(uint8_t col, uint8_t value);
        void setColumnAll(uint8_t col, uint8_t value);
        void setDot(uint8_t col, uint8_t row, uint8_t value);

        void writeSprite(int x, int y, const uint8_t* sprite);
    
        void shiftLeft(bool rotate = false, bool fill_zero = true);
        void shiftRight(bool rotate = false, bool fill_zero = true);
        void shiftUp(bool rotate = false);
        void shiftDown(bool rotate = false);


    private:

         uint8_t data;
         uint8_t load;
         uint8_t clock;
         uint8_t num;
         uint8_t buffer[112]; 

         void reload();

};

