`default_nettype none

`include "parameters.vh"

module ledwalker#(WIDTH=`DEFAULT_WIDTH)(i_clk, o_led);
  input  wire                i_clk;
  output reg[(WIDTH - 1): 0] o_led;

  reg[3:0] led_index;

  initial o_led     = 8'h01;
  initial led_index = 4'h0;

  always @(posedge i_clk)
  begin
    if (led_index >= 4'hd) begin
      led_index <= 0;
    end else begin
      led_index <= led_index + 1'b1;
    end
  end

  always @(posedge i_clk)
  begin
    case(led_index)
      4'h0: o_led <= 8'h01;
      4'h1: o_led <= 8'h02;
      4'h2: o_led <= 8'h04;
      4'h3: o_led <= 8'h08;
      4'h4: o_led <= 8'h10;
      4'h5: o_led <= 8'h20;
      4'h6: o_led <= 8'h40;
      4'h7: o_led <= 8'h80;
      4'h8: o_led <= 8'h40;
      4'h9: o_led <= 8'h20;
      4'ha: o_led <= 8'h10;
      4'hb: o_led <= 8'h08;
      4'hc: o_led <= 8'h04;
      4'hd: o_led <= 8'h02;
      default: o_led <= 8'h01;
    endcase
  end
endmodule
