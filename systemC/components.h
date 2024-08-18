#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <systemc.h>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;

SC_MODULE(Counter8) {
    sc_in<sc_logic> clk, rst, cnt, clr, ld;
    sc_in<sc_lv<8> > parIn;
    sc_out<sc_logic> co;
    sc_out<sc_lv<8> > out;

    sc_uint<8> tmpOut;

    SC_CTOR(Counter8) {
        SC_THREAD(evl);
        sensitive << rst << clk ;
    }
    void evl();
};


SC_MODULE(Reg16) {
    sc_in<sc_logic> clk, rst, clr, ld;
    sc_in<sc_lv<16> > parIn;
    sc_out<sc_lv<16> > out;

    sc_uint<16> tmpOut;

    SC_CTOR(Reg16) {
        SC_THREAD(evl);
        sensitive << rst << clk;
    }

    void evl();
};


SC_MODULE(Reg8) {
    sc_in<sc_logic> clk, rst, clr, ld;
    sc_in<sc_lv<8> > parIn;
    sc_out<sc_lv<8> > out;

    sc_uint<8> tmpOut;

    SC_CTOR(Reg8) {
        SC_THREAD(evl);
        sensitive << rst << clk;
    }
    void evl();
};

SC_MODULE(Comparator) {
    sc_in<sc_lv<16> > A, B;
    sc_out<sc_logic> lt;

    sc_uint<16> tmpA, tmpB;

    SC_CTOR(Comparator) {
        SC_METHOD(evl);
        sensitive << A << B;
    }

    void evl();
};

SC_MODULE(MUX2to1_8) {
    sc_in<sc_lv<8> > A, B;
    sc_in<sc_logic> sel;
    sc_out<sc_lv<8> > Y;

    SC_CTOR(MUX2to1_8) {
        SC_METHOD(evl);
        sensitive << A << B << sel;
    }
    void evl();
};

SC_MODULE(MUX2to1_16) {
    sc_in<sc_lv<16> > A, B;
    sc_in<sc_logic> sel;
    sc_out<sc_lv<16> > Y;

    SC_CTOR(MUX2to1_16) {
        SC_METHOD(evl);
        sensitive << A << B << sel;
    }
    void evl();
};

template<int ADDRESS, int WORD_LENGTH>
class RegisterFile : public sc_module {
public:
	sc_in<sc_logic> clk, rst, read, write;
	sc_in<sc_lv<ADDRESS> > Addr;
	sc_in<sc_lv<WORD_LENGTH> > Din;
	sc_out<sc_lv<WORD_LENGTH> > Dout;

	int addrSpace;
	sc_uint <WORD_LENGTH> *mem;

	void meminit();
	void resetting();
	void memread();
	void memwrite();
	void memdump();

	SC_HAS_PROCESS(RegisterFile);
	RegisterFile(sc_module_name);
};

template<int ADDRESS, int WORD_LENGTH>
RegisterFile<ADDRESS, WORD_LENGTH>::RegisterFile(sc_module_name) 
{
	addrSpace = int(pow(2.0, ADDRESS));
	mem = new sc_uint<WORD_LENGTH>[addrSpace];

	SC_THREAD(meminit);
    SC_THREAD(resetting);
    sensitive << rst.pos();
	SC_METHOD(memread);
	sensitive << Addr << read;
	SC_THREAD(memwrite);
	sensitive << Addr << Din << write << clk.pos();
	// SC_METHOD(memdump);
}

template<int ADDRESS, int WORD_LENGTH>
void RegisterFile<ADDRESS, WORD_LENGTH>::meminit() {
    ifstream in("mem.txt");
    int i;
    sc_lv<WORD_LENGTH> data;

    for (i = 0; i<addrSpace; i++) {
        in >> data;
        mem[i] = data;
    }
}

template<int ADDRESS, int WORD_LENGTH>
void RegisterFile<ADDRESS, WORD_LENGTH>::memwrite() {
	sc_uint<ADDRESS> ad;
    while (true)
    {
        if (clk == '1') {
                if (write == '1') {
                    ad = Addr; 
                    mem[ad] = Din;
                }
        }
        wait();
    }
}

template<int ADDRESS, int WORD_LENGTH>
void RegisterFile<ADDRESS, WORD_LENGTH>::resetting() {
	sc_uint<ADDRESS> ad;
    while (true)
    {
        if (rst == '1') {
            for (int i = 0; i<addrSpace; i++)
                mem[i] = 0;
        }
        wait();
    }
}

template<int ADDRESS, int WORD_LENGTH>
void RegisterFile<ADDRESS, WORD_LENGTH>::memread() {
	sc_uint<ADDRESS> ad;
    if (read == '1') {
        ad = Addr; 
        Dout = mem[ad];
    }
}

template<int ADDRESS, int WORD_LENGTH>
void RegisterFile<ADDRESS, WORD_LENGTH>::memdump() {
	int i;
	sc_lv<WORD_LENGTH> data;
	ofstream out("out.txt");
	for (i = 0; i<addrSpace; i++) {
		data = mem[i];
		out << data << "\n";
	}
}

#endif