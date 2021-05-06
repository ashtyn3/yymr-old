#include "../include/mapper.h"
#include <iostream>

void MemoryMapper::map(MemoryDevice *device, uint16_t start, uint16_t end,
                       uint8_t remap) {
  MemoryRange range = {device, start, end, remap};
  MemoryMapper::ranges.insert(ranges.begin(), range);
}

MemoryRange MemoryMapper::find(uint16_t address) {
  MemoryRange found;
  for (int i = 0; i < MemoryMapper::ranges.size(); i++) {
    MemoryRange reg = ranges[i];
    if (address >= reg.start && address <= reg.end) {
      found = reg;
    }
  }

  return found;
}

uint16_t MemoryMapper::getUint16(uint16_t address) {
  MemoryRange region = MemoryMapper::find(address);
  uint16_t Final = 0x0000;
  if (region.remap == 1) {
    Final = address - region.start;
  } else {
    Final = address;
  }
  return region.device->getUint16(Final);
}

void MemoryMapper::setUint16(uint16_t address, uint16_t value) {
  MemoryRange region = MemoryMapper::find(address);
  uint16_t Final = 0x0000;
  if (region.remap == 1) {
    Final = address - region.start;
  } else {
    Final = address;
  }

  region.device->setUint16(Final, value);
}

uint8_t MemoryMapper::getUint8(uint16_t address) {
  MemoryRange region = MemoryMapper::find(address);
  uint16_t Final = 0x0000;
  if (region.remap == 1) {
    Final = address - region.start;
  } else {
    Final = address;
  }
  return region.device->getUint8(Final) & 0xff;
}

void MemoryMapper::setUint8(uint16_t address, uint8_t value) {
  MemoryRange region = MemoryMapper::find(address);
  uint16_t Final = 0x0000;
  if (region.remap == 1) {
    Final = address - region.start;
  } else {
    Final = address;
  }

  region.device->setUint8(Final, value);
}
