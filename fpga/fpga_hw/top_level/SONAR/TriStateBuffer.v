/*
Anthony De Caria - April 5, 2013

This is a tri-state buffer.
*/
module TriStateBuffer (In, Select, Out);
	//	I/Os	//
	input In, Select;
	output reg Out;
	
	always@(In, Select)
	begin
		if (Select == 0)
		begin
			Out <= 1'bz;
		end
		else
		begin
			Out <= In;
		end
	end
endmodule
