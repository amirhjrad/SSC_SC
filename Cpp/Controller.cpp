#include "Controller.h"

Controller::Controller(bus &clk, bus &rst, bus &start, bus &done, bus &clrC1, bus &ldC2, bus &clrTmpR, bus &ldMinR, bus &ldTmpR,
                       bus &clrMinR, bus &clrAddr, bus &ldAddr, bus &read, bus &selC1C2, bus &swap, bus &cnt1, bus &cnt2,
                       bus &co1, bus &co2, bus &write, bus &selMinMax) {
    this->clk = &clk;
    this->rst = &rst;
    this->start = &start;
    this->done = &done;
    this->clrC1 = &clrC1;
    this->ldC2 = &ldC2;
    this->clrTmpR = &clrTmpR;
    this->clrMinR = &clrMinR;
    this->clrAddr = &clrAddr;
    this->ldAddr = &ldAddr;
    this->read = &read;
    this->selC1C2 = &selC1C2;
    this->swap = &swap;
    this->cnt1 = &cnt1;
    this->cnt2 = &cnt2;
    this->co1 = &co1;
    this->co2 = &co2;
    this->write = &write;
    this->selMinMax = &selMinMax;
    this->ldMinR = &ldMinR;
    this->ldTmpR = &ldTmpR;
    ps = 0;
    ns = 0;
}

void Controller::evl() {
    *done = "0";
    *clrC1 = "0";
    *clrTmpR = "0";
    *ldTmpR = "0";
    *clrMinR = "0";
    *clrAddr = "0";
    *ldAddr = "0";
    *ldC2 = "0";
    *ldMinR = "0";
    *read = "0";
    *selC1C2 = "0";
    *cnt1 = "0";
    *cnt2 = "0";
    *write = "0";
    *selMinMax = "0";



    switch (ps)
    {
    case 0: //Idle
        if (*start == "1")
            ns = 1;
        else ns = 0;
        break;
    case 1: //Init
        *clrC1 = "1";
        *ldC2 = "1";
        *clrTmpR = "1";
        *clrMinR = "1";
        *clrAddr = "1";
        ns = 2;
        break;
    case 2: //Fetch D1
        *read = "1";
        *selC1C2 = "0";
        *ldAddr = "1";
        *ldMinR = "1";
        ns = 3;
        break;
    case 3: //Fetch D2
        *read = "1";
        *selC1C2 = "1";
        *ldTmpR = "1";
        ns = 4;
        break;
    case 4: //Compare
        if (*swap == "1")
            ns = 7;
        else if (*swap == "0")
            ns = 5;
        break;
    case 5: //Counter 2
        *cnt2 = "1";
        if (*co2 == "1")
            ns = 6;
        else if (*co2 == "0")
            ns = 3;
        break;
    case 6: //Counter 1
        *cnt1 = "1";
        *ldC2 = "1";
        if (*co1 == "1")
            ns = 10;
        else if (*co1 == "0")
            ns = 2;
        break;
    case 7: // update 0
        *selC1C2 = "1";
        *write = "1";
        *selMinMax = "0";
        ns = 8;
        break;
    case 8: //update 1
        *selC1C2 = "0";
        *write = "1";
        *selMinMax = "1";
        ns = 9;
        break;
    case 9: //update 2
        *selC1C2 = "0";
        *read = "1";
        *ldAddr = "1";
        *ldMinR = "1";
        ns = 5;
        break;
    case 10: //end
        *done = "1";
        ns = 0;
        break;
    default:
        ns = 0;
        break;
    }


    if (*rst == "1")
        ps = 0;
	else if (*clk == "P") 
        ps = ns;
}