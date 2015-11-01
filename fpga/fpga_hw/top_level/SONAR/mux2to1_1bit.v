module mux2to1_1bit(input data1x, data0x, sel, output result);
	assign result = (data0x & ~sel) | (data1x	& sel);
endmodule
