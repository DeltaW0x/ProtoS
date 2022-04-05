#include "PPU.hpp"


PPU* PPU::p_instance{nullptr};
Mutex PPU::s_mutex;


PPU *PPU::getInstance() {
  s_mutex.lock();
  if (p_instance == nullptr) {
    p_instance = new PPU();
  }
  s_mutex.unlock();
  return p_instance;
}