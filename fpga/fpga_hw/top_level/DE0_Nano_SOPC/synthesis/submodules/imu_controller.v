// This is the Avalon slave for the IMU
//
// Registers 0-7 store ADC outputs

module imu_controller(
  input chipselect, 
  input [3:0]addr, 
  input read, 
  output reg [31:0] readdata, 
  input spi_clk, 
  input spi_reset,
  input sys_clk, 
  input ADC_SDAT, 
  output ADC_CS_N, 
  output ADC_SADDR, 
  output ADC_SCLK
);

  wire [8*32-1:0] adc_channels;

  imu imu(
    .reset_n(1'b1),
    .spi_clk(spi_clk),
    .sys_clk(sys_clk),
    .sda(),
    .scl(),
    .adc_channels(adc_channels),
    .ADC_SDAT(ADC_SDAT),
    .ADC_CS_N(ADC_CS_N),
    .ADC_SADDR(ADC_SADDR),
    .ADC_SCLK(ADC_SCLK)
);

  always @(posedge sys_clk)
    if (chipselect & read)
    casex (addr)
      4'b0000:
        readdata <= adc_channels[1*32-1:0*32];
      4'b0001:
        readdata <= adc_channels[2*32-1:1*32];
      4'b0010:
        readdata <= adc_channels[3*32-1:2*32];
      4'b0011:
        readdata <= adc_channels[4*32-1:3*32];
      4'b0100:
        readdata <= adc_channels[5*32-1:4*32];
      4'b0101:
        readdata <= adc_channels[6*32-1:5*32];
      4'b0110:
        readdata <= adc_channels[7*32-1:6*32];
      4'b0111:
        readdata <= adc_channels[8*32-1:7*32];
      default:
        readdata <= 32'd0;
    endcase
endmodule

