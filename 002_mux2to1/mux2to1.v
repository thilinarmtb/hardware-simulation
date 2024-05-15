`default_nettype none

module mux2to1(i_a, i_b, i_sel, o_out);
  input  wire i_a, i_b, i_sel;
  output wire o_out;

  assign o_out = (i_sel) ? i_a : i_b;
endmodule
