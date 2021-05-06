#ifndef MEMORY
#define MEMORY

#include "../include/mapper.h"
#include <inttypes.h>
#include <vector>

struct MemoryDriver : public MemoryDevice {
public:
  std::vector<uint16_t> memory;
  int size;
  MemoryDriver(int size);

  uint16_t getUint16(uint16_t address) override;

  uint8_t getUint8(uint16_t address) override;

  void setUint8(uint16_t address, uint8_t value) override;

  void setUint16(uint16_t address, uint16_t value) override;
};

#endif
