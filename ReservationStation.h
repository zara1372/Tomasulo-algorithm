#ifndef TOMASULO_RS_H
#define TOMASULO_RS_H
class ReservationStation {
    public:
        int wy ,wz ,Ri ,Rl ,lat ,op ,result ,instNum ,ISSUE_Lat ,WRITEBACK_Lat;
        bool resultReady ,busy;
    public:
        ReservationStation();
        ReservationStation(int, int);
};
#endif 
