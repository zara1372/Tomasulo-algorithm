#ifndef TOMASULO_REGSTATUS_H
#define TOMASULO_REGSTATUS_H
class RegisterStatus {
    public:
        bool busy;
        int wx;
    public:
        RegisterStatus();
        RegisterStatus(int);
};
#endif 