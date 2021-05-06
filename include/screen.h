#ifndef screen
#define screen
#include "../include/mapper.h"
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <vector>

struct ScreenDriver : public MemoryDevice {
  uint16_t getUint16(uint16_t address) override;
  void setUint16(uint16_t address, uint16_t value) override;
  uint8_t getUint8(uint16_t address) override;
  void setUint8(uint16_t address, uint8_t value) override;
};

#endif
