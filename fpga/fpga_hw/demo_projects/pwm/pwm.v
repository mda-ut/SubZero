`define FREQ_IN_KHZ 18
`define DUTY_CYCLE 85/100

`define PERIOD (50000 / `FREQ_IN_KHZ)
`define DUTY_PERIOD (`PERIOD*`DUTY_CYCLE)

module pwm(input CLOCK_50, input [0:0]SW, output [7:0]LED, output [7:0]GPIO_1);

  motor_controller mc0(CLOCK_50, 1'b1, SW[0], `PERIOD, `DUTY_PERIOD, LED[3:0]);
  motor_controller mc1(CLOCK_50, 1'b0, SW[0], `PERIOD, `DUTY_PERIOD, LED[7:4]);
  motor_controller mc2(CLOCK_50, 1'b1, SW[0], `PERIOD, `DUTY_PERIOD, {GPIO_1[7], GPIO_1[5], GPIO_1[3], GPIO_1[1]});
endmodule
