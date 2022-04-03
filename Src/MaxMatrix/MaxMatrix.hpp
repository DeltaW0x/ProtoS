/*
 * MaxMatrix
 * Version 1.0 Feb 2013
 * Copyright 2013 Oscar Kin-Chung Au
 * Adapted by DeltaWave0x
 */
#pragma once

#include <cstdint>
#include <chrono>

#include "mbed.h"

#define LSBFIRST 0
#define MSBFIRST 1

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
  private:
    uint8_t num;
    uint8_t buffer[120];

    DigitalOut *data;
    DigitalOut *clk;
    DigitalOut *load;

    void shiftOut(DigitalOut *dataPin, DigitalOut *clockPin, uint8_t bitOrder, uint8_t val);

  public:

    MaxMatrix(PinName dataPin, PinName loadPin, PinName clockPin, uint8_t _num);

    void setDot(uint8_t col, uint8_t row, uint8_t value);
    void setColumn(uint8_t col, uint8_t value);
    void setColumnAll(uint8_t col, uint8_t value);

    void writeSprite(int x, int y, const uint8_t *sprite);
    void fadeToFromSprite(int x, int y,uint8_t fadeTime, uint8_t targetBrightness, const uint8_t *sprite_new,const uint8_t *sprite_old);

    void reload();

    void setCommand(uint8_t command, uint8_t value);

    void clear();

    void setIntensity(uint8_t intensity);
    void init();
};