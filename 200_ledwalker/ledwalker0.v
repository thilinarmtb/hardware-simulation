`default_nettype none

`include "parameters.vh"

module ledwalker#(WIDTH=`DEFAULT_WIDTH)(i_clk, o_led);
  input  wire               i_clk;
  output reg[(WIDTH -1): 0] o_led;

  initial o_led = 8'h1;
  always @(posedge i_clk)
  begin
    o_led <= {o_led[(WIDTH - 2): 0], o_led[WIDTH - 1]};
  end
endmodule
