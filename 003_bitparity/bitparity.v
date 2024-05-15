`default_nettype none

module bitparity(i_word, o_parity);
  input  wire[7:0] i_word;
  output wire      o_parity;

  assign o_parity = ^i_word;
endmodule
