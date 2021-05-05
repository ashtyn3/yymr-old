#ifndef cpu
#define cpu
#include "../include/mapper.h"
#include <vector>

enum registers {
  ip = 0,
  acc = 1,
  r1 = 2,
  r2 = 3,
  r3 = 4,
  r4 = 5,
  r5 = 6,
  r6 = 7,
  r7 = 8,
  r8 = 9,
  sp = 10,
  fp = 11,
};

class CPU {
public:
  CPU(MemoryMapper *ram) : memory(ram) {}
  int memoryLimit;
  uint8_t stackFrameSize;
  uint16_t reg[12];
  MemoryMapper *memory;
  void initReg();
  void pushState();
  void popState();
  void push(uint16_t lit);
  uint16_t pop();
  uint16_t getRegister(int address);
  void setRegister(int address, uint16_t value);
  uint8_t fetch();
  uint16_t fetch16();
  uint8_t execute(uint8_t current);
  uint8_t step();
  void run();
};

#endif
