#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "buses.h"

class Controller
{
    bus *clk, *rst, *start, *done, *clrC1, *ldC2, *clrTmpR, *clrMinR, *clrAddr, *read, *ldTmpR,
        *selC1C2, *swap, *cnt1, *cnt2, *co1, *co2, *write, *selMinMax, *ldAddr, *ldMinR;
    int ps, ns;
public:
    Controller(bus &clk, bus &rst, bus &start, bus &done, bus &clrC1, bus &ldC2, bus &clrTmpR, bus &ldMinR, bus &ldTmpR, bus &clrMinR, bus &clrAddr, bus &ldAddr,
               bus &read, bus &selC1C2, bus &swap, bus &cnt1, bus &cnt2, bus &co1, bus &co2, bus &write, bus &selMinMax);
    ~Controller();
    void evl();
};


#endif