```
# Tomasulo-algorithm
Steps of program implementation :

A. setup reservation station 

//number of reservationstation & reservation station latency & Datapath latency 
& input reservation station---
1.
const int n_Add = 5;
const int n_mull = 2;
const int n_div = 4;
2.
const int ADD_Lat = 6;
const int MULT_Lat = 10;
const int DIV_Lat = 40;
3.
const int ISSUE_Lat = 2;
const int WRITEBACK_Lat = 1;
4.
ReservationStation for addinstruction
ADD1(AddOp, op_int),ADD2(AddOp, op_int),ADD3(AddOp, op_int),
ADD4(AddOp, op_int),ADD5(AddOp,op_int);
ReservationStation for mulinstruction
MULT1(MultOp, op_int),MULT2(MultOp, op_int);
ReservationStation for divinstruction
DIV1(DivOp, op_int),DIV2(DivOp, op_int),
DIV3(DivOp, op_int),DIV4(DivOp,op_int);

!!! Note: There are now 14 registrations. 
To have fewer clocks, you must add the number from the REGISTER STATUS section!!!

5.
RegisterStatus
B0(reg_sEmpty),B1(reg_sEmpty),B2(reg_sEmpty),B3(reg_sEmpty),
B4(reg_sEmpty), B5(reg_sEmpty),B6(reg_sEmpty),B7(reg_sEmpty),
B8(reg_sEmpty),B9(reg_sEmpty),B10(reg_sEmpty),B11(reg_sEmpty),
B12(reg_sEmpty),B13(reg_sEmpty),B14(reg_sEmpty);

!!! When resetting the program, keep in mind that the logic of these instructions is as follows:
In parentheses opposite each I, the first value is RD, which is the destination register, the second option
is RS, which is the first source operand, and finally RT, which is the second source operand.
In front of each instruction is also shown the OPCODE that is performed !!!

 6.
Input instructions
Instruction
I0(1,2,3,AddOp),I1(4,3,2,AddOp),I2(5,7,6,SubOp),I3(8,9,10,MultOp),I4(13,10,12,DivOp),
I5(4,1,2,MultOp),I8(14,12,11,AddOp),I7(2,6,8,MultOp),I6(1,5,3,DivOp);

!!! At this point, the program will be completed, quantified and fully implemented.
The displayed output will show the ISSUE EXECUTE WRITEBACK timeline for 
consistent content of each instruction in each clock cycle!!!

7.

      Inst    Issue        Execute      WB        SystemClock
                                                      22

       0        1            3-8         9
       1        2            4-9         10 
       2        3            5-10        11
       3        4            6-11        12
       4        5            7-12        13
       5        6            10-15       16
       6        7            12-17       18
       7        13           15-20       21
       8        14           16-21       22


EXAMPLE :
//For example: explain the demo file above to test this program---

Input program instructions
I0(1,2,3,AddOp),
I1(4,3,2,AddOp),
I2(5,7,6,SubOp),
I3(8,9,10,MultOp),
I4(13,10,12,DivOp),
I5(4,1,2,MultOp),
I8(14,12,11,AddOp),
I7(2,6,8,MultOp),
I6(1,5,3,DivOp);

Initial Register File Values
F0(reg_sEmpty) = 2500
F1(reg_sEmpty) = 1
F2(reg_sEmpty) = 2
F3(reg_sEmpty) = 3
F4(reg_sEmpty) = 4
F5(reg_sEmpty) = 5
F6(reg_sEmpty) = 6
F7(reg_sEmpty) = 7
F8(reg_sEmpty) = 8
F9(reg_sEmpty) = 9
F10(reg_sEmpty) = 10
F11(reg_sEmpty) =11
F12(reg_sEmpty) =12
F13(reg_sEmpty) = 13
F14(reg_sEmpty) = 14

run & debug program

Output display:

     Inst      Issue     Execute        WB        SystemClock
                                                      22

       0        1          3-8          9
       1        2          4-9          10 
       2        3          5-10         11
       3        4          6-11         12
       4        5          7-12         13
       5        6          10-15        16
       6        7          12-17        18
       7        13         15-20        21
       8        14         16-21        22

!!!Important Note: You must enter the commands of this program manually.
This program does not have the command to load from memory and store to memory automatically.
Changing the number of reservation stations directly effects the change of time!!!


```
