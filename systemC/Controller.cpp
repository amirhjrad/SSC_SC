#include "Controller.h"

void Controller::comb() {
    done = sc_logic_0;
    clrC1 = sc_logic_0;
    clrTmpR = sc_logic_0;
    ldTmpR = sc_logic_0;
    clrMinR = sc_logic_0;
    clrAddr = sc_logic_0;
    ldAddr = sc_logic_0;
    ldC2 = sc_logic_0;
    ldMinR = sc_logic_0;
    read = sc_logic_0;
    selC1C2 = sc_logic_0;
    cnt1 = sc_logic_0;
    cnt2 = sc_logic_0;
    write = sc_logic_0;
    selMinMax = sc_logic_0;

    switch (ps)
    {
    case 0: //Idle
        if (start == '1')
            ns = 1;
        else ns = 0;
        break;
    case 1: //Init
        clrC1 = sc_logic_1;
        ldC2 = sc_logic_1;
        clrTmpR = sc_logic_1;
        clrMinR = sc_logic_1;
        clrAddr = sc_logic_1;
        ns = 2;
        break;
    case 2: //Fetch D1
        read = sc_logic_1;
        selC1C2 = sc_logic_0;
        ldAddr = sc_logic_1;
        ldMinR = sc_logic_1;
        ns = 3;
        break;
    case 3: //Fetch D2
        read = sc_logic_1;
        selC1C2 = sc_logic_1;
        ldTmpR = sc_logic_1;
        ns = 4;
        break;
    case 4: //Compare
        if (swap == '1')
            ns = 7;
        else if (swap == '0')
            ns = 5;
        break;
    case 5: //Counter 2
        cnt2 = sc_logic_1;
        if (co2 == '1')
            ns = 6;
        else if (co2 == '0')
            ns = 3;
        break;
    case 6: //Counter 1
        cnt1 = sc_logic_1;
        ldC2 = sc_logic_1;
        if (co1 == '1')
            ns = 10;
        else if (co1 == '0')
            ns = 2;
        break;
    case 7: // update 0
        selC1C2 = sc_logic_1;
        write = sc_logic_1;
        selMinMax = sc_logic_0;
        ns = 8;
        break;
    case 8: //update 1
        selC1C2 = sc_logic_0;
        write = sc_logic_1;
        selMinMax = sc_logic_1;
        ns = 9;
        break;
    case 9: //update 2
        selC1C2 = sc_logic_0;
        read = sc_logic_1;
        ldAddr = sc_logic_1;
        ldMinR = sc_logic_1;
        ns = 5;
        break;
    case 10: //end
        done = sc_logic_1;
        cout << "done\n";
        ns = 0;
        break;
    default:
        ns = 0;
        break;
    }
}

void Controller::seq() {
    while (true)
    {
    if (rst == '1')
        ps = 0;
    else if (clk.event() && clk == '1')
        ps = ns;
    wait();
    }
}