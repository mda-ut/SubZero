/*
Anthony De Caria - June 15, 2014

This module is the structure that interfaces NIOS-II with two AD7264 A-D-Cs.
This is done using SPI protocol.

It takes key signals from NIOS (CPOL, CPHA, ss), and transforms them into SCLK and SS signals.

In addition, it also creates the structures needed to collect and transmit data to and from the AD7264s
A 16-bit serializer for transmitting.
And two 14-bit deserializers for recieveing (the AD7264 is dual channel).
*/

module ADCConnector (SPIClock, resetn, 
								CPOL, CPHA, ss,
									SCLK, SS, MOSI1, MISO1A, MISO1B, MOSI2, MISO2A, MISO2B, 
										DOM1, DIM1A, DIM1B, DOM2, DIM2A, DIM2B,
											DOL1, DOL2, ready, loaded1, loaded2);
	
	/*
	
	I/Os
	
	*/
	
	//	General I/Os	//
	input SPIClock;
	input resetn;
	
	//	CPU I/Os	//
	input CPOL;
	input CPHA;
	input ss;
	
	input DOL1;
	input DOL2;
	
	output ready;
	output loaded1;
	output loaded2;
	
	//	Data I/Os	//
	//	Note: DOM lines are the lines that have data to be sent out.	//
	//			While DIM lines are the lines that have data for NIOS.	//
	input [15:0]DOM1;
	output [13:0]DIM1A;
	output [13:0]DIM1B;
	
	input [15:0]DOM2;
	output [13:0]DIM2A;
	output [13:0]DIM2B;
	
	//	SPI I/Os	//
	output SCLK;
	output SS;
	
	output MOSI1;
	input MISO1A;
	input MISO1B;
	
	output MOSI2;
	input MISO2A;
	input MISO2B;
	
	//	Intra-Connector wires	//
	wire [5:0] master_counter_bit;
	wire Des_en, Ser_en;
	wire A1, B1, A2, B2, O1, O2;
	wire [15:0] o1, o2;
	wire RS;
	
	//	Early assignments	//
	assign SS = ss;
	
	assign Ser_en = ~master_counter_bit[5] & ~master_counter_bit[4];
	assign Des_en = (~master_counter_bit[5] & master_counter_bit[4] & (master_counter_bit[3] | master_counter_bit[2] | master_counter_bit[1] & master_counter_bit[0]) ) | (master_counter_bit[5] & ~master_counter_bit[4] & ~master_counter_bit[3] & ~master_counter_bit[2] & ~master_counter_bit[1] & ~master_counter_bit[0]);
	
	assign ready = master_counter_bit[5];
	assign loaded1 = (o1 == DOM1)? 1'b1: 1'b0;
//	assign loaded2 = (o2 == DOM2)? 1'b1: 1'b0;
	assign loaded2 = 1'b1;
	
	assign O1 = o1[15];
	assign O2 = o2[15];
	
	/*
	
	Counter
	This is the counter that will be used to pace out the sending out and receiving parts of the 
	
	*/	
	SixBitCounterAsync PocketWatch(
											.clk(SPIClock), 
											.resetn(resetn & ~SS), 
											.enable(~SS & ~(master_counter_bit[5] & ~master_counter_bit[4] & ~master_counter_bit[3] & ~master_counter_bit[2] & ~master_counter_bit[1] & master_counter_bit[0]) ),
											.q(master_counter_bit)
										);
										
	/*
	
	Signal Makers
	
	*/
	SCLKMaker TimeLord(
								.Clk(SPIClock), 
								.S(ss), 
								.CPOL(CPOL), 
								.SCLK(SCLK)
							);
	
	SPIRSMaker Level(
							.CPHA(CPHA), 
							.CPOL(CPOL), 
							.RS(RS)
							);
										
	/*
	
	Serializers
	
	*/
	ShiftRegisterWEnableSixteenAsyncMuxedInput OutBox1(
																			.clk(~(SPIClock ^ RS)), 
																			.resetn(resetn), 
																			.enable(Ser_en), 
																			.select(DOL1), 
																			.d(DOM1), 
																			.q(o1)
																		);
	
	/*
	
	Deserializers
	
	*/
	ShiftRegisterWEnableFourteen InBox1A(
														.clk(~(SPIClock ^ RS)), 
														.resetn(resetn), 
														.enable(Des_en), 
														.d(A1), 
														.q(DIM1A)
													);
													
	ShiftRegisterWEnableFourteen InBox1B(
														.clk(~(SPIClock ^ RS)), 
														.resetn(resetn), 
														.enable(Des_en), 
														.d(B1), 
														.q(DIM1B)
													);
	
	/*
	
	Tri-state buffers
	
	*/
	TriStateBuffer BorderGuardOut1(
												.In(O1), 
												.Select(Ser_en), 
												.Out(MOSI1)
											);
											
	TriStateBuffer BorderGuardIn1A(
												.In(MISO1A), 
												.Select(Des_en), 
												.Out(A1)
											);
											
	TriStateBuffer BorderGuardIn1B(
												.In(MISO1B), 
												.Select(Des_en), 
												.Out(B1)
											);

endmodule
