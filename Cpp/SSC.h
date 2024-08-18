#ifndef SSC_H
#define SSC_H
#include "DataPath_.h"
#include "Controller.h"

class SSC
{
    bus *clk, *rst, *start, *done;
    DataPath *DP;
    Controller *CT;

    bus cnt1, clrC1, co1, co2, cnt2, ldC2, clrTmpR, ldTmpR, clrMinR, ldMinR, clrAddr, ldAddr, read, write, swap, selMinMax, selC1C2;
public:
    SSC(bus &clk, bus &rst, bus &start, bus &done);
    ~SSC();
    void evl();
    void init();
};

#endif