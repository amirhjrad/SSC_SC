#include "SSC.h"

SC_MODULE(TB) {
    sc_signal<sc_logic> clk, rst, start, done;
    SSC *UUT;
    SC_CTOR(TB){
        UUT = new SSC("SSC_ins");
        UUT->clk(clk);
        UUT->rst(rst);
        UUT->start(start);
        UUT->done(done);
        SC_THREAD(clocking);
        SC_THREAD(rsting);
        SC_THREAD(inputing);
    }

    void inputing(){
        start = sc_logic_0;
        wait(3,SC_NS);
        start = sc_logic_1;
        wait(3,SC_NS);
        start = sc_logic_0;
    }

    void rsting(){
        rst = sc_logic_0;
    }

    void clocking(){
        while (1)
        {
            clk = sc_logic_0;
            wait(1,SC_NS);
            clk = sc_logic_1;
            wait(1,SC_NS);
        }
    }
};