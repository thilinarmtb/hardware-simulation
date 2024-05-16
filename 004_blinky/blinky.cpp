#include <cstdio>
#include <cstdlib>

#include "verilated.h"

#include "Vblinky.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

static void tick(const std::unique_ptr<Vblinky> &pbky) {
  pbky->eval();
  pbky->i_clk = 1;
  pbky->eval();
  pbky->i_clk = 0;
  pbky->eval();
}

int main(int argc, char *argv[]) {
  const std::unique_ptr<VerilatedContext> pctx{new VerilatedContext{}};
  pctx->commandArgs(argc, argv);

  const std::unique_ptr<Vblinky> pbky{new Vblinky{pctx.get()}};

  int last_led = 1;
  for (int t = 0; t < (1 << 20); t++) {
    tick(pbky);
    if (last_led != pbky->o_led) printf("t = %7d, led = %d\n", t, pbky->o_led);
    last_led = pbky->o_led;
  }

  pbky->final();
  pctx->statsPrintSummary();

  return 0;
}
