#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#pragma once
using namespace std;

class BigInt
{
    static const int base = 100000000;
    static const int baseLen = 8;

    vector<int> number;
    int sign;

    void RemoveZero();
    void ShiftRight();
public:
    BigInt();
    BigInt(int num);

    void ReadFromFile(const char* fileName);
    void WriteToFile(const char* fileName);
    void StringToInt(string str);
    void PrintNumber();

    BigInt PowMod(BigInt a, BigInt k, BigInt n);

    BigInt abs() const;
    BigInt operator-() const;

    BigInt operator +(const BigInt& right) const;
    BigInt operator -(const BigInt& right) const;
    BigInt operator *(const BigInt& right) const;
    BigInt operator /(const BigInt& right) const;
    BigInt operator %(const BigInt& right) const;
    BigInt operator ^(BigInt& right) const;

    BigInt operator +=(const BigInt& right);
    BigInt operator -=(const BigInt& right);
    BigInt operator *=(const BigInt& right);
    BigInt operator /=(const BigInt& right);
    BigInt operator %=(const BigInt& right);
    BigInt operator ^=(BigInt& right);

    bool operator<(const BigInt &r) const;
    bool operator>(const BigInt &r) const;
    bool operator<=(const BigInt &r) const;
    bool operator>=(const BigInt &r) const;
    bool operator==(const BigInt &r) const;
    bool operator!=(const BigInt &r) const;
};

