//control unit for write enable and ALU control

`include "define.v"

module control(
  input [5:0] inst_cntrl, 
  output reg wen_cntrl,
  output reg alusrc_cntrl,
  output reg regdst_cntrl,
  output reg [2:0] aluop_cntrl,
  output reg memwrite_cntrl,
  output reg memtoreg_cntrl
 
  
  );
  
  always@(inst_cntrl)
  begin
 
    case(inst_cntrl)
			`ADD: begin
					wen_cntrl=1;
					alusrc_cntrl=0;
					regdst_cntrl=1;
					aluop_cntrl=inst_cntrl[2:0];
					memwrite_cntrl=0;
					memtoreg_cntrl=1;
			end
        `SUB: begin
                wen_cntrl=1;
					 alusrc_cntrl=0;
					 regdst_cntrl=1;
                aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
        end
        `AND: begin
                wen_cntrl=1;
					 alusrc_cntrl=0;
					 regdst_cntrl=1;
                aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
        end
        `XOR: begin
                wen_cntrl=1;
					 alusrc_cntrl=0;
					 regdst_cntrl=1;
                aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
        end
     
        `COM: begin
                wen_cntrl=1;
					 alusrc_cntrl=0;
					 regdst_cntrl=1;
                aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
        end
        `MUL: begin
                wen_cntrl=1;
					 alusrc_cntrl=0;
					 regdst_cntrl=1;
					 aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
			end
		`ADDI: begin
                wen_cntrl=1;
					 alusrc_cntrl=1;
					 regdst_cntrl=0;
					 aluop_cntrl=inst_cntrl[2:0];
					 memwrite_cntrl=0;
					 memtoreg_cntrl=1;
        end
		  	`LW: begin
                wen_cntrl=1;
					 alusrc_cntrl=1;
					 regdst_cntrl=0;
					 aluop_cntrl=3'b000;//opcode for addition
					 memwrite_cntrl=0;
					 memtoreg_cntrl=0;
        end
		   `SW: begin
                wen_cntrl=0;
					 alusrc_cntrl=1;//As the instruction stops in DMEM regdst, wen and MemtoReg is not needed.
					 aluop_cntrl=3'b000;//opcode for addition
					 memwrite_cntrl=1;
					 regdst_cntrl=0;
					 memtoreg_cntrl=0;
					 
				end	
		
		default: begin
				wen_cntrl=1;//the default condition is set for R type inst
				alusrc_cntrl=0;
				regdst_cntrl=1;
				aluop_cntrl=inst_cntrl[2:0];
				 memwrite_cntrl=0;
				memtoreg_cntrl=1;
		end	
		
    endcase
  end
  
endmodule
