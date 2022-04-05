#pragma once
#include <mbed.h>

class SPI_BUS {
private:
  static SPI_BUS *p_instance;
  static Mutex s_mutex;

protected:
  SPI_BUS(){};
  ~SPI_BUS(){};

public:
  SPI_BUS(SPI_BUS &other) = delete;
  void operator=(const SPI_BUS &) = delete;

  static SPI_BUS *getInstance();
};
