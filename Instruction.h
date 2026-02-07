#ifndef TOMASULO_INSTRUCTION_H
#define TOMASULO_INSTRUCTION_H
class Instruction {
    public:
        int rs , rt , rd , op , issue_clk , exe_clk_s , exe_clk_e ,wb_clk;
    public:
        Instruction();
        Instruction(int,int,int,int);
};
#endif 