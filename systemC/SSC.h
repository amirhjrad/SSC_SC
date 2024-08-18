#ifndef __SSC_H__
#define __SSC_H__
#include "DataPath.h"
#include "Controller.h"

SC_MODULE(SSC){
    sc_in<sc_logic> clk, rst, start;
    sc_out<sc_logic> done;

    sc_signal<sc_logic> cnt1, clrC1, co1, co2, cnt2, ldC2, clrTmpR, ldTmpR, clrMinR, ldMinR, 
                        clrAddr, ldAddr, read, write, swap, selMinMax, selC1C2;

    DataPath *DP;
    Controller *CT;

    SC_CTOR(SSC) {
        DP = new DataPath("DataPath_ins");
            DP->clk(clk);
            DP->rst(rst);
            DP->cnt1(cnt1);
            DP->clrC1(clrC1);
            DP->co1(co1);
            DP->cnt2(cnt2);
            DP->ldC2(ldC2);
            DP->ldMinR(ldMinR);
            DP->clrTmpR(clrTmpR);
            DP->ldTmpR(ldTmpR);
            DP->clrMinR(clrMinR);
            DP->clrAddr(clrAddr);
            DP->ldAddr(ldAddr);
            DP->read(read);
            DP->write(write);
            DP->swap(swap);
            DP->selMinMax(selMinMax);
            DP->selC1C2(selC1C2);
            DP->co2(co2);
        CT = new Controller("Controller_ins");
            CT->clk(clk);
            CT->rst(rst);
            CT->start(start);
            CT->done(done);
            CT->clrC1(clrC1);
            CT->ldC2(ldC2);
            CT->clrTmpR(clrTmpR);
            CT->ldMinR(ldMinR);
            CT->ldTmpR(ldTmpR);
            CT->clrMinR(clrMinR);
            CT->clrAddr(clrAddr);
            CT->ldAddr(ldAddr);
            CT->read(read);
            CT->selC1C2(selC1C2);
            CT->swap(swap);
            CT->cnt1(cnt1);
            CT->cnt2(cnt2);
            CT->co1(co1);
            CT->co2(co2);
            CT->write(write);
            CT->selMinMax(selMinMax);
    }

};

#endif