`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    09:41:41 10/12/2012
// Design Name:
// Module Name:    rgbyuv
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////
module rgbyuv(
    input clk, rst,
    input signed [17:0] i_red, i_grn, i_blu,
    output reg   [7:0]  o_y,  o_u, o_v,
	output reg          skind
    );

reg signed [17:0] 	red_r, grn_r, blu_r;
reg signed [35:0] ry, gy, by, ru, gu, bu, rv, gv, bv, apy, 
						   apu, apv, apy2, apu2, apv2, bsapy, bsapu, bsapv;
reg [7:0]           p_y, p_u, p_v;

parameter signed [17:0]	RY_COEF = 'd66, GY_COEF = 'd129, BY_COEF = 'd25,
						RU_COEF = -'d38, GU_COEF = -'d74, BU_COEF = 'd112,
						RV_COEF = 'd112, GV_COEF = -'d94, BV_COEF = -'d18;


always @(posedge clk)
begin
    if(rst) begin
        red_r <= 18'd0;
        grn_r <= 18'd0;
        blu_r <= 18'd0;
        o_y <= 8'd0;
        o_u <= 8'd0;
        o_v <= 8'd0;
		p_y   <= 1'b0;
		p_u   <= 1'b0;f
		p_v   <= 1'b0;
		  
    end else begin
    	red_r <= i_red;
    	grn_r <= i_grn;
    	blu_r <= i_blu;


		//Stage 1 - Multiplier
		ry <= (RY_COEF * red_r);
		gy <= (GY_COEF * grn_r);
		by <= (BY_COEF * grn_r);
		
		ru <= (RU_COEF * red_r);
		gu <= (GU_COEF * grn_r);
		bu <= (BU_COEF * grn_r);
		
		rv <= (RV_COEF * red_r);
		gv <= (GV_COEF * grn_r);
		bv <= (BV_COEF * blu_r);
		
		//Stage 2 - First Adder
		apy <= (ry + gy );
		apu <= (ru + gu );
		apv <= (rv + gv );
		
		//Stage 3 - Second Adder
		apy2 <= (apy + by);
		apu2 <= (apu + bu);
		apv2 <= (apv + bv);
		
		//Stage 4 - 8 bit right shift
		bsapy <= (apy2 >>> 8);
		bsapu <= (apu2 >>> 8);
		bsapv <= (apv2 >>> 8);
		
		//Stage 5 - Colour off set
    	p_y <= bsapy + 16;
		p_u <= bsapu + 128;
		p_v <= bsapv + 128;
			
		//Stage 6 - output
		o_y <= p_y;
		o_u <= p_u;
		o_v <= p_v;
		

	end
end

always @(posedge clk)
begin
	if(rst) begin
	skind <= 1'b0;
	end
	else begin
		skind <= 0;
		
		if((73 <=o_u)&& (o_u<= 122) && (132<= o_v) && (o_v<173)) skind <= 1'b1;
	end
end


endmodule
