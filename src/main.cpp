#include "../include/cpu.h"
#include "../include/mem.h"
#include "../include/opcodes.h"
#include <iostream>

int main() {
  MemoryMapper map;
  MemoryDriver mem(256 * 256);
  map.map(&mem, 0x0000, 0xffff, 0);

  CPU newCPU(map);
  newCPU.initReg();

  int i = 0;
  mem.memory[i++] = MOV_LIT_REG;
  mem.memory[i++] = 0x0001;
  mem.memory[i++] = r1;

  mem.memory[i++] = MOV_LIT_REG;
  mem.memory[i++] = 0x0014;
  mem.memory[i++] = r2;

  mem.memory[i++] = MOV_REG_REG;
  mem.memory[i++] = r2;
  mem.memory[i++] = r4;

  newCPU.step();
  newCPU.step();
  newCPU.step();

  std::cout << "ip: " << unsigned(newCPU.getRegister(ip)) << std::endl;
  std::cout << "register 1: " << unsigned(newCPU.getRegister(r1)) << std::endl;
  std::cout << "register 2: " << unsigned(newCPU.getRegister(r2)) << std::endl;
  std::cout << "register 3: " << unsigned(newCPU.getRegister(r3)) << std::endl;
  std::cout << "register 4: " << unsigned(newCPU.getRegister(r4)) << std::endl;
  return 0;
}
