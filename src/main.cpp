#include "../include/cpu.h"
#include <iostream>

int main() {
  CPU newCPU;
  newCPU.initMemory();
  newCPU.setRegister(ip, 0x0000);
  newCPU.memory[0] = 0x0a;
  uint8_t num = newCPU.fetch();
  std::cout << "Number: " << unsigned(num) << "\n";
  std::cout << newCPU.getRegister(ip) << std::endl;
  return 0;
}
