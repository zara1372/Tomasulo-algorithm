#include "Instruction.h"
Instruction::Instruction() {
    = 0;
    rs , rt , rd , op , issue_clk , exe_clk_s , exe_clk_e , wb_clk = 0;
}
Instruction::Instruction(int RS = rs, int RT = rt ,int RD = rd, int OP = op) {
    issue_clk ,  exe_clk_s , exe_clk_e , wb_clk  = 0;
}