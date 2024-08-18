#ifndef COMPONENT_H
#define COMPONENT_H
#include "buses.h"
#include <fstream>

class Counter8
{
    bus *clk, *rst, *cnt, *clr, *ld, *parIn;
    bus *co, *out;
public:
    Counter8(bus &clk, bus &rst, bus &cnt, bus &clr, bus &co, bus &out) {
        this->clk = &clk;
        this->rst = &rst;
        this->cnt = &cnt;
        this->clr = &clr;
        this->co = &co;
        this->out = &out;
        this->ld = nullptr;
    }
    Counter8(bus &clk, bus &rst, bus &cnt, bus &ld, bus &parIn, bus &co, bus &out) {
        this->clk = &clk;
        this->rst = &rst;
        this->cnt = &cnt;
        this->ld = &ld;
        this->co = &co;
        this->parIn = &parIn;
        this->out = &out;
        this->clr = nullptr;
    }
    ~Counter8();
    void evl() {
        if (*rst == "1")
            out->fill('0');
        if (*clk == "P") {
            if (*cnt == "1")
                *out = *out + "1";
            if (clr != nullptr)
                if (*clr == "1")
                    out->fill('0');
            if (ld != nullptr)
                if (*ld == "1")
                    *out = *parIn;
        }
        if (*out == "11111111")
            co->fill('1');
        else
            co->fill('0');
    };
};

class Reg16
{
public:
    bus *clk, *rst, *clr, *ld, *parIn;
    bus *out;
    Reg16(bus &clk, bus &rst, bus &clr, bus &ld, bus &parIn, bus &out) {
        this->clk = &clk;
        this->rst = &rst;
        this->clr = &clr;
        this->ld = &ld;
        this->parIn = &parIn;
        this->out = &out;
    }
    ~Reg16();
    void evl() {
        if (*rst == "1")
            out->fill('0');
        if (*clk == "P") {
            if (*clr == "1")
                out->fill('0');
            if (*ld == "1")
                *out = *parIn;
        }
    }
};

class Reg8
{
public:
    bus *clk, *rst, *clr, *ld, *parIn;
    bus *out;
    Reg8(bus &clk, bus &rst, bus &clr, bus &ld, bus &parIn, bus &out) {
        this->clk = &clk;
        this->rst = &rst;
        this->clr = &clr;
        this->ld = &ld;
        this->parIn = &parIn;
        this->out = &out;
    }
    ~Reg8();
    void evl() {
        if (*rst == "1")
            out->fill('0');
        if (*clk == "P") {
            if (*clr == "1")
                out->fill('0');
            if (*ld == "1")
                *out = *parIn;
        }
    }
};

class Comparator
{
public:
    bus *A, *B;
    bus * lt;
    Comparator(bus &A, bus &B, bus &lt) {
        this->A = &A;
        this->B = &B;
        this->lt = &lt;
    }
    ~Comparator();
    void evl() {
        if (*A < *B)
            lt->fill('1');
        else lt->fill('0');
    }
};

class MUX2to1
{
public:
    bus *A, *B, *sel;
    bus *Y;
    MUX2to1(bus &A, bus &B, bus &sel, bus &Y) {
        this->A = &A;
        this->B = &B;
        this->sel = &sel;
        this->Y = &Y;
    }
    ~MUX2to1();
    void evl() {
        if (*sel == "0")
            *Y = *A;
        else if (*sel == "1")
            *Y = *B;
    }
};

class RegisterFile
{
    bus *rst, *clk, *read, *write, *Din, *Addr;
	bus *Dout;
	bus *mem;
	int N;
	public:
		RegisterFile(bus& clk, bus& rst, bus& read, bus& write,
			         bus& Din, bus& Addr, bus& Dout) {
                        this->clk = &clk;
                        this->rst = &rst;
                        this->read = &read;
                        this->write = &write;
                        this->Din = &Din;
                        this->Addr = &Addr;
                        this->Dout = &Dout;

                        this->Dout->fill('X');
                        int LEN = 16;
                        int ADS = 8;
                        N = int(pow(2.0, ADS));
                        mem = new bus[N];
                        for (int i=0; i < N; i++) {
                            mem[i].resize(LEN, '0'); 
                        }
                     }
		~RegisterFile ();
		void init (const string& filename) {
            ifstream finp(filename);
            for (int i = 0; i < N; i++) {
                finp >> mem[i]; 
                // cout << mem[i] << "\n";
            }
        }
		void evl () {
            if (rst->at(0) == "1") {
                for (int i = 0; i < N; i++) mem[i].fill('0');
            }
            else if (read->at(0) == "1") {
                *Dout = mem[Addr->ival()];
            }
            else if (clk->at(0) == "P") {
                if (write->at(0) == "1") {
                    mem[Addr->ival()] = *Din;
                }
            }
        }
		void dump (const string& filename) {
            ofstream fout(filename);
            for (int i = 0; i < N; i++) {
                fout << mem[i] << "\n"; 
                cout << mem[i] << "\n"; 
            }
        }
};


#endif