#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vbitparity.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

int main(int argc, char *argv[]) {
  VerilatedContext *const context = new VerilatedContext{};
  context->commandArgs(argc, argv);

  Vbitparity *const bp = new Vbitparity{context};

  for (unsigned t = 0; t < 32; t++) {
    bp->i_word = t;
    bp->eval();
    printf("t = %02d, i_word = %02d, o_bitparity = %d\n", t, bp->i_word,
           bp->o_parity);
  }

  delete context;

  return 0;
}
