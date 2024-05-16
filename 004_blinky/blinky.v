`default_nettype none

`include "parameters.vh"

module blinky#(parameter WIDTH=`DEFAULT_WIDTH)(i_clk, o_led);
  input  wire i_clk;
  output wire o_led;

  reg     [WIDTH - 1:0] counter;
  initial counter = 0;

  always @(posedge i_clk)
  begin
    counter <= counter + 1'b1;
  end

  assign o_led = counter[WIDTH - 1];
endmodule
