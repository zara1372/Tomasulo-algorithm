#include "ReservationStation.h"
ReservationStation::ReservationStation(){
    busy = false;
    op , lat , result = 0;
    resultReady = false;
    wy , wz = 1;
    Ri , Rl = 0;
    instNum = 31000;
    ISSUE_Lat , WRITEBACK_Lat = 0;
}
ReservationStation::ReservationStation(int OP, int RSoperandAvailable){
    busy = false;
    op = OP;
    lat , result = 0;
    resultReady = false;
    wy , wz = RSoperandAvailable;
    Ri , Rl = 0;
    instNum = 31000;
    ISSUE_Lat , WRITEBACK_Lat = 0;

}