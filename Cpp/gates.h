#ifndef GATES_H
#define GATES_H

inline char AND(char a, char b)
{
    if ((a == '0') || (b == '0')) return '0';
    else if ((a == '1') && (b == '1')) return '1';
    else return 'X';
}

inline char OR(char a, char b)
{
    if ((a == '1') || (b == '1')) return '1';
    else if ((a == '0') && (b == '0')) return '0';
    else return 'X';
}

inline char NOT(char a)
{
    if (a == '1') return '0';
    else if (a == '0') return '1';
    else return 'X';
}

inline char tri(char a, char c)
{
    if (c == '1') return a;
    else return 'Z';
}

inline char resolve(char a, char b)
{
    if (a == 'Z' || a == b) return b;
    else if (b == 'Z') return a;
    else return 'X';
}

inline char XOR(char a, char b)
{
    if ((a == 'X') || (b == 'X') || (a == 'Z') || (b == 'Z')) return 'X';
    else if (a == b) return '0';
    else return '1';
}

inline void fullAdder(char a, char b, char ci, char &co, char &sum)
{
    char axb, ab, abc;

    axb = XOR(a, b);
    ab = AND(a, b);
    abc = AND(axb, ci);
    co = OR(ab, abc);
    sum = XOR(axb, ci);
}

#endif
