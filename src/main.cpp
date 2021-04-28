#include "../include/cpu.h"
#include "../include/opcodes.h"
#include <iostream>

void log(CPU cpu) {
  for (int i = 0; i < 10; i++) {
    if (i == 0) {
      std::cout << "IP: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else if (i == 1) {
      std::cout << "ACC: " << unsigned(cpu.getRegister(i)) << std::endl;
    } else {
      std::cout << "R" << i - 1 << ": " << unsigned(cpu.getRegister(i))
                << std::endl;
    }
  }
}

int main() {
  CPU newCPU;
  newCPU.initMemory();
  int i = 0;
  newCPU.memory[i++] = MOV_LIT_REG;
  newCPU.memory[i++] = 0x0001;
  newCPU.memory[i++] = r1;

  newCPU.memory[i++] = MOV_MEM_REG;
  newCPU.memory[i++] = 0x00014;
  newCPU.memory[i++] = r2;

  newCPU.memory[i++] = ADD_REG_REG;
  newCPU.memory[i++] = r1;
  newCPU.memory[i++] = r2;

  newCPU.memory[i++] = MOV_REG_MEM;
  newCPU.memory[i++] = acc;
  newCPU.memory[i++] = 0x00014;

  newCPU.memory[i++] = JMP_NOT_EQ;
  newCPU.memory[i++] = 0x0003;
  newCPU.memory[i++] = 0x0000;

  int count = 1;
  while (true) {
    getchar();
    newCPU.step();
    if (newCPU.getRegister(ip) == 0) {
      std::cout << "\nJUMPED TO START: " << count << std::endl;
      count = 0;
    }

    log(newCPU);
    std::cout << "Memory at address 20: " << unsigned(newCPU.memory[20])
              << std::endl;
    count++;
    if (newCPU.getRegister(ip) == 12 && newCPU.memory[20] == 0x0003) {
      std::cout << "\nDONE: " << count << std::endl;
    }
  }
  return 0;
}
