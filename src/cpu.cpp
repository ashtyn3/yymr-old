#include "../include/cpu.h"
#include <array>
#include <iostream>

/*
Reads 16 bit integer out of memory.
*/
uint16_t CPU::readMemory(int address) {
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
