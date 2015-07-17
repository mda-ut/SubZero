/*	
Anthony De Caria - October 31, 2013

This module takes the SPI inputs CPOL as well as a Clk signal and a toggle signal S
and creates a SCLK signal.

Idling is triggered by S, if S = 1 then the signal is idle.
Where to idle is controlled by CPOL. If CPOL = 0, then the SCLK should idle in 0 and vice versa.

As such:
	If CPOL = 0, S = 0 and Clk = 0; SCLK = 0
	If CPOL = 0, S = 0 and Clk = 1; SCLK = 1
	If CPOL = 0, S = 1 and Clk = 0; SCLK = 0
	If CPOL = 0, S = 1 and Clk = 1; SCLK = 0
	If CPOL = 1, S = 0 and Clk = 0; SCLK = 0
	If CPOL = 1, S = 0 and Clk = 1; SCLK = 1
	If CPOL = 1, S = 1 and Clk = 0; SCLK = 1
	If CPOL = 1, S = 1 and Clk = 1; SCLK = 1
*/

module SCLKMaker(Clk, S, CPOL, SCLK);
	//Define the inputs and outputs
	input Clk;
	input S;
	input CPOL;
	
	output SCLK;
	
	//Create SCLK
	assign SCLK = (~S & Clk) | (CPOL & S);
	
endmodule
