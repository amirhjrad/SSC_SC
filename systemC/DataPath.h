#ifndef __DATAPATH_H__
#define __DATAPATH_H__
#include "systemc.h"
#include "components.h"

SC_MODULE(DataPath) {
    sc_in<sc_logic> clk, rst, cnt1, clrC1, cnt2, ldC2, clrTmpR, ldTmpR, clrMinR, ldMinR, clrAddr, ldAddr, read, write, selMinMax, selC1C2;
    sc_out<sc_logic> co1, co2, swap;

    sc_signal<sc_lv<8> >  C1out, cPin, C2out, M2Out, AddrOut;
    sc_signal<sc_lv<16> > tmpRIn, tmpRout, minRout, M1Out, Dout;

    sc_signal<sc_logic> nop;

    Counter8* Counter1;
    Counter8* Counter2;
    Reg16* tmpReg;
    Reg16* minReg;
    Reg8* minAddrReg;
    RegisterFile<8, 16>* RF;
    Comparator* comp;
    MUX2to1_16* M1;
    MUX2to1_8* M2;

    SC_CTOR(DataPath) {
        Counter1 = new Counter8("Counter1_ins");
            Counter1->clk(clk);
            Counter1->rst(rst);
            Counter1->cnt(cnt1);
            Counter1->clr(clrC1);
            Counter1->co(co1);
            Counter1->out(C1out);
            Counter1->ld(nop);
            Counter1->parIn(cPin);
        Counter2 = new Counter8("Counter2_ins");
            Counter2->clk(clk);
            Counter2->rst(rst);
            Counter2->cnt(cnt2);
            Counter2->ld(ldC2);
            Counter2->parIn(cPin);
            Counter2->co(co2);
            Counter2->out(C2out);
            Counter2->clr(nop);
        tmpReg = new Reg16("tmpReg_ins");
            tmpReg->clk(clk);
            tmpReg->rst(rst);
            tmpReg->clr(clrTmpR);
            tmpReg->ld(ldTmpR);
            tmpReg->parIn(Dout);
            tmpReg->out(tmpRout);
        minReg = new Reg16("minReg_ins");
            minReg->clk(clk);
            minReg->rst(rst);
            minReg->clr(clrMinR);
            minReg->ld(ldMinR);
            minReg->parIn(Dout);
            minReg->out(minRout);
        minAddrReg = new Reg8("minAddrReg_ins");
            minAddrReg->clk(clk);
            minAddrReg->rst(rst);
            minAddrReg->clr(clrAddr);
            minAddrReg->ld(ldAddr);
            minAddrReg->parIn(C1out);
            minAddrReg->out(AddrOut);
        comp = new Comparator("comp_ins");
            comp->A(tmpRout);
            comp->B(minRout);
            comp->lt(swap);
        M1 = new MUX2to1_16("M1_ins");
            M1->A(minRout);
            M1->B(tmpRout);
            M1->sel(selMinMax);
            M1->Y(M1Out);
        M2 = new MUX2to1_8("M2_ins");
            M2->A(C1out);
            M2->B(C2out);
            M2->sel(selC1C2);
            M2->Y(M2Out);
        RF = new RegisterFile <8,16> ("RF_ins");
            RF->clk(clk);
            RF->rst(rst);
            RF->read(read);
            RF->write(write);
            RF->Din(M1Out);
            RF->Addr(M2Out);
            RF->Dout(Dout);


        init();
        SC_METHOD(evl);
        sensitive << ldC2;
    }

    void init() {
        cPin = "00000001";
        C1out = "00000000";
        C2out = "00000000"; 
        tmpRIn = "0000000000000000";
        tmpRout = "0000000000000000";
        minRout = "0000000000000000";
        AddrOut = "00000000";
        M1Out = "0000000000000000";
        M2Out = "0000000000000000";
        Dout = "0000000000000000";
        nop.write(SC_LOGIC_0);
    }
    void evl() {
        sc_uint<8> tmp;
        tmp = C1out;
        cPin = tmp + 1;
    }
};

#endif