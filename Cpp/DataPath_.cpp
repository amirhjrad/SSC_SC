#include "DataPath_.h"

DataPath::DataPath(bus &clk, bus &rst, bus &cnt1, bus &clrC1, bus &co1, bus &cnt2, bus &ldC2, bus &clrTmpR, bus &ldTmpR, bus &clrMinR,
                   bus &ldMinR, bus &clrAddr, bus &ldAddr, bus &read, bus &write,  bus &swap, bus &selMinMax, bus &selC1C2, bus &co2) {
    this->clk = &clk;
    this->rst = &rst;
    this->cnt1 = &cnt1;
    this->clrC1 = &clrC1;
    this->co1 = &co1;
    this->cnt2 = &cnt2;
    this->ldC2 = &ldC2;
    this->clrTmpR = &clrTmpR;
    this->clrMinR = &clrMinR;
    this->ldMinR = &ldMinR;
    this->clrAddr = &clrAddr;
    this->read = &read;
    this->write = &write;
    this->swap = &swap;
    this->selMinMax = &selMinMax;
    this->selC1C2 = &selC1C2;
    this->co2 = &co2;
    
    cPin = "00000001";
    C1out = "XXXXXXXX";
    C2out = "XXXXXXXX"; 
    tmpRIn = "XXXXXXXXXXXXXXXX";
    tmpRout = "XXXXXXXXXXXXXXXX";
    minROut = "XXXXXXXXXXXXXXXX";
    AddrOut = "XXXXXXXX";
    M1Out = "XXXXXXXXXXXXXXXX";
    M2Out = "XXXXXXXXXXXXXXXX";
    Dout = "XXXXXXXXXXXXXXXX";

    Counter1 = new Counter8(clk, rst, cnt1, clrC1, co1, C1out);
    Counter2 = new Counter8(clk, rst, cnt2, ldC2, cPin, co2, C2out);
    tmpReg = new Reg16(clk, rst, clrTmpR, ldTmpR, Dout, tmpRout);
    minReg = new Reg16(clk, rst, clrMinR, ldMinR, Dout, minROut);
    minAddrReg = new Reg8(clk, rst, clrAddr, ldAddr, C1out, AddrOut);
    comp = new Comparator(tmpRout, minROut, swap);
    M1 = new MUX2to1(minROut, tmpRout, selMinMax, M1Out);
    M2 = new MUX2to1(C1out, C2out, selC1C2, M2Out);
    RF = new RegisterFile(clk, rst, read, write, M1Out, M2Out, Dout);
}

void DataPath::evl() {
    cPin = C1out + "1";
    Counter1->evl();
    Counter2->evl();
    M2->evl();
    M1->evl();
    RF->evl();
    tmpReg->evl();
    minReg->evl();
    minAddrReg->evl();
    comp->evl();
}
