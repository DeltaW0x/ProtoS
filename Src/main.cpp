#include <mbed.h>
#include <cstdint>
#include <PinNames.h>
#include <mutex>

#include "MaxMatrix/MaxMatrix.hpp"
#include "Core/PPU.hpp"
#include "Core/SPI_BUS.hpp"

PinName DIN = A7;
PinName CS = A5;
PinName CLK = A6;

uint8_t MAX_N = 2;

PPU* PPU::instance = nullptr;
SPI_BUS* SPI_BUS::instance = nullptr;

std::once_flag PPU::initInstanceFlag;
std::once_flag SPI_BUS::initInstanceFlag;

int main()
{
    MaxMatrix *m = new MaxMatrix(DIN, CS, CLK, MAX_N);
    
}