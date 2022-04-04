#pragma once

#include <mbed.h>
#include <mutex>

class PPU {

public:
  static PPU &getInstance() {
    std::call_once(initInstanceFlag, &PPU::initSingleton);
    return *instance;
  }

private:
  PPU() = default;
  ~PPU() = default;
  PPU(const PPU &) = delete;
  PPU &operator=(const PPU &) = delete;

  static PPU *instance;
  static std::once_flag initInstanceFlag;

  static void initSingleton() { instance = new PPU; }

};

