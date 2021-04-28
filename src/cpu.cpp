#include "../include/cpu.h"
#include "../include/opcodes.h"
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

uint8_t split(uint16_t i) { return i & 0xff; }

uint8_t CPU::fetch() {
  int currentPointer = CPU::getRegister(ip);
  uint8_t pointer = CPU::readMemory(currentPointer);
  CPU::setRegister(ip, currentPointer + 1);
  return split(pointer);
}

uint16_t CPU::fetch16() {
  int currentPointer = CPU::getRegister(ip);
  uint8_t p1 = CPU::readMemory(currentPointer);
  CPU::setRegister(ip, currentPointer + 1);
  return p1;
}

void CPU::execute(uint8_t current) {
  switch (current) {
  case MOV_LIT_REG: {
    uint16_t lit = fetch16();
    uint8_t reg = fetch();
    CPU::setRegister(reg, lit);
    break;
  }
  case MOV_REG_REG: {
    uint8_t regFrom = fetch();
    uint8_t regTo = fetch();
    uint16_t value = CPU::getRegister(regFrom);
    CPU::setRegister(regFrom, value);
    break;
  }
  case MOV_REG_MEM: {
    uint8_t regFrom = fetch();
    uint16_t address = fetch16();
    uint16_t value = CPU::getRegister(regFrom);
    // uint8_t chunks = split(value);
    memory[address] = value;
    break;
  }
  case MOV_MEM_REG: {
    uint16_t address = fetch16();
    uint8_t regTo = fetch();
    CPU::setRegister(regTo, memory[address]);
    break;
  }
  case ADD_REG_REG: {
    uint8_t reg1 = fetch();
    uint8_t reg2 = fetch();
    uint16_t value1 = CPU::getRegister(reg1);
    uint16_t value2 = CPU::getRegister(reg2);
    CPU::setRegister(acc, value1 + value2);
    break;
  }
  case JMP_NOT_EQ: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value != CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
  }
  }
}

void CPU::step() {
  uint8_t instruction = CPU::fetch();
  CPU::execute(instruction);
}
