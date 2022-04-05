#include "SPI_BUS.hpp"

SPI_BUS* SPI_BUS::p_instance{nullptr};
Mutex SPI_BUS::s_mutex;


SPI_BUS *SPI_BUS::getInstance() {
  s_mutex.lock();
  if (p_instance == nullptr) {
    p_instance = new SPI_BUS();
  }
  s_mutex.unlock();
  return p_instance;
}