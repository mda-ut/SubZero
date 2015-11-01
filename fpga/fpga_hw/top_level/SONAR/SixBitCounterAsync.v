/*
Anthony De Caria - May 17, 2014

This is a Six Bit Asyncronous Counter.
*/

module SixBitCounterAsync(clk, resetn, enable, q);
	
	input clk;
	input resetn;
	input enable;
	output [5:0]q;
	
	T_FF_with_Enable_Async Five(clk, resetn, enable, q[0] & q[1] & q[2] & q[3] & q[4], q[5]);
	T_FF_with_Enable_Async Four(clk, resetn, enable, q[0] & q[1] & q[2] & q[3], q[4]);
	T_FF_with_Enable_Async Three(clk, resetn, enable, q[0] & q[1] & q[2], q[3]);
	T_FF_with_Enable_Async Two(clk, resetn, enable, q[0] & q[1], q[2]);
	T_FF_with_Enable_Async One(clk, resetn, enable, q[0], q[1]);
	T_FF_with_Enable_Async Zero(clk, resetn, enable, 1'b1, q[0]);
	
endmodule
