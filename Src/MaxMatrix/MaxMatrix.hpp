#pragma once

#include "mbed.h"
#include <stdint.h>

#define max7219_reg_noop 0x00
#define max7219_reg_digit0 0x01
#define max7219_reg_digit1 0x02
#define max7219_reg_digit2 0x03
#define max7219_reg_digit3 0x04
#define max7219_reg_digit4 0x05
#define max7219_reg_digit5 0x06
#define max7219_reg_digit6 0x07
#define max7219_reg_digit7 0x08
#define max7219_reg_decodeMode 0x09
#define max7219_reg_intensity 0x0a
#define max7219_reg_scanLimit 0x0b
#define max7219_reg_shutdown 0x0c
#define max7219_reg_displayTest 0x0f

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

class MaxMatrix
{

  public:
    MaxMatrix(PinName data, PinName load, PinName clock, uint8_t num);
    ~MaxMatrix();

    void init();
    void clear();

    void setCommand(uint8_t command, uint8_t value);
    void setIntensity(uint8_t intensity);
    void setColumn(uint8_t col, uint8_t value);
    void setColumnAll(uint8_t col, uint8_t value);
    void setDot(uint8_t col, uint8_t row, uint8_t value);

    void writeSprite(int x, int y, const uint8_t *sprite);

    void shiftLeft(bool rotate = false, bool fill_zero = true);
    void shiftRight(bool rotate = false, bool fill_zero = true);
    void shiftUp(bool rotate = false);
    void shiftDown(bool rotate = false);

  private:
    DigitalOut *m_data;
    DigitalOut *m_load;
    DigitalOut *m_clock;

    uint8_t m_num;
    uint8_t m_buffer[112];

    enum bitOrder
    {
        MSBFIRST,
        LSBFIRST
    };

    void reload();

    void shiftOut(DigitalOut &dataPin, DigitalOut &clockPin, uint8_t bitOrder, uint8_t val);
};
