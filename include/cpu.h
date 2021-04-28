#ifndef HEADER_FILE_NAME
#define HEADER_FILE_NAME
#include <stdint.h>
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
  r8 = 9
};

class CPU {
public:
  uint16_t reg[10];
  std::vector<uint8_t> memory;
  uint8_t readMemory(int address);
  void initMemory(int size = 20);
  uint16_t getRegister(int address);
  void setRegister(int address, uint16_t value);
  uint8_t fetch();
  uint16_t fetch16();
  void execute(uint8_t current);
  void step();
};

#endif
