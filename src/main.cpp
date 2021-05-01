#include "../include/cpu.h"
#include "../include/opcodes.h"
#include <iostream>

void log(CPU cpu) {
  for (int i = 0; i < 12; i++) {
    if (i == 0) {
      std::cout << "IP: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else if (i == 1) {
      std::cout << "ACC: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else if (i == 10) {
      std::cout << "SP: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else if (i == 11) {
      std::cout << "FP: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else {
      std::cout << "R" << i - 1 << ": " << unsigned(cpu.getRegister(i))
                << std::endl;
    }
  }
}

void memoryAt(CPU cpu, int addr) {
  std::cout << "0x" << std::hex << addr << ": " << std::dec;
  for (int i = addr; i < addr + 4; i++) {
    std::cout << "0x" << std::hex << unsigned(cpu.memory[i]) << " ";
  }
  std::cout << std::endl;
}

int main() {
  CPU newCPU(256 * 256);
  newCPU.initMemory();
  int i = 0;

  newCPU.memory[i++] = MOV_LIT_REG;
  newCPU.memory[i++] = 0x0001;
  newCPU.memory[i++] = r1;

  newCPU.memory[i++] = MOV_LIT_REG;
  newCPU.memory[i++] = 0x0002;
  newCPU.memory[i++] = r2;

  newCPU.memory[i++] = PSH_REG;
  newCPU.memory[i++] = r1;

  newCPU.memory[i++] = PSH_REG;
  newCPU.memory[i++] = r2;

  newCPU.memory[i++] = POP;
  newCPU.memory[i++] = r1;

  newCPU.memory[i++] = POP;
  newCPU.memory[i++] = r2;

  int count = 1;
  while (true) {
    getchar();
    newCPU.step();
    log(newCPU);
    memoryAt(newCPU, newCPU.memory[newCPU.getRegister(sp)]);
    memoryAt(newCPU, newCPU.getRegister(ip));
  }

  return 0;
}

int old() {
  CPU newCPU(256 * 256);
  newCPU.initMemory();
  int i = 0;
  newCPU.memory[i++] = PSH_LIT;
  newCPU.memory[i++] = 0x14;
  newCPU.step();
  log(newCPU);
  std::cout << "\t" << unsigned(newCPU.memory[0x100]) << std::endl;
}
