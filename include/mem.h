#ifndef MEMORY
#define MEMORY

#include "../include/mapper.h"
#include <inttypes.h>
#include <vector>

class MemoryDriver {
public:
  std::vector<uint16_t> memory;
  int size;
  MemoryDriver(int size) : control(this), size(size) {
    for (int i = 0; i < size; i++) {
      memory.push_back(0x00);
    }
  };

  struct Controller : public MemoryDevice {
    MemoryDriver *parent;
    Controller(MemoryDriver *item);
    uint16_t getUint16(uint16_t address);

    uint8_t getUint8(uint16_t address);

    void setUint8(uint16_t address, uint8_t value);

    void setUint16(uint16_t address, uint16_t value);
  };
  Controller control;
};

#endif
