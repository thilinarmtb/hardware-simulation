#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vbitselect.h"

int main(int argc, char *argv[]) {
  VerilatedContext *const context = new VerilatedContext{};
  context->commandArgs(argc, argv);

  Vbitselect *const bs = new Vbitselect{context};

  for (unsigned t = 0; t < 20; t++) {
    bs->i_sw = t & 0x1ff;
    bs->eval();
    printf("t = %02d, sw = %03x led = %03x\n", t, bs->i_sw, bs->o_led);
  }

  delete context;

  return 0;
}
