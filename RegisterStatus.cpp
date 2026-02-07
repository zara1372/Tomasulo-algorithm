#include "RegisterStatus.h"
RegisterStatus::RegisterStatus(){
    busy = false;
    wx = 0;
}
RegisterStatus::RegisterStatus(int RegStatusEmpty) {
    wx = RegStatusEmpty;
}