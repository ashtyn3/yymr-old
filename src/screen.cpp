#include "../include/screen.h"

uint16_t ScreenDriver::getUint16(uint16_t address) { return 0x0000; };

uint8_t ScreenDriver::getUint8(uint16_t address) { return 0x000; };

void ScreenDriver::setUint8(uint16_t address, uint8_t value){};

void ScreenDriver::setUint16(uint16_t address, uint16_t value) {
  char character = value & 0x00ff;

  uint16_t x = (address % 16) + 1;
  uint16_t y = floor(address / 16) + 1;
  std::cout << "\x1b[" << x * 2 << ";" << y << "H";
  std::cout << character;
};
