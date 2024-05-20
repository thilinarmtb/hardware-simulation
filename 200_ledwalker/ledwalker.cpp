#include <cstdio>
#include <cstdlib>

#include "verilated.h"
#include "verilated_vcd_c.h"

#include "Vledwalker.h"

template <class T> using uptr_t = std::unique_ptr<T>;

static void tick(unsigned &tick_count, const uptr_t<Vledwalker> &lw,
                 const uptr_t<VerilatedVcdC> &vcd) {
  tick_count++;

  lw->eval();
  vcd->dump(tick_count * 10 - 2);

  lw->i_clk = 1;
  lw->eval();
  vcd->dump(tick_count * 10);

  lw->i_clk = 0;
  lw->eval();
  vcd->dump(tick_count * 10 + 5);
}

int main(int argc, char *argv[]) {
  const uptr_t<VerilatedContext> ctx{new VerilatedContext{}};
  ctx->commandArgs(argc, argv);

  const uptr_t<Vledwalker> lw{new Vledwalker{ctx.get()}};
  ctx->traceEverOn(true);

  const uptr_t<VerilatedVcdC> vcd{new VerilatedVcdC{}};
  lw->trace(vcd.get(), 00);
  vcd->open("ledwalkertrace.vcd");

  int last_led = lw->o_led;
  unsigned tick_count = 0;
  for (int t = 0; t < (1 << 20); t++) {
    tick(tick_count, lw, vcd);

    if (lw->o_led == last_led) continue;

    last_led = lw->o_led;
    fprintf(stderr, "t = %7d, led = %d\n", t, last_led);
    fflush(stderr);
  }

  lw->final();
  ctx->statsPrintSummary();

  return 0;
}
