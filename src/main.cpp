#include "../include/cpu.h"
#include "../include/mem.h"
#include "../include/opcodes.h"
#include "../include/screen.h"
#include <iostream>

int main() {
  MemoryMapper map;
  ScreenDriver screenDevice;
  MemoryDriver mem(256 * 256);
  map.map(&mem.control, 0x0000, 0xffff, 0);
  map.map(&screenDevice, 0x3000, 0x30ff, 1);

  // CPU newCPU(map);
  // newCPU.initReg();

  // int i = 0;

  // int count = 1;
  // while (true) {
  //  getchar();
  // newCPU.step();
  //}

  return 0;
}
