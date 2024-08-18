#include "components.h"

void Counter8::evl() {
    while (true)
    {
        if (rst == '1')
                tmpOut = 0;
        else if (clk.event() && clk== '1') {
            if (cnt == '1')
                tmpOut = tmpOut + 1;
            if (clr == '1')
                tmpOut = 0;
            if (ld == '1')
                tmpOut = parIn;
        }
        if (tmpOut == 255)
            co = sc_logic_1;
        else
            co = sc_logic_0;
        out = tmpOut;
        wait();
    }
    
}


void Reg16::evl() {
    while (true)
    {
        if (rst == '1')
                tmpOut = 0;
        else if (clk.event() && clk == '1') {
            if (clr == '1')
                tmpOut = 0;
            if (ld == '1')
                tmpOut = parIn;
        }
        out = tmpOut;
        wait();
    }
}

void Reg8::evl() {
    while (true)
    {
        if (rst == '1')
                tmpOut = 0;
        if (clk == '1') {
            if (clr == '1')
                tmpOut = 0;
            if (ld == '1')
                tmpOut = parIn;
        }
        out = tmpOut;
        wait();
    }
}

void Comparator::evl() {
    tmpA = A.read();
    tmpB = B.read();
    if (tmpA < tmpB)
        lt = sc_logic_1;
    else lt = sc_logic_0;
}

void MUX2to1_8::evl() {
    if (sel == '0')
        Y = A;
    else if (sel == '1')
        Y = B;
}

void MUX2to1_16::evl() {
    if (sel == '0')
        Y = A;
    else if (sel == 1)
        Y = B;
}
