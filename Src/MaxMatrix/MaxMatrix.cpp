#include <cstdint>

#include "MaxMatrix.hpp"

MaxMatrix::MaxMatrix(PinName _data, PinName _load, PinName _clock, uint8_t _num)
{
    m_data = new DigitalOut(_data);
    m_load = new DigitalOut(_load);
    m_clock = new DigitalOut(_clock);

    for (int i = 0; i < 112; i++)
    {
        m_buffer[i] = 0;
    }
}
MaxMatrix::~MaxMatrix()
{
    delete m_data;
    delete m_load;
    delete m_clock;
}

void MaxMatrix::init()
{
    m_clock->write(1);

    setCommand(max7219_reg_scanLimit, 0x07);
    setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
    setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    setCommand(max7219_reg_displayTest, 0x00); // no display test

    // empty registers, turn all LEDs off
    clear();

    setIntensity(0x0f); // the first 0x0f is the value you can set
}

void MaxMatrix::setIntensity(uint8_t intensity)
{
    setCommand(max7219_reg_intensity, intensity);
}

void MaxMatrix::clear()
{
    for (int i = 0; i < 8; i++)
        setColumnAll(i, 0);

    for (int i = 0; i < 112; i++)
        m_buffer[i] = 0;
}

void MaxMatrix::setCommand(uint8_t command, uint8_t value)
{
    m_load->write(0);
    for (int i = 0; i < m_num; i++)
    {
        shiftOut(*m_data, *m_clock, bitOrder::MSBFIRST, command);
        shiftOut(*m_data, *m_clock, bitOrder::MSBFIRST, value);
    }
    m_load->write(0);
    m_load->write(1);
}

void MaxMatrix::setColumn(uint8_t col, uint8_t value)
{
    int n = col / 8;
    int c = col % 8;
    m_load->write(0);

    for (int i = 0; i < m_num; i++)
    {
        if (i == n)
        {
            shiftOut(*m_data, *m_clock, MSBFIRST, c + 1);
            shiftOut(*m_data, *m_clock, MSBFIRST, value);
        }
        else
        {
            shiftOut(*m_data, *m_clock, MSBFIRST, 0);
            shiftOut(*m_data, *m_clock, MSBFIRST, 0);
        }
    }
    m_load->write(0);
    m_load->write(1);

    m_buffer[col] = value;
}

void MaxMatrix::setColumnAll(uint8_t col, uint8_t value)
{
    m_load->write(0);
    for (int i = 0; i < m_num; i++)
    {
        shiftOut(*m_data, *m_clock, MSBFIRST, col + 1);
        shiftOut(*m_data, *m_clock, MSBFIRST, value);
        m_buffer[col * i] = value;
    }
    m_load->write(0);
    m_load->write(1);
}

void MaxMatrix::setDot(uint8_t col, uint8_t row, uint8_t value)
{
    bitWrite(m_buffer[col], row, value);

    int n = col / 8;
    int c = col % 8;
    m_load->write(0);
    for (int i = 0; i < m_num; i++)
    {
        if (i == n)
        {
            shiftOut(*m_data, *m_clock, MSBFIRST, c + 1);
            shiftOut(*m_data, *m_clock, MSBFIRST, m_buffer[col]);
        }
        else
        {
            shiftOut(*m_data, *m_clock, MSBFIRST, 0);
            shiftOut(*m_data, *m_clock, MSBFIRST, 0);
        }
    }
    m_load->write(0);
    m_load->write(1);
}

void MaxMatrix::writeSprite(int x, int y, const uint8_t *sprite)
{
    int w = sprite[0];
    int h = sprite[1];

    if (h == 8 && y == 0)
        for (int i = 0; i < w; i++)
        {
            int c = x + i;
            if (c >= 0 && c < 112)
                setColumn(c, sprite[i + 2]);
        }
    else
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
            {
                int c = x + i;
                int r = y + j;
                if (c >= 0 && c < 112 && r >= 0 && r < 8)
                    setDot(c, r, bitRead(sprite[i + 2], j));
            }
}

void MaxMatrix::reload()
{
    for (int i = 0; i < 8; i++)
    {
        int col = i;
        m_load->write(0);
        for (int j = 0; j < m_num; j++)
        {
            shiftOut(*m_data, *m_clock, MSBFIRST, i + 1);
            shiftOut(*m_data, *m_clock, MSBFIRST, m_buffer[col]);
            col += 8;
        }
        m_load->write(0);
        m_load->write(1);
    }
}

void MaxMatrix::shiftLeft(bool rotate, bool fill_zero)
{
    uint8_t old = m_buffer[0];
    int i;
    for (i = 0; i < 112; i++)
    {
        m_buffer[i] = m_buffer[i + 1];
    }

    if (rotate)
    {
        m_buffer[m_num * 8 - 1] = old;
    }

    else if (fill_zero)
    {
        m_buffer[m_num * 8 - 1] = 0;
    }

    reload();
}

void MaxMatrix::shiftRight(bool rotate, bool fill_zero)
{
    int last = m_num * 8 - 1;
    uint8_t old = m_buffer[last];
    int i;
    for (i = 111; i > 0; i--)
    {
        m_buffer[i] = m_buffer[i - 1];
    }
    if (rotate)
    {
        m_buffer[0] = old;
    }
    else if (fill_zero)
    {
        m_buffer[0] = 0;
    }

    reload();
}

void MaxMatrix::shiftUp(bool rotate)
{
    for (int i = 0; i < m_num * 8; i++)
    {
        bool b = m_buffer[i] & 1;
        m_buffer[i] >>= 1;
        if (rotate)
        {
            bitWrite(m_buffer[i], 7, b);
        }
    }
    reload();
}

void MaxMatrix::shiftDown(bool rotate)
{
    for (int i = 0; i < m_num * 8; i++)
    {
        bool b = m_buffer[i] & 128;
        m_buffer[i] <<= 1;
        if (rotate)
        {
            bitWrite(m_buffer[i], 0, b);
        }
    }
    reload();
}

void MaxMatrix::shiftOut(DigitalOut &dataPin, DigitalOut &clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (bitOrder == bitOrder::LSBFIRST)
        {
            dataPin.write(val & 1);
            val >>= 1;
        }
        else
        {
            dataPin.write((val & 128) != 0);
            val <<= 1;
        }

        clockPin.write(1);
        clockPin.write(0);
    }
}