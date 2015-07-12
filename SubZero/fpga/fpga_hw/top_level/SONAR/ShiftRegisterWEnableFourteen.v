/*
Anthony De Caria - March 17, 2014

This module creates a Shift Register with a seperate enable signal.
This specific module creates an output that is 14-bits wide.
*/

module ShiftRegisterWEnableFourteen(clk, resetn, enable, d, q);
	
	//Define the inputs and outputs
	input clk;
	input resetn;
	input enable;
	input d;
	output [13:0] q;
	
	D_FF_with_Enable Zero(clk, resetn, enable, d, q[0]);
	D_FF_with_Enable One(clk, resetn, enable, q[0], q[1]);
	D_FF_with_Enable Two(clk, resetn, enable, q[1], q[2]);
	D_FF_with_Enable Three(clk, resetn, enable, q[2], q[3]);
	D_FF_with_Enable Four(clk, resetn, enable, q[3], q[4]);
	D_FF_with_Enable Five(clk, resetn, enable, q[4], q[5]);
	D_FF_with_Enable Six(clk, resetn, enable, q[5], q[6]);
	D_FF_with_Enable Seven(clk, resetn, enable, q[6], q[7]);
	D_FF_with_Enable Eight(clk, resetn, enable, q[7], q[8]);
	D_FF_with_Enable Nine(clk, resetn, enable, q[8], q[9]);
	D_FF_with_Enable Ten(clk, resetn, enable, q[9], q[10]);
	D_FF_with_Enable Eleven(clk, resetn, enable, q[10], q[11]);
	D_FF_with_Enable Twelve(clk, resetn, enable, q[11], q[12]);
	D_FF_with_Enable Thirteen(clk, resetn, enable, q[12], q[13]);

endmodule
