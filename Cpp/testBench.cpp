#include "SSC.h"

int main() {
    bus clk, rst, start, done;
    SSC *UUT = new SSC(clk, rst, start, done);
    clk = "P";
    UUT->init();
    start = "1";
    while (1)
    {
        UUT->evl();
        if (done == "1") {
            cout <<"done\n";
            break;
        }
    }
    
}