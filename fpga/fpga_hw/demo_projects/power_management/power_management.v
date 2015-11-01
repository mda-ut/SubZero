// Turn power on and rotate through mux outputs at about 100kHz
module power_management(input CLOCK_50, output [6:0]LED, inout [33:0]GPIO_1);
  wire [2:0] voltage_mux;
  wire kill_sw;
  reg [11:0] counter = 12'd0;

  assign kill_sw = 1'd1;

  // kill switch
  assign GPIO_1[33] = kill_sw;

  // voltage muxes
  assign {GPIO_1[29], GPIO_1[31], GPIO_1[25]} = voltage_mux;
  assign voltage_mux = counter[11:9];

  // LEDs
  generate
  genvar i;
    for (i = 0; i < 7; i = i+1)
      begin : led_loop
        assign LED[i] = GPIO_1[27] && voltage_mux == i;
      end
  endgenerate

  always @(posedge CLOCK_50)
    counter = counter + 12'd1;
endmodule
