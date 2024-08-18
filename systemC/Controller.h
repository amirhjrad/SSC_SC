#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "systemc.h"

SC_MODULE(Controller) {
    sc_in<sc_logic> clk, rst, start, swap, co1, co2;
    sc_out<sc_logic> done, clrC1, ldC2, clrTmpR, clrMinR, clrAddr, read, ldTmpR, 
                     selC1C2, cnt1, cnt2, write, selMinMax, ldAddr, ldMinR;

    // enum states {Idle, Init, Fetch_D1, Fetch_D2, Compare, Counter2, Counter1, update0, update1, update2, End};

    // sc_signal<states> ps, ns;
    sc_signal<int> ps, ns;

    SC_CTOR(Controller) {
        SC_METHOD(comb);
        sensitive << ps << start << swap << co1 << co2;
        SC_THREAD(seq);
        sensitive << clk << rst;
    }

    void comb();
    void seq();
};

#endif