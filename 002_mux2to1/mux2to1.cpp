#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vmux2to1.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

int main(int argc, char *argv[]) {
  VerilatedContext *const context = new VerilatedContext{};
  context->commandArgs(argc, argv);

  Vmux2to1 *const m2to1 = new Vmux2to1{context};

  for (unsigned t = 0; t < 20; t++) {
    m2to1->i_a = 1, m2to1->i_b = 0, m2to1->i_sel = t & 1;
    m2to1->eval();
    printf("t = %02d, i_a = %d, i_b = %d, i_sel = %d, o_out = %d\n", t,
           m2to1->i_a, m2to1->i_b, m2to1->i_sel, m2to1->o_out);
  }

  delete context;

  return 0;
}
