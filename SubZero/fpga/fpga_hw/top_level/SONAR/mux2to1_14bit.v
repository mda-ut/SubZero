module mux2to1_14bit(data1, data0, sel, result);
	input [13:0] data0, data1;
	input sel;
	output reg [13:0] result;
	
	always@(sel)
	begin
		if (~sel)
		begin
			result <= data0;
		end
		else
		begin
			result <= data1;
		end
	end
endmodule
