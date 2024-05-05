#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vthruwire.h"

int main(int argc, char *argv[]) {
  VerilatedContext *const context = new VerilatedContext{};
  context->commandArgs(argc, argv);

  Vthruwire *const tw = new Vthruwire{context};

  for (unsigned t = 0; t < 20; t++) {
    tw->i_sw = t & 1;
    tw->eval();
    printf("t = %02d, sw = %02d led = %02d\n", t, tw->i_sw, tw->o_led);
  }

  return 0;
}
