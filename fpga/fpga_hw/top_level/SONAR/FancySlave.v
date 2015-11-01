/*
Anthony De Caria - May 17, 2014

This code describes a slave that represents the AD7264 Analog Digital Converter chip.
The AD7264 expects a 33 cycle SS period.
In the first 16 cycles, the AD7264 chip expects to recieve data.
In the 17th and 18th cycles, the AD7264 will be in the three-state.
From the 19th clock cycle to the 32nd, the AD7264 will transmit data.
The 33rd cycle will have the same data as the 32nd.
*/

module FancySlave (resetn, SCLK, MOSI, MISOA, MISOB, SS, Hex0, Hex1, Hex2, Hex3, Hex4, Hex5, Switches, Keys, Lights, Green);
	/*
		I/Os
	*/
	
	//	General I/Os	//
	input resetn;
	input [17:0] Switches;
	input [1:0] Keys;
	
	output [6:0] Hex0, Hex1, Hex2, Hex3, Hex4, Hex5;
	output [17:0] Lights;
	output [2:0] Green;
	
	//	SPI I/Os	//
	input SCLK;
	input MOSI;
	input SS;
	
	output MISOA;
	output MISOB;
	
	//	Additional Wires	//
	wire [5:0] slave_counter_bit;
	wire Des_en, Tri_en, Ser_en;
	wire [15:0]DOS;
	wire DIS, A, B;
	wire [13:0] SA, SB;
	
	//	Early wire assignments	//
	assign Des_en = ~SS & ~slave_counter_bit[5] & ~slave_counter_bit[4];
	assign Tri_en = ~SS & ~slave_counter_bit[5] & slave_counter_bit[4] & ~slave_counter_bit[3] & ~slave_counter_bit[2] & (slave_counter_bit[1] ^ slave_counter_bit[0]);
	assign Ser_en = ~SS & (~slave_counter_bit[5] & slave_counter_bit[4] & (slave_counter_bit[3] | slave_counter_bit[2] | slave_counter_bit[1] & slave_counter_bit[0] ) ) | (slave_counter_bit[5] & ~slave_counter_bit[4] & ~slave_counter_bit[3] & ~slave_counter_bit[2] & ~slave_counter_bit[1] & ~slave_counter_bit[0]);
	
	assign A = SA[13];
	assign B = SB[13];
	
	//	Debug Assignments //
//	assign Lights[16] = SCLK;
//	assign Lights[17] = SS;
	
//	assign Green[0] = Des_en;
//	assign Green[1] = Tri_en;
//	assign Green[2] = Ser_en;
	
//	assign Lights[15] = MISOA;
//	assign Lights[14] = MISOB;
	
	/*
	
	Counter
	
	*/	
	SixBitCounterAsync HootHoot(
											.clk(~SCLK),
											.resetn(resetn & ~SS),
											.enable(~SS & ~(slave_counter_bit[5] & ~slave_counter_bit[4] & ~slave_counter_bit[3] & ~slave_counter_bit[2] & ~slave_counter_bit[1] & slave_counter_bit[0]) ),
											.q(slave_counter_bit)
										);
				
	/*
	
	Deserializer
	
	*/	
	ShiftRegisterWEnableSixteen Registeel(
															.clk(~SCLK), 
															.resetn(resetn), 
															.enable(Des_en), 
															.d(DIS), 
															.q(DOS)
														);
								
	/*
	
	Serializer
	
	*/
	ShiftRegisterWEnableFourteenAsyncMuxedInput OutboxA(
																			.clk(~SCLK), 
																			.resetn(resetn), 
																			.enable(Ser_en | ~Keys[0]), 
																			.select(~Keys[0]), 
																			.d(Switches[13:0]), 
																			.q(SA) 
																		);
												
	ShiftRegisterWEnableFourteenAsyncMuxedInput OutboxB(
																			.clk(~SCLK), 
																			.resetn(resetn), 
																			.enable(Ser_en | ~Keys[1]), 
																			.select(~Keys[1]), 
																			.d(Switches[13:0]), 
																			.q(SB) 
																		);
												
	/*
	
	Tri-state
	
	*/
	TriStateBuffer BorderGuard1(
											.In(MOSI), 
											.Select(Des_en), 
											.Out(DIS)
										);
								
	TriStateBuffer BorderGuardA(
											.In(A), 
											.Select(Ser_en), 
											.Out(MISOA)
										);
								
	TriStateBuffer BorderGuardB(
											.In(B), 
											.Select(Ser_en), 
											.Out(MISOB)
										);
	
	/*
	
	HEXs
	
	*/
	SevenSegmentDisplayDecoder One(.ssOut(Hex0), .nIn(DOS[3:0]));
	SevenSegmentDisplayDecoder Two(.ssOut(Hex1), .nIn(DOS[7:4]));
	SevenSegmentDisplayDecoder Three(.ssOut(Hex2), .nIn(DOS[11:8]));
	SevenSegmentDisplayDecoder Four(.ssOut(Hex3), .nIn(DOS[15:12]));
	
	SevenSegmentDisplayDecoder CounterHigher(.ssOut(Hex5), .nIn(slave_counter_bit[5:4]));
	SevenSegmentDisplayDecoder CounterLower(.ssOut(Hex4), .nIn(slave_counter_bit[3:0]));
	
	/*
	
	Mux
	
	*/
	mux2to1_14bit FancySwitch(
											.data0(SA),
											.data1(SB),
											.sel(Switches[14]),
											.result(Lights)
										);
	
endmodule
