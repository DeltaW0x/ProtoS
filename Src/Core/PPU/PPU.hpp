#pragma once
#include <mbed.h>

class PPU {
private:
  static PPU *p_instance;
  static Mutex s_mutex;

protected:
  PPU(){};
  ~PPU(){};

public:
  PPU(PPU &other) = delete;
  void operator=(const PPU &) = delete;

  static PPU *getInstance();
};
