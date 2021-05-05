#include "../include/mem.h"
#include "../include/mapper.h"
#include <iostream>

uint8_t splitBytes(uint16_t i) { return i & 0xff; }

uint16_t MemoryDriver::getUint16(uint16_t address) { return memory[address]; };

uint8_t MemoryDriver::getUint8(uint16_t address) {
  std::cout << memory.size() << std::endl;
  return splitBytes(memory[address]);
};

void MemoryDriver::setUint8(uint16_t address, uint8_t value) {
  memory[address] = value;
};

void MemoryDriver::setUint16(uint16_t address, uint16_t value) {
  memory[address] = value;
};
