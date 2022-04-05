#pragma once

#include <mbed.h>
#include <mutex>

class SPI_BUS {

public:
  static SPI_BUS &getInstance() {
    std::call_once(initInstanceFlag, &SPI_BUS::initSingleton);
    return *instance;
  }

private:
  SPI_BUS() = default;
  ~SPI_BUS() = default;
  SPI_BUS(const SPI_BUS &) = delete;
  SPI_BUS &operator=(const SPI_BUS &) = delete;

  static SPI_BUS *instance;
  static std::once_flag initInstanceFlag;

  static void initSingleton() { instance = new SPI_BUS; }

};

