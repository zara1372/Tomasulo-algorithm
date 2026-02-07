#include <iostream>
#include <iomanip>
#include <vector>
#include "Instruction.h"
#include "ReservationStation.h"
#include "RegisterStatus.h"
using namespace std;
const int n_Add = 5;
const int n_mull = 2;
const int n_div = 4;
const int AddOp = 2;
const int SubOp = 1;
const int MultOp = 0;
const int DivOp = 3;
const int ADD_Lat = 6;
const int MULT_Lat = 10;
const int DIV_Lat = 40;
const int ISSUE_Lat = 2;
const int WRITEBACK_Lat = 1;
int Clock = 0;
bool Done = true;
int Total_WRITEBACKS = 0;
int priv_issu = 0;
const int first_reg =2500;
const int reg_sEmpty = 500;
const int op_ready = 501;
const int op_int = 502;
int ISSUE(vector<Instruction>& Inst,vector<ReservationStation>& ResStat,
          vector<RegisterStatus>& RegStat,vector<int>& Register);
void EXECUTE(vector<Instruction>& Inst,vector<ReservationStation>& ResStat,
             vector<RegisterStatus>& RegStat,vector<int>& Register);
void WRITEBACK(vector<Instruction>& Inst,vector<ReservationStation>& ResStat,
               vector<RegisterStatus>& RegStat,vector<int>& Register);
void printInstructions(vector<Instruction> );
void printReservationStations(vector<ReservationStation> );
void printRegisterStatus(vector<RegisterStatus> );
void printTimingTable(vector<Instruction> );
int main(){
    Instruction
        I0(1,2,3,AddOp),I1(4,3,2,AddOp),I2(5,7,6,SubOp),I3(8,9,10,MultOp),I4(13,10,12,DivOp),
		I5(4,1,2,MultOp),I8(14,12,11,AddOp),I7(2,6,8,MultOp),I6(1,5,3,DivOp);
    vector<Instruction> Inst = {I0,I1,I2,I3,I4,I5,I6,I7,I8};
    ReservationStation
        ADD1(AddOp, op_int),ADD2(AddOp, op_int),ADD3(AddOp, op_int),
        ADD4(AddOp, op_int),ADD5(AddOp,op_int);
    ReservationStation
        MULT1(MultOp, op_int),MULT2(MultOp, op_int);
    ReservationStation
        DIV1(DivOp, op_int),DIV2(DivOp, op_int),
        DIV3(DivOp,op_int),DIV4(DivOp,op_int);
    vector<ReservationStation> Ress = {ADD1,ADD2,ADD3,ADD4,ADD5,MULT1,MULT2,DIV1,DIV2,DIV3,DIV4};
    RegisterStatus
        B0(reg_sEmpty),B1(reg_sEmpty),B2(reg_sEmpty),B3(reg_sEmpty),
        B4(reg_sEmpty), B5(reg_sEmpty),B6(reg_sEmpty),B7(reg_sEmpty),
        B8(reg_sEmpty),B9(reg_sEmpty),B10(reg_sEmpty),B11(reg_sEmpty),
        B12(reg_sEmpty),B13(reg_sEmpty),B14(reg_sEmpty);
    vector<RegisterStatus> RegisterStatus ={B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13 , B14};
    vector<int> Register = {first_reg,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    cout << "First VALUES:" << endl;
    printInstructions(Inst);
    printReservationStations(Ress);
    printRegisterStatus(RegisterStatus);
    cout << endl;
    do{
        Clock++;
        ISSUE(Inst,Ress,RegisterStatus,Register);
		EXECUTE(Inst,Ress,RegisterStatus,Register);
		WRITEBACK(Inst,Ress,RegisterStatus,Register);
        cout << endl;
        Done = false;
        if(Total_WRITEBACKS == Inst.size())
            Done = true;
        cout << endl;
	}while(!Done);
	printTimingTable(Inst);
     return 0;
}
int ISSUE(vector<Instruction>& INST,vector<ReservationStation>& Ress,
          vector<RegisterStatus>& reg_s,vector<int>& REG){
    int r = 0;
    bool rsFree = false;
    if(priv_issu >= INST.size())
            return 0;
    r = INST[priv_issu].op;
    int Add_begin = n_Add-n_Add;
    int Add_end = n_Add;
    int sub_begin = n_Add-n_Add;
    int sub_end = n_Add;
    int mul_begin = n_Add;
    int mul_end = n_Add+n_mull;
    int div_begin = n_Add+n_mull;
    int div_end = n_Add+n_mull+n_div;
    switch(r){
		case MultOp:
            for(int i=mul_begin;i<mul_end;i++){
                if(!Ress[i].busy){
                    r = i;
                    priv_issu++;
                    Ress[i].op = MultOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree)
                return 1;
            break;
        case DivOp:
            for(int i=div_begin;i<div_end;i++){
                if(!Ress[i].busy){
                    r = i;
                    priv_issu++;
                    Ress[i].op = DivOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree)
                return 1;
            break;
        case AddOp:
            for(int i=Add_begin;i<Add_end;i++){
                if(!Ress[i].busy){
                    r = i;
                    priv_issu++;
                    Ress[i].op = AddOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree)
                return 1;
            break;
        case SubOp:
            for(int i=sub_begin;i<sub_end;i++){
                if(!Ress[i].busy){
                    r = i;
                    priv_issu++;
                    Ress[i].op = SubOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree)
                return 1;
            break;
        default:
            break;
    }
    if(reg_s[INST[priv_issu-1].rs].wx == reg_sEmpty){
        Ress[r].Ri = REG[INST[priv_issu-1].rs];
        Ress[r].wy = op_ready;
    }
    else{
        Ress[r].wy = reg_s[INST[priv_issu-1].rs].wx;
    }
    if(reg_s[INST[priv_issu-1].rt].wx == reg_sEmpty){
        Ress[r].Rl = REG[INST[priv_issu-1].rt];
        Ress[r].wz = op_ready;
    }
    else{
        Ress[r].wz = reg_s[INST[priv_issu-1].rt].wx;
    }
    Ress[r].busy = true;
    Ress[r].ISSUE_Lat = 0;
    Ress[r].instNum = priv_issu-1;
    INST[priv_issu-1].issue_clk = Clock;
    reg_s[INST[priv_issu-1].rd].wx = r;
    return 2;
}
void EXECUTE(vector<Instruction>& INST,vector<ReservationStation>& Ress,
             vector<RegisterStatus>& reg_s,vector<int>& REG){
    for (int r=0;r<Ress.size();r++){
        if(Ress[r].busy == true){
            if(Ress[r].ISSUE_Lat >= ISSUE_Lat){
                if(Ress[r].wy == op_ready && Ress[r].wz == op_ready){
                    if(INST[Ress[r].instNum].exe_clk_s == 0)
                        INST[Ress[r].instNum].exe_clk_s = Clock;
                    Ress[r].lat++;
                    switch(Ress[r].op){
						case(MultOp):
                            if(Ress[r].lat == MULT_Lat){
                                Ress[r].result = Ress[r].Ri * Ress[r].Rl;
                                Ress[r].resultReady = true;
                                Ress[r].lat = 0;
                                INST[Ress[r].instNum].exe_clk_e = Clock;
                                Ress[r].ISSUE_Lat = 0;
                            }
                        case(DivOp):
                            if(Ress[r].lat == DIV_Lat){
                                Ress[r].result = Ress[r].Ri / Ress[r].Rl;
                                Ress[r].resultReady = true;
                                Ress[r].lat = 0;
                                INST[Ress[r].instNum].exe_clk_e = Clock;
                                Ress[r].ISSUE_Lat = 0;
                            }
                        case(AddOp):
                            if(Ress[r].lat == ADD_Lat){
                                Ress[r].result = Ress[r].Ri + Ress[r].Rl;
                                Ress[r].resultReady = true;
                                Ress[r].lat = 0;
                                INST[Ress[r].instNum].exe_clk_e = Clock;
                                Ress[r].ISSUE_Lat = 0;
                            }
                        case(SubOp):
                            if(Ress[r].lat == ADD_Lat){
                                Ress[r].result = Ress[r].Ri - Ress[r].Rl;
                                Ress[r].resultReady = true;
                                Ress[r].lat = 0;
                                INST[Ress[r].instNum].exe_clk_e = Clock;
                                Ress[r].ISSUE_Lat = 0;
                            }
                        default:
                            break;
                    }
                }
            }
            else
                Ress[r].ISSUE_Lat++;
        }
    }
}
void WRITEBACK(vector<Instruction>& INST,vector<ReservationStation>& Ress,
               vector<RegisterStatus>& reg_s,vector<int>& REG){
    for(int r=0;r<Ress.size();r++){
        if(Ress[r].resultReady){
            if(Ress[r].WRITEBACK_Lat == WRITEBACK_Lat){
                if(INST[Ress[r].instNum].wb_clk == 0)
                    INST[Ress[r].instNum].wb_clk = Clock;
                for(int x=0;x<REG.size();x++) {
                    if (reg_s[x].wx == r) {
                        REG[x] = Ress[r].result;
                        reg_s[x].wx = reg_sEmpty;
                    }
                }
                for(int y=0;y<Ress.size();y++){
                    if(Ress[y].wy==r){
                        Ress[y].Ri=Ress[r].result;
                        Ress[y].wy=op_ready;
                    }
                    if(Ress[y].wz==r){
                        Ress[y].Rl=Ress[r].result;
                        Ress[y].wz=op_ready;
                    }
                }
                Ress[r].resultReady = false;
                Ress[r].busy = false;
                Ress[r].wy , Ress[r].wz = op_int;
                Ress[r].Ri , Ress[r].Rl = 0;
                Ress[r].WRITEBACK_Lat = 0;
                Total_WRITEBACKS++;
            }
            else
                Ress[r].WRITEBACK_Lat++;
        }
    }

}
void printInstructions(vector<Instruction> IV){
    for(int i=0; i<IV.size(); i++)
        cout << "Instruction #: " << i << "  Operation: " <<
                IV[i].op << "  " <<
                IV[i].rd << " <- " << IV[i].rs << " op " <<
                IV[i].rt << endl;
}
void printReservationStations(vector<ReservationStation> RSV){
    for(int i=0; i<RSV.size(); i++)
        cout << "RS #: " << i << "  Busy: " << RSV[i].busy << "  op: "<<
                RSV[i].op << "  Ri: " << RSV[i].Ri << "  Rl: " <<
                RSV[i].Rl << "  wy: " << RSV[i].wy << "  wz: " <<
                RSV[i].wz << endl;
}
void printRegisterStatus(vector<RegisterStatus> RegisterStatusVector){
    cout << "Register Status: " << endl;
    for(int i=0; i<RegisterStatusVector.size(); i++)
        cout << RegisterStatusVector[i].wx << ' ';
    cout << endl;
}
void printTimingTable(vector<Instruction> INST){
    char separator    = ' ';
    const int width     = 5;
    char lineSeperator = '-';
    const int lineWidth = 15;

    cout << right << setw(width*5) << setfill(separator) << Clock;
    cout << endl;
    cout << left << setw(lineWidth) << setfill(lineSeperator);
    cout << endl;
    cout << left << setw(width) << setfill(separator) << "Inst";
    cout << left << setw(width) << setfill(separator) << "Issue";
    cout << left << setw(width) << setfill(separator) << "Execute";
    cout << left << setw(width) << setfill(separator) << "WB";
    cout << left << setw(width) << setfill(separator) << "SystemClock"
    cout << endl;

    for(int i=0;i<INST.size();i++){
        cout << left  << setw(width) << setfill(separator) << i;
        cout << left << setw(width) << setfill(separator) << INST[i].issue_clk;
        cout << INST[i].exe_clk_s <<  "-";
        cout << left << setw(width) << setfill(separator)  << INST[i].exe_clk_e;
        cout << left << setw(width) << setfill(separator) << INST[i].wb_clk;
        cout << endl;
    }
}