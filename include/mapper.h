#ifndef mapper
#define mapper
#include <functional>
#include <stdint.h>
#include <string>
#include <vector>

struct MemoryDevice {
  void setUint16(uint16_t address, uint16_t value);
  uint16_t getUint16(uint16_t address);

  void setUint8(uint16_t address, uint8_t value);
  uint16_t getUint8(uint16_t address);
};

struct MemoryRange {
  MemoryDevice device;
  uint16_t start;
  uint16_t end;
  uint8_t remap;
  std::string name;
};

class MemoryMapper {
public:
  void unmap();
  std::vector<MemoryRange> ranges;
  void map(MemoryDevice device, uint16_t start, uint16_t end, uint8_t remap);

  MemoryRange find(uint16_t find);

  void setUint16(uint16_t address, uint16_t value);
  uint16_t getUint16(uint16_t address);

  void setUint8(uint16_t address, uint8_t value);
  uint8_t getUint8(uint16_t address);
};

#endif
