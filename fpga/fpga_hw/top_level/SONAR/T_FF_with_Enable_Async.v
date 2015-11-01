/*
Anthony De Caria - April 5, 2014

This is a T Flip Flop that has an enable and is asyncronous.
*/

module T_FF_with_Enable_Async(clk, resetn, enable, d, q);
	
	input clk;
	input resetn;
	input enable;
	input d;
	output reg q;
	
	always @(posedge clk or negedge resetn)
	begin
		if (!resetn)
		begin
			q <= 1'b0;
		end
		else
		begin
			if (enable)
			begin
				if (d)
				begin
				q <= !q;
				end
			end
		end
	end
	
endmodule
