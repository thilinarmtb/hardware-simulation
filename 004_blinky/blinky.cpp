#include <cstdio>
#include <cstdlib>

#include "verilated.h"
#include "verilated_vcd_c.h"

#include "Vblinky.h"

// Example found in the tutorial: https://zipcpu.com/tutorial/lsn-01-wires.pdf

static void tick(const unsigned tick_count, const std::unique_ptr<Vblinky> &bky,
                 const std::unique_ptr<VerilatedVcdC> &tfp) {
  bky->eval();
  tfp->dump(tick_count * 10 - 2);
  bky->i_clk = 1;
  bky->eval();
  tfp->dump(tick_count * 10);
  bky->i_clk = 0;
  bky->eval();
  tfp->dump(tick_count * 10 + 5);
}

int main(int argc, char *argv[]) {
  const std::unique_ptr<VerilatedContext> ctx{new VerilatedContext{}};
  ctx->commandArgs(argc, argv);

  const std::unique_ptr<Vblinky> bky{new Vblinky{ctx.get()}};
  ctx->traceEverOn(true);

  const std::unique_ptr<VerilatedVcdC> tfp{new VerilatedVcdC};
  bky->trace(tfp.get(), 00);
  tfp->open("blinkytrace.vcd");

  int last_led = bky->o_led;
  unsigned tick_count = 0;
  for (int t = 0; t < (1 << 20); t++) {
    tick_count++;
    tick(tick_count, bky, tfp);
    if (last_led != bky->o_led) printf("t = %7d, led = %d\n", t, bky->o_led);
    last_led = bky->o_led;
  }

  bky->final();
  ctx->statsPrintSummary();

  return 0;
}
