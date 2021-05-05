#include "../include/mem.h"
#include "../include/mapper.h"

MemoryDriver *parent;
MemoryDriver::Controller::Controller(MemoryDriver *item) : parent(item) {}
uint16_t MemoryDriver::Controller::getUint16(uint16_t address) {
  return parent->memory[address];
};

uint8_t MemoryDriver::Controller::getUint8(uint16_t address) {
  return parent->memory[address] & 0x00ff;
};

void MemoryDriver::Controller::setUint8(uint16_t address, uint8_t value) {
  parent->memory[address] = value & 0xff;
};

void MemoryDriver::Controller::setUint16(uint16_t address, uint16_t value) {
  parent->memory[address] = value;
};
