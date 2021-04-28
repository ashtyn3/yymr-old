#include "../include/cpu.h"
#include <array>
#include <iostream>

uint16_t mergeNumbers(uint8_t f, uint8_t s) { return (f << 8) | (s); }

/*
Reads 8 bit integer out of memory.
*/
uint8_t CPU::readMemory(int address) {
  if (address >= int(memory.size())) {
    std::cerr << "Cannot read memory address: " << address << std::endl;
    return 0;
  }
  return memory[address];
}

void CPU::initMemory(int size) {
  for (int i = 0; i < size; i++) {
    memory.push_back(0x00);
  }
  for (int i = 0; i < 11; i++) {
    reg[i] = 0x0000;
  }
}

uint16_t CPU::getRegister(int address) {
  if (address > 9) {
    std::cerr << "Cannot get register: " << address << std::endl;
    return 0;
  }

  return reg[address];
}

void CPU::setRegister(int address, uint16_t value) {
  if (address > 9) {
    std::cerr << "Cannot set register: " << address << std::endl;
    return;
  }
  reg[address] = value;
}

uint8_t CPU::fetch() {
  int currentPointer = CPU::getRegister(ip);
  uint8_t pointer = CPU::readMemory(currentPointer);
  CPU::setRegister(ip, currentPointer + 1);
  return pointer;
}

uint16_t CPU::fetch16() {
  int currentPointer = CPU::getRegister(ip);
  uint8_t p1 = memory[currentPointer];
  uint8_t p2 = memory[currentPointer + 1];
  uint16_t pointer = mergeNumbers(p1, p2);
  CPU::setRegister(ip, currentPointer + 2);

  return pointer;
}

void CPU::execute() {}
