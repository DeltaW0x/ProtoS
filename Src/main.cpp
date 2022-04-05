#include <mbed.h>
#include <cstdint>
#include <PinNames.h>

#include "MaxMatrix/MaxMatrix.hpp"
#include "Core/PPU/PPU.hpp"
#include "Core/SPI_BUS/SPI_BUS.hpp"


PinName DIN = A7;
PinName CS = A5;
PinName CLK = A6;

uint8_t MAX_N = 2;

int main()
{
    MaxMatrix *m = new MaxMatrix(DIN, CS, CLK, MAX_N);
    
}