// This is the motor_controller for each H-bridge circuit
// Direction and on/off can be specified, as well as duty cycle

`include "defines.v"

module motor_controller (input clk, input dir, input on, input [15:0] period, input [15:0] duty_cycle, output [3:0] out);

  reg [`PERIOD_LENGTH-1:0] duty_counter = 0;
  reg dir_reg;

  always @(posedge clk)
  begin
    if (duty_counter == period)
      duty_counter <= 0;
    else
      duty_counter <= duty_counter + 1;
    dir_reg <= (on && duty_counter < duty_cycle) ? ~dir : dir;
  end

  motor_internal mi(clk, dir_reg, on, out);

endmodule

module motor_internal (input clk, input dir, input on, output reg [3:0] out);

  reg [3:0] out_reg;
  reg [9:0] dead_time_counter = `DEAD_TIME;
  reg [1:0] prev_in = 2'b00;

  always @(posedge clk)
  begin
    if ({dir, on} != prev_in)
      dead_time_counter <= 10'd0;
    if (dead_time_counter != `DEAD_TIME)
      dead_time_counter <= dead_time_counter + 10'd1;
    casex ({dir, on})
      2'b00: out_reg <= 4'b0000;
      2'b10: out_reg <= 4'b1010;
      2'b11: out_reg <= 4'b1001;
      2'b01: out_reg <= 4'b0110;
    endcase
    prev_in <= {dir, on};
    out <= (dead_time_counter != `DEAD_TIME) ? 4'd0 : out_reg;
  end

endmodule
