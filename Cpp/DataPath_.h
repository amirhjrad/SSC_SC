#ifndef DATAPATH_H
#define DATAPATH_H
#include "components.h"

class DataPath
{
    bus *clk, *rst, *cnt1, *clrC1, *co1, *co2, *cnt2, *ldC2, *clrTmpR, *ldTmpR, *clrMinR, 
        *ldMinR, *clrAddr, *ldAddr, *read, *write,  *swap, *selMinMax, *selC1C2;

    bus C1out, cPin, C2out, tmpRIn, tmpRout, minROut, AddrOut, M1Out, M2Out, Dout;

    Counter8 *Counter1;
    Counter8 *Counter2;
    Reg16 *tmpReg;
    Reg16 *minReg;
    Reg8 *minAddrReg;
    RegisterFile *RF;
    Comparator *comp;
    MUX2to1 *M1;
    MUX2to1 *M2;

public:
    DataPath(bus &clk, bus &rst, bus &cnt1, bus &clrC1, bus &co1, bus &cnt2, bus &ldC2, bus &clrTmpR, bus &ldTmpR, bus &clrMinR,
             bus &ldMinR, bus &clrAddr, bus &ldAddr, bus &read, bus &write,  bus &swap, bus &selMinMax, bus &selC1C2, bus &co2);
    ~DataPath();
    void evl();
    void initRF(const string filename) { RF->init(filename); }
    void expRF(const string filename) { RF->dump(filename); }
};

#endif

