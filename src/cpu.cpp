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

void CPU::initMemory() {
  for (int i = 0; i < memoryLimit; i++) {
    memory.push_back(0x00);
  }
  for (int i = 0; i < 12; i++) {
    reg[i] = 0x0000;
  }
  reg[sp] = 0x100;
  reg[fp] = 0x100;
}

void CPU::pushState() {
  CPU::push(CPU::getRegister(r1));
  CPU::push(CPU::getRegister(r2));
  CPU::push(CPU::getRegister(r3));
  CPU::push(CPU::getRegister(r4));
  CPU::push(CPU::getRegister(r5));
  CPU::push(CPU::getRegister(r6));
  CPU::push(CPU::getRegister(r7));
  CPU::push(CPU::getRegister(r8));
  CPU::push(CPU::getRegister(ip));
  CPU::push(CPU::stackFrameSize + 1);

  CPU::setRegister(fp, CPU::getRegister(sp));
  CPU::stackFrameSize = 0;
}

void CPU::popState() {
  uint16_t framePointer = CPU::getRegister(fp);
  CPU::setRegister(sp, framePointer);
  CPU::stackFrameSize = CPU::pop();
  uint16_t stackStateSize = CPU::stackFrameSize;
  CPU::setRegister(ip, pop());
  CPU::setRegister(r8, CPU::pop());
  CPU::setRegister(r7, CPU::pop());
  CPU::setRegister(r6, CPU::pop());
  CPU::setRegister(r5, CPU::pop());
  CPU::setRegister(r4, CPU::pop());
  CPU::setRegister(r3, CPU::pop());
  CPU::setRegister(r2, CPU::pop());
  CPU::setRegister(r1, CPU::pop());

  uint16_t nArgs = CPU::pop();
  for (int i = 0; i < nArgs; i++) {
    CPU::pop();
  }
  CPU::setRegister(fp, framePointer + stackStateSize);
}

uint16_t CPU::getRegister(int address) {
  if (address > 11) {
    std::cerr << "Cannot get register: " << address << std::endl;
    return 0;
  }

  return reg[address];
}

void CPU::setRegister(int address, uint16_t value) {
  if (address > 11) {
    std::cerr << "Cannot set register: " << address << std::endl;
    return;
  }
  reg[address] = value;
}

uint8_t split(uint16_t i) { return i & 0xff; }

void CPU::push(uint16_t lit) {
  uint16_t stackPointer = CPU::getRegister(sp);
  CPU::memory[stackPointer] = lit;
  CPU::setRegister(sp, stackPointer - 1);
  CPU::stackFrameSize += 1;
}

uint16_t CPU::pop() {
  uint16_t stackPointer = CPU::getRegister(sp) + 1;
  CPU::setRegister(sp, stackPointer);
  CPU::stackFrameSize -= 1;
  return CPU::memory[stackPointer];
}

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

uint8_t CPU::execute(uint8_t current) {
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
    break;
  }
  case JMP_EQ: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value != CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
    break;
  }
  case JMP_LESS_EQ: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value <= CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
    break;
  }
  case JMP_LESS: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value < CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
    break;
  }
  case JMP_GREATER_EQ: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value >= CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
    break;
  }
  case JMP_GREATER: {
    uint8_t value = fetch16();
    uint8_t pointer = fetch16();
    if (value > CPU::getRegister(acc)) {
      CPU::setRegister(ip, pointer);
    }
    break;
  }
  case PSH_LIT: {
    uint16_t val = fetch16();
    push(val);
    break;
  }
  case PSH_REG: {
    uint16_t registerIndex = fetch();
    uint16_t val = CPU::getRegister(registerIndex);
    push(val);
    break;
  }
  case POP: {
    uint16_t index = fetch16();
    uint16_t value = pop();
    CPU::setRegister(index, value);
    break;
  }
  case CAL_LIT: {
    uint16_t address = fetch16();

    CPU::pushState();
    CPU::setRegister(ip, address);
    break;
  }
  case CAL_REG: {
    uint8_t pointer = fetch16();
    uint16_t address = CPU::getRegister(pointer);
    CPU::pushState();
    CPU::setRegister(ip, address);
    break;
  }
  case RET: {
    CPU::popState();
    break;
  }
  case HLT: {
    return 1;
  }
  }
  return 0;
}

uint8_t CPU::step() {
  uint8_t instruction = CPU::fetch();
  return CPU::execute(instruction);
}

void CPU::run() {
  uint8_t halt = CPU::step();
  if (halt != 0) {
    CPU::run();
  }
}
