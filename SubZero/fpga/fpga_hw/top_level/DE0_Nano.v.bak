// --------------------------------------------------------------------
// Copyright (c) 2011 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/   
//                     email: support@terasic.com
//
// --------------------------------------------------------------------



module DE0_Nano(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SW //////////
	SW,

	//////////// SDRAM //////////
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_DQM,
	DRAM_RAS_N,
	DRAM_WE_N,
	
	//////////// ECPS //////////
	EPCS_ASDO,
	EPCS_DATA0,
	EPCS_DCLK,
	EPCS_NCSO,

	//////////// Accelerometer and EEPROM //////////
	G_SENSOR_CS_N,
	G_SENSOR_INT,
	I2C_SCLK,
	I2C_SDAT,

	//////////// ADC //////////
	ADC_CS_N,
	ADC_SADDR,
	ADC_SCLK,
	ADC_SDAT,

	//////////// 2x13 GPIO Header //////////
	GPIO_2,
	GPIO_2_IN,

	//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	GPIO_0,
	GPIO_0_IN,

	//////////// GPIO_1, GPIO_1 connect to GPIO Default //////////
	GPIO_1,
	GPIO_1_IN 
);

//=======================================================
//  PARAMETER declarations
//=======================================================


//=======================================================
//  PORT declarations
//=======================================================

//////////// CLOCK //////////
input 		          		CLOCK_50;

//////////// LED //////////
output		     [7:0]		LED;

//////////// KEY //////////
input 		     [1:0]		KEY;

//////////// SW //////////
input 		     [3:0]		SW;

//////////// SDRAM //////////
output		    [12:0]		DRAM_ADDR;
output		     [1:0]		DRAM_BA;
output		          		DRAM_CAS_N;
output		          		DRAM_CKE;
output		          		DRAM_CLK;
output		          		DRAM_CS_N;
inout 		    [15:0]		DRAM_DQ;
output		     [1:0]		DRAM_DQM;
output		          		DRAM_RAS_N;
output		          		DRAM_WE_N;

//////////// EPCS //////////
output		          		EPCS_ASDO;
input 		          		EPCS_DATA0;
output		          		EPCS_DCLK;
output		          		EPCS_NCSO;

//////////// Accelerometer and EEPROM //////////
output		          		G_SENSOR_CS_N;
input 		          		G_SENSOR_INT;
output							I2C_SCLK;
inout 		          		I2C_SDAT;

//////////// ADC //////////
output		          		ADC_CS_N;
output		          		ADC_SADDR;
output		          		ADC_SCLK;
input 		          		ADC_SDAT;

//////////// 2x13 GPIO Header //////////
inout 		    [12:0]		GPIO_2;
input 		     [2:0]		GPIO_2_IN;

//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
inout 		    [33:0]		GPIO_0;
input 		     [1:0]		GPIO_0_IN;

//////////// GPIO_1, GPIO_1 connect to GPIO Default //////////
inout 		    [33:0]		GPIO_1;
input 		     [1:0]		GPIO_1_IN;


//=======================================================
//  REG/WIRE declarations
//=======================================================
wire reset_n;
wire select_i2c_clk;
wire i2c_clk;
wire spi_clk;

wire [32:0] gpio_0_wire;
wire [33:0] gpio_1_wire;
wire [12:0] gpio_2_wire;
wire [3:0]  led_wire;

wire error, power;
wire [2:0] voltage_mux;

//=======================================================
//  Structural coding
//=======================================================

assign reset_n = 1'b1;
assign GPIO_1[33] = power;
assign {GPIO_1[29], GPIO_1[31], GPIO_1[25]} = voltage_mux;
assign LED[3:0] = {2'b10, GPIO_0[33], gpio_2_wire[5]};

global_disable #(
  .NUM_IN(2+1),
  .NUM_IOS(34+13+4)
) dis_inst (
  .clk(CLOCK_50),
  .shutdown(~{KEY, power}),
  .gpio_in({gpio_0_wire, gpio_2_wire, led_wire}),
  .gpio_out_default({{33{1'b0}}, {7{1'b0}}, {1'b1}, {5{1'b0}}, {4{1'b0}}}), // GPIO_2[5] defaults to 1
  .gpio_out({GPIO_0[32:0], GPIO_2, LED[7:4]})
);

// assign IMU reset to low
assign gpio_2_wire[9] = 1'b0;

DE0_Nano_SOPC DE0_Nano_SOPC_inst(
                      // global signals:
                       .altpll_io(),
                       .altpll_sdram(DRAM_CLK),
                       .altpll_sys(),
                       .clk_50(CLOCK_50),
                       .reset_n(reset_n),

			
                      // GPIO pins to Avalon slave(s)
                       .GPIO_out_from_the_motor_controller_0({led_wire[3:0], gpio_2_wire[6], gpio_2_wire[8], gpio_0_wire[24], gpio_0_wire[25], gpio_0_wire[18], gpio_0_wire[19], gpio_0_wire[12], gpio_0_wire[13], gpio_0_wire[16], gpio_0_wire[17], gpio_0_wire[10], gpio_0_wire[11], gpio_2_wire[2], gpio_2_wire[4], gpio_0_wire[22], gpio_0_wire[23], gpio_0_wire[4], gpio_0_wire[5], gpio_0_wire[2], gpio_0_wire[0]}),

                      // Clocks for the IMU
                      .sys_clk_to_the_imu_controller_0(CLOCK_50),
                      .ADC_CS_N_from_the_imu_controller_0(ADC_CS_N),
                      .ADC_SADDR_from_the_imu_controller_0(ADC_SADDR),
                      .ADC_SCLK_from_the_imu_controller_0(ADC_SCLK),
                      .ADC_SDAT_to_the_imu_controller_0(ADC_SDAT),

                      // RS232 Signals (add signals later)
                      .UART_RXD_to_the_RS232_0(!power | GPIO_0[33]), // 1 if power is off
                      .UART_TXD_from_the_RS232_0(gpio_2_wire[5]),

                      // Power Management
                      .data_to_the_power_management_slave_0(GPIO_1[27]),
                      .mux_from_the_power_management_slave_0(voltage_mux),
                      .kill_sw_from_the_power_management_slave_0(power),

                      // the_select_i2c_clk
                       .out_port_from_the_select_i2c_clk(select_i2c_clk),

                      // the_altpll_0
                       .locked_from_the_altpll_0(),
                       .phasedone_from_the_altpll_0(),

                      // the_epcs
                       .data0_to_the_epcs(EPCS_DATA0), 
                       .dclk_from_the_epcs(EPCS_DCLK), 
                       .sce_from_the_epcs(EPCS_NCSO), 
                       .sdo_from_the_epcs(EPCS_ASDO), 


                      // the_gsensor_spi
                       .SPI_CS_n_from_the_gsensor_spi(G_SENSOR_CS_N),
                       .SPI_SCLK_from_the_gsensor_spi(spi_clk),
                       .SPI_SDIO_to_and_from_the_gsensor_spi(I2C_SDAT),	


                      // the_g_sensor_int
                       .in_port_to_the_g_sensor_int(G_SENSOR_INT),

                      // the_i2c_scl
                       .out_port_from_the_i2c_scl(i2c_clk),

                      // the_i2c_sda
                       .bidir_port_to_and_from_the_i2c_sda(I2C_SDAT),

                      // the_key
                       .in_port_to_the_key(KEY),

                      // the_sdram
                       .zs_addr_from_the_sdram(DRAM_ADDR),
                       .zs_ba_from_the_sdram(DRAM_BA),
                       .zs_cas_n_from_the_sdram(DRAM_CAS_N),
                       .zs_cke_from_the_sdram(DRAM_CKE),
                       .zs_cs_n_from_the_sdram(DRAM_CS_N),
                       .zs_dq_to_and_from_the_sdram(DRAM_DQ),
                       .zs_dqm_from_the_sdram(DRAM_DQM),
                       .zs_ras_n_from_the_sdram(DRAM_RAS_N),
                       .zs_we_n_from_the_sdram(DRAM_WE_N),

                      // the_sw
                       .in_port_to_the_sw(SW)
                    );

						  
assign I2C_SCLK = (select_i2c_clk)?i2c_clk:spi_clk;

endmodule

