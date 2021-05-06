#include "../include/mem.h"
#include "../include/mapper.h"
#include <iostream>

uint8_t splitBytes(uint16_t i) { return i & 0xff; }

MemoryDriver::MemoryDriver(int size) : size(size) {
  for (int i = 0; i < size; i++) {
    memory.push_back(0x00);
  }
};

uint16_t MemoryDriver::getUint16(uint16_t address) {
  return MemoryDriver::memory[address];
};

uint8_t MemoryDriver::getUint8(uint16_t address) {
  return splitBytes(memory[address]);
};

void MemoryDriver::setUint8(uint16_t address, uint8_t value) {
  memory[address] = value;
};

void MemoryDriver::setUint16(uint16_t address, uint16_t value) {
  memory[address] = value;
};
