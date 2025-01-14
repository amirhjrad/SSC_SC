#ifndef BUSES_H
#define BUSES_H
#include <iostream>
#include <math.h>
#include "gates.h"

using namespace std;

#define MIN(a,b) ((a<b)?a:b);
#define MAX(a,b) ((a>b)?a:b);

class bus{
	string v;
public:
	bus() { v.resize(1, 'X'); }
	bus(int SIZE) { v.resize(SIZE, 'X'); }
	bus(int SIZE, char c) { v.resize(SIZE, c); }
	bus(const string s) { v = s; }
	bus(const char* c) { v = c; }
	bus(const bus& a) { v = a.v; } // Copy constructor for =
	void resize(int SIZE, char c) { v.resize(SIZE, c); }
	bus range(int i1, int i2)
	{
		int left = MAX(i1, i2);
		int rite = MIN(i1, i2);
		bus slice(left - rite + 1, 'X');
		int vSize = v.length();
		slice.v = v.substr(vSize - 1 - left, left - rite + 1);
		return slice;
	}

	bus at(int i)
	{
		bus bit(1, 'X');
		int vSize = v.length();
		bit.v = v.at(vSize -1 - i);
		return bit;
	}

	char operator[](int i) const {
		return v[v.length()-i-1];
	}

	char& operator[](int i) {
		return v[v.length()-i-1];
	}

	int length()
	{
		return v.length();
	}

	void fill(char c)
	{
		v.assign(v.length(), c);
	}

	friend bus operator& (bus a, bus b) // Friend, because 2 arguments
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		int rSize;
		if (bSize == 1) rSize = aSize; else rSize = MIN(aSize, bSize);
		bus r(rSize, 'X');
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			if (bSize == 1) r.v[i] = AND(a.v.at(i), b.v.at(0));
			else r.v[i] = AND(a.v.at(i), b.v.at(i));
		}
		return r;
	}

	friend bus operator| (bus a, bus b)
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		int rSize;
		if (bSize == 1) rSize = aSize; else rSize = MIN(aSize, bSize);
		bus r(rSize, 'X');
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			if (bSize == 1) r.v[i] = OR(a.v.at(i), b.v.at(0));
			else r.v[i] = OR(a.v.at(i), b.v.at(i));
		}
		return r;
	}

	friend bus operator^ (bus a, bus b)
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		int rSize;
		if (bSize == 1) rSize = aSize; else rSize = MIN(aSize, bSize);
		bus r(rSize, 'X');
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			if (bSize == 1) r.v[i] = XOR(a.v.at(i), b.v.at(0));
			else r.v[i] = XOR(a.v.at(i), b.v.at(i));
		}
		return r;
	}

	friend bus operator~ (bus a)
	{
		int aSize = a.v.length();
		int rSize = aSize;
		bus r(rSize, 'X');
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			r.v[i] = not(a.v.at(i));
		}
		return r;
	}

	friend bus operator+ (const bus a, const bus b)
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		int rSize;
		int min = MIN(aSize, bSize);
		if (bSize == 1) rSize = aSize; else rSize = min + 1;
		bus r(rSize, 'X');

		char ci('0');
		char co('0'), sum('0');
		if (bSize == 1){
			for (int i = rSize - 1; i >= 0; i--) {
				if (i == rSize - 1)	fullAdder(a.v.at(i), b.v.at(0), ci, co, sum);
				else fullAdder(a.v.at(i), '0', ci, co, sum);
				ci = co;
				r.v[i] = sum;
			}
		}
		else {
			for (int i = rSize - 1; i >= 1; i--) {
				fullAdder(a.v.at(i - 1), b.v.at(i - 1), ci, co, sum);
				ci = co;
				r.v[i] = sum;
			}
			r.v[0] = co;
		}
		return r;
	}

	friend bus operator, (bus a, bus b)
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		int rSize = aSize + bSize;
		bus r(rSize, 'X');
		int i;
		for (i = bSize - 1; i >= 0; i--) {
			r.v[aSize + i] = b.v.at(i);
		}
		for (i = aSize - 1; i >= 0; i--) {
			r.v[i] = a.v.at(i);
		}
		return r;
	}

	friend bool operator== (bus a, const bus b)
	{
		return (a.v == b.v);
	}
	friend bool operator> (bus a, const bus b) // Assume same size
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		bool r = false;
		int i = 0;
		do{
			if ((a.v[i] == '1') && (b.v[i] == '0')){
				r = true; break;
			}
			else if ((a.v[i] == '0') && (b.v[i] == '1')){
				r = false; break;
			}
		} while (++i < aSize);
		return r;
	}
	friend bool operator< (bus a, const bus b) // Assume same size
	{
		int aSize = a.v.length();
		int bSize = b.v.length();
		bool r = false;
		int i = 0;
		do{
			if ((a.v[i] == '0') && (b.v[i] == '1')){
				r = true; break;
			}
			else if ((a.v[i] == '1') && (b.v[i] == '0')){
				r = false; break;
			}
		} while (++i < aSize);
		return r;
	}

	bool operator&& (bus b) // Must be member function for second arg
	{
		int aSize = this->v.length();
		int bSize = b.v.length();
		int rSize;
		if (bSize == 1) rSize = aSize; else rSize = MIN(aSize, bSize);
		bool r = false;
		char c = '0';
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			if (bSize == 1) c = AND(this->v.at(i), b.v.at(0));
			else c = AND(this->v.at(i), b.v.at(i));
			if (c == '1') r = true;
		}
		return r;
	}

	bool operator|| (bus b)
	{
		int aSize = this->v.length();
		int bSize = b.v.length();
		int rSize;
		if (bSize == 1) rSize = aSize; else rSize = MIN(aSize, bSize);
		bool r = false;
		char c = '0';
		int i;
		for (i = rSize - 1; i >= 0; i--) {
			if (bSize == 1) c = OR(this->v.at(i), b.v.at(0));
			else c = OR(this->v.at(i), b.v.at(i));
			if (c == '1') r = true;
		}
		return r;
	}

	friend ostream& operator<<(ostream& out, const bus a)
	{
		return(out << a.v);
	}

	friend istream& operator>>(istream& in, bus& a)
	{
		return(in >> a.v);
	}

	int ival ()
	{
		int aSize = v.length();
		int ia=0;
		for (int i = aSize - 1; i >= 0; i--) {
			if (v.at(i) == '1') ia = ia + int(pow(2.0, (aSize - 1 - i) ));
		}
		return ia;
	}
};

#endif