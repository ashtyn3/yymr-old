#include "../include/cpu.h"
#include <iostream>

int main() {
  CPU newCPU;
  newCPU.initMemory();
  newCPU.memory[0] = 0x10;
  newCPU.memory[1] = 0x00;
  newCPU.memory[2] = 0x01; // 0x0001
  newCPU.memory[3] = 0x02;

  newCPU.step();
  // uint8_t num = newCPU.fetch();
  std::cout << unsigned(newCPU.getRegister(r1));
  return 0;
}
