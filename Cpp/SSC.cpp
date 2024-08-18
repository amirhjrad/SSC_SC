#include "SSC.h"

SSC::SSC(bus &clk, bus &rst, bus &start, bus &done) {
    this->clk = &clk;
    this->rst = &rst;
    this->start = &start;
    this->done = &done;

    DP = new DataPath(clk, rst, cnt1, clrC1, co1, cnt2, ldC2, clrTmpR, ldTmpR, clrMinR, ldMinR, clrAddr, ldAddr, read, write, swap, selMinMax, selC1C2, co2);
    CT = new Controller(clk, rst, start, done, clrC1, ldC2, clrTmpR, ldMinR, ldTmpR, clrMinR, clrAddr, ldAddr, read, selC1C2, swap, cnt1, cnt2, co1, co2, write,selMinMax);
}

void SSC::evl() {
    CT->evl();
    DP->evl();
    if (*done == "1")
        DP->expRF("out.txt");
}

void SSC::init() {
    *rst = "1";
    DP->evl();
    CT->evl();
    *rst = "0";
    DP->initRF("mem.txt");
}