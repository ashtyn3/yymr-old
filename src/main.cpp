#include "../include/cpu.h"
#include <iostream>

int main() {
  CPU newCPU;
  newCPU.initMemory();
  std::cout << newCPU.reg[9];
  std::cout << newCPU.readMemory(0x0) << std::endl;
  return 0;
}
