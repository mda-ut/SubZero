// Global disable
//
// If any of the shutdown inputs goes high, all GPIO outputs will be set to 0

module global_disable #(
  parameter NUM_IN = 2,
  parameter NUM_IOS = 2
) (
  input clk,
  input [NUM_IN-1:0] shutdown,
  input [NUM_IOS-1:0] gpio_in,
  input [NUM_IOS-1:0] gpio_out_default,
  output reg [NUM_IOS-1:0] gpio_out
);

  always @(posedge clk)
    if (|shutdown)
      // Set all GPIO outputs to low
      gpio_out = gpio_out_default;
    else
      // Set all GPIO outputs to the input
      gpio_out = gpio_in;

endmodule
