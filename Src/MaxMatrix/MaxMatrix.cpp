/*
 * MaxMatrix
 * Version 1.0 Feb 2013
 * Copyright 2013 Oscar Kin-Chung Au
 * Adapted by DeltaWave0x
 */
 

#include "MaxMatrix.hpp"

MaxMatrix::MaxMatrix(PinName dataPin, PinName loadPin, PinName clockPin, uint8_t _num)
{
    num = _num;

    data = new DigitalOut(dataPin);
    clk = new DigitalOut(clockPin);
    load = new DigitalOut(loadPin);

    for (int i = 0; i < 120; i++)
    {
        buffer[i] = 0;
    }
}

void MaxMatrix::setDot(uint8_t col, uint8_t row, uint8_t value)
{
    bitWrite(buffer[col], row, value);

    int n = col / 8;
    int c = col % 8;
    load->write(0);
    for (int i = 0; i < num; i++)
    {
        if (i == n)
        {
            shiftOut(data, clk, MSBFIRST, c + 1);
            shiftOut(data, clk, MSBFIRST, buffer[col]);
        }
        else
        {
            shiftOut(data, clk, MSBFIRST, 0);
            shiftOut(data, clk, MSBFIRST, 0);
        }
    }
    load->write(0);
    load->write(1);
}

void MaxMatrix::setColumn(uint8_t col, uint8_t value)
{
    int n = col / 8;
    int c = col % 8;
    load->write(0);
    for (int i = 0; i < num; i++)
    {
        if (i == n)
        {
            shiftOut(data, clk, MSBFIRST, c + 1);
            shiftOut(data, clk, MSBFIRST, value);
        }
        else
        {
            shiftOut(data, clk, MSBFIRST, 0);
            shiftOut(data, clk, MSBFIRST, 0);
        }
    }
    load->write(0);
    load->write(1);

    buffer[col] = value;
}

void MaxMatrix::setColumnAll(uint8_t col, uint8_t value)
{
    load->write(0);
    for (int i = 0; i < num; i++)
    {
        shiftOut(data, clk, MSBFIRST, col + 1);
        shiftOut(data, clk, MSBFIRST, value);
        buffer[col * i] = value;
    }
    load->write(0);
    load->write(1);
}

void MaxMatrix::writeSprite(int x, int y, const uint8_t *sprite)
{
    int w = sprite[0];
    int h = sprite[1];

    if (h == 8 && y == 0)
        for (int i = 0; i < w; i++)
        {
            int c = x + i;
            if (c >= 0 && c < 120)
                setColumn(c, sprite[i + 2]);
        }
    else
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
            {
                int c = x + i;
                int r = y + j;
                if (c >= 0 && c < 120 && r >= 0 && r < 8)
                    setDot(c, r, bitRead(sprite[i + 2], j));
            }
}

void MaxMatrix::reload()
{
    for (int i = 0; i < 8; i++)
    {
        int col = i;
        load->write(0);
        for (int j = 0; j < num; j++)
        {
            shiftOut(data, clk, MSBFIRST, i + 1);
            shiftOut(data, clk, MSBFIRST, buffer[col]);
            col += 8;
        }
        load->write(0);
        load->write(1);
    }
}

void MaxMatrix::setCommand(uint8_t command, uint8_t value)
{
    load->write(0);
    for (int i = 0; i < num; i++)
    {
        shiftOut(data, clk, MSBFIRST, command);
        shiftOut(data, clk, MSBFIRST, value);
    }
    load->write(0);
    load->write(1);
}

void MaxMatrix::clear()
{
    for (int i = 0; i < 8; i++)
        setColumnAll(i, 0);

    for (int i = 0; i < 120; i++)
        buffer[i] = 0;
}

void MaxMatrix::setIntensity(uint8_t intensity)
{
    setCommand(max7219_reg_intensity, intensity);
}

void MaxMatrix::init()
{
    clk->write(1);

    setCommand(max7219_reg_scanLimit, 0x07);
    setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
    setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    setCommand(max7219_reg_displayTest, 0x00); // no display test

    // empty registers, turn all LEDs off
    clear();

    setIntensity(0x0f); // the first 0x0f is the value you can set
}

void MaxMatrix::shiftOut(DigitalOut *dataPin, DigitalOut *clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (bitOrder == LSBFIRST)
            dataPin->write(!!(val & (1 << i)));
        else
            dataPin->write(!!(val & (1 << (7 - i))));

        clockPin->write(1);
        clockPin->write(0);
    }
}