#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vbitselect.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

int main(int argc, char *argv[]) {
  VerilatedContext *const context = new VerilatedContext{};
  context->commandArgs(argc, argv);

  Vbitselect *const bs = new Vbitselect{context};

  for (unsigned t = 0; t < 20; t++) {
    bs->i_sw = t & 0x1ff;
    bs->eval();
    printf("t = %02d, sw = %03x led = %03x\n", t, bs->i_sw, bs->o_led);
  }

  delete bs;
  delete context;

  return 0;
}
