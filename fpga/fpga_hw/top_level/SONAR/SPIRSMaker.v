/*
Anthony De Caria - October 31, 2013

This module takes the SPI signals CPHA and CPOL
and producces a signal RS 
that will control on what edge of the clock the SPI registers run.

If RS is 1; the register should toggle on the posedge
If RS is 0; the register should toggle on the negedge

As such:
	If CPHA = 0 and CPOL = 0; RS = 0
	If CPHA = 0 and CPOL = 1; RS = 1
	If CPHA = 1 and CPOL = 0; RS = 1
	If CPHA = 1 and CPOL = 1; RS = 0
	
Reference: http://www.byteparadigm.com/applications/introduction-to-i2c-and-spi-protocols/?/article/AA-00255/22/Introduction-to-SPI-and-IC-protocols.html

*/
module SPIRSMaker (CPHA, CPOL, RS);
	//Define the Inputs and Outputs
	input CPHA;
	input CPOL;
	output RS;
	
	assign RS = CPHA ^ CPOL;
	
endmodule 
