#include "bigint.h"


BigInt::BigInt()
{
    sign = 1;
}


BigInt::BigInt(int num)
{
    if (num >= 0)
    {
        this->sign = 1;
    }
    else
    {
        this->sign = -1;
        num *= -1;
    }

    this->number.push_back(num % BigInt::base);

    num /= BigInt::base;

    if (num != 0)
        this->number.push_back(num);
}


void BigInt::RemoveZero()
{
    while (this->number.size() > 1 && this->number.back() == 0)
    {
        this->number.pop_back();
    }

    if (this->number.size() == 1 && this->number[0] == 0) this->sign = 1;
}


void BigInt::ShiftRight()
{
    if (this->number.size() == 0)
    {
        this->number.push_back(0);
        return;
    }

    this->number.push_back(this->number[this->number.size() - 1]);

    for (int i = this->number.size() - 2; i > 0; --i)
    {
        this->number[i] = this->number[i - 1];
    }

    this->number[0] = 0;
}



void BigInt::ReadFromFile(const char* fileName)
{
    ifstream ifst(fileName);
    string str;
    getline(ifst, str);
    StringToInt(str);
}


void BigInt::WriteToFile(const char* fileName)
{
    ofstream ofst(fileName);

    if (this->sign == -1)
    {
        ofst << "-";
    }

    ofst << number[number.size() - 1];

    for (int i = number.size() - 2; i >= 0; i--)
    {
        if (number[i] < (BigInt::base / 10))
        {
            int count = 0;
            int buf = number[i];

            if (number[i] == 0) count += 1;

            while (buf){
                buf /= 10;
                count++;
            }
            for (int j = 0; j < (BigInt::baseLen - count); j++)
            {
                ofst << 0;
            }
        }
        ofst << number[i];
    }
}


void BigInt::PrintNumber()
{
    if (this->sign == -1)
    {
        cout << "-";
    }

    if (this->number.size() != 0)
    {
        cout << number[number.size() - 1];

        for (int i = number.size() - 2; i >= 0; i--)
        {
            if (number[i] < (BigInt::base / 10))
            {
                int count = 0;
                int buf = number[i];

                if (number[i] == 0) count += 1;

                while (buf){
                    buf /= 10;
                    count++;
                }

                for (int j = 0; j < (BigInt::baseLen - count); j++)
                {
                    cout << 0;
                }
            }
            cout << number[i];
        }
    }
    cout << endl;
}


void BigInt::StringToInt(string str)
{
    if (str[0] == '-')
    {
        str = str.substr(1);
        this->sign = -1;
    }
    else
    {
        this->sign = 1;
    }

    for (int i = str.length(); i > 0; i -= BigInt::baseLen)
    {
        if (i < 9)
            this->number.push_back(atoi(str.substr(0, i).c_str()));
        else
            this->number.push_back(atoi(str.substr(i - BigInt::baseLen, BigInt::baseLen).c_str()));
    }

    this->RemoveZero();
}


BigInt BigInt::PowMod(BigInt a, BigInt k, BigInt n)
{
    BigInt res(1);

    while (k != 0)
    {
        if ((k % 2) == 1)
        {
            res = (res * a) % n;
        }

        a = (a * a) % n;
        k /= 2;
    }

    return res;
}


BigInt BigInt::abs() const
{
    BigInt res = *this;
    res.sign *= res.sign;
    return res;
}


BigInt BigInt::operator-() const
{
    BigInt res = *this;
    res.sign *= -1;
    return res;
}


BigInt BigInt::operator +(const BigInt& right) const
{
    BigInt left = *this;

    if (left.sign != right.sign)
    {
        return left - (-right);
    }

    BigInt res = right;

    int carry = 0;
    int maxLen = (left.number.size() >= right.number.size() ? left.number.size() : right.number.size());

    for (int i = 0; i < maxLen || carry; ++i)
    {
        if (i == res.number.size())
        {
            res.number.push_back(0);
        }

        res.number[i] += carry + (i < left.number.size() ? left.number[i] : 0);

        carry = res.number[i] >= BigInt::base;

        if (carry)
        {
            res.number[i] -= BigInt::base;
        }
    }
    return res;
}


BigInt BigInt::operator +=(const BigInt& right) {
    return *this = *this + right;
}


BigInt BigInt::operator -(const BigInt& right) const
{
    BigInt left = *this;
    if (left.sign != right.sign)
    {
        return left - (-right);
    }

    if (this->abs() >= right.abs())
    {
        BigInt res = left;
        int carry = 0;

        for (int i = 0; i < right.number.size() || carry; ++i)
        {
            res.number[i] -= carry + (i < right.number.size() ? right.number[i] : 0);
            carry = res.number[i] < 0;

            if (carry)
            {
                res.number[i] += BigInt::base;
            }
        }
        res.RemoveZero();
        return res;
    }
    else
    {
        return -(right - left);
    }
}


BigInt BigInt::operator -=(const BigInt& right)
{
    return *this = (*this - right);
}


BigInt BigInt::operator *(const BigInt& right) const
{
    BigInt left = *this;
    BigInt res;
    res.sign = left.sign * right.sign;

    res.number.resize(right.number.size() + left.number.size() + 1);

    for (int i = 0; i < left.number.size(); i++)
    {
        for (int j = 0, carry = 0; j < right.number.size() || carry; j++)
        {
            long long buf = res.number[i + j] + left.number[i] * 1ll * (j < right.number.size() ? right.number[j] : 0) + carry;
            res.number[i + j] = (int)(buf % BigInt::base);
            carry = (int)(buf / BigInt::base);
        }
    }
    res.RemoveZero();
    return res;
}


BigInt BigInt::operator *=(const BigInt& right)
{
    return *this = (*this * right);
}


BigInt BigInt::operator /(const BigInt& right) const
{
    BigInt left = *this;
    BigInt b = right, result, current;
    result.number.resize(left.number.size());

    for (long long i = (left.number.size() - 1); i >= 0; --i)
    {
        current.ShiftRight();
        current.number[0] = left.number[i];
        current.RemoveZero();

        int x = 0, l = 0, r = BigInt::base;

        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInt t = b * m;
            if (t <= current)
            {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result.number[i] = x;
        current = current - b * x;
    }

    result.sign = this->sign * right.sign;
    result.RemoveZero();

    return result;
}


BigInt BigInt::operator /=(const BigInt& right)
{
    return *this = (*this / right);
}


BigInt BigInt::operator %(const BigInt& right) const
{
    BigInt left = *this;
    BigInt result = left - (left / right) * right;

    if (result.sign == -1)
        result += right;

    return result;
}



BigInt BigInt::operator %=(const BigInt& right)
{
    return *this = (*this % right);
}


BigInt BigInt::operator ^(BigInt& right) const
{
    BigInt left = *this;
    BigInt res(1);

    while (right != 0)
    {
        if ((right % 2) == 1)
        {
            res *= left;
        }

        left *= left;
        right /= 2;
    }

    return res;
}


BigInt BigInt::operator ^=(BigInt& right)
{
    return *this = (*this ^ right);
}


bool BigInt::operator<(const BigInt &r) const
{
    if (this->sign != r.sign)
        return this->sign < r.sign;
    if (this->number.size() != r.number.size())
        return this->number.size() * this->sign < r.number.size() * r.sign;
    for (int i = this->number.size() - 1; i >= 0; i--)
        if (this->number[i] != r.number[i])
            return number[i] * this->sign < r.number[i] * this->sign;
    return false;
}


bool BigInt::operator>(const BigInt &r) const
{
    return r < *this;
}


bool BigInt::operator<=(const BigInt &r) const
{
    return !(r < *this);
}


bool BigInt::operator>=(const BigInt &r) const
{
    return !(*this < r);
}


bool BigInt::operator==(const BigInt &r) const
{
    return !(*this < r) && !(r < *this);
}


bool BigInt::operator!=(const BigInt &r) const
{
    return *this < r || r < *this;
}

