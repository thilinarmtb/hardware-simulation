#include <cstdio>
#include <cstdlib>

#include "verilated.h"
#include "verilated_vcd_c.h"

#include "Vstrobe.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

static void tick(const unsigned tick_count,
                 const std::unique_ptr<Vstrobe> &strb,
                 const std::unique_ptr<VerilatedVcdC> &tfp) {
  strb->eval();
  tfp->dump(tick_count * 10 - 2);
  strb->i_clk = 1;
  strb->eval();
  tfp->dump(tick_count * 10);
  strb->i_clk = 0;
  strb->eval();
  tfp->dump(tick_count * 10 + 5);
}

int main(int argc, char *argv[]) {
  const std::unique_ptr<VerilatedContext> ctx{new VerilatedContext{}};
  ctx->commandArgs(argc, argv);

  const std::unique_ptr<Vstrobe> strb{new Vstrobe{ctx.get()}};
  ctx->traceEverOn(true);

  const std::unique_ptr<VerilatedVcdC> tfp{new VerilatedVcdC};
  strb->trace(tfp.get(), 00);
  tfp->open("strobetrace.vcd");

  int last_led = strb->o_led;
  unsigned tick_count = 0;
  for (int t = 0; t < (1 << 20); t++) {
    tick_count++;
    tick(tick_count, strb, tfp);
    if (last_led != strb->o_led) printf("t = %7d, led = %d\n", t, strb->o_led);
    last_led = strb->o_led;
  }

  strb->final();
  ctx->statsPrintSummary();

  return 0;
}
