#include "bigInt.h"
const BigInt& BigInt::operator=(const BigInt& integer)
{
    Update(integer.Integer);
    Sign = integer.Sign;
    size = integer.size;
    return *this;
}
BigInt& BigInt::operator+(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    return *rez->Summary(buf);
}
BigInt& BigInt::operator-(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    return *rez->Subtraction(buf);
}
BigInt& BigInt::operator-()
{
    this->Sign = !this->Sign;
    return *this;
}
BigInt& BigInt::operator++(int)
{
    BigInt one = "1", *Oldvar;
    Oldvar = new BigInt(this);
    this->SummaryS(&one);
    return *Oldvar;
}
BigInt& BigInt::operator++()
{
    BigInt one = "1";
    this->SummaryS(&one);
    return *this;
}
BigInt& BigInt::operator--(int)
{
    BigInt one = "1", *Oldvar;
    Oldvar = new BigInt(this);
    this->SubtractionS(&one);
    return *Oldvar;
}
BigInt& BigInt::operator--()
{
    BigInt one = "1";
    this->SubtractionS(&one);
    return *this;
}
BigInt& BigInt::operator+=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->SummaryS(buf);
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->SubtractionS(buf);
    return *this;
}
BigInt& BigInt::operator*(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    rez->MultiplicationS(buf);
    return *rez;
}
BigInt& BigInt::operator*=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->MultiplicationS(buf);
    return *this;
}
BigInt& BigInt::operator/(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    rez->DivisionS(buf);
    return *rez;
}
BigInt& BigInt::operator/=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->DivisionS(buf);
    return *this;
}
BigInt& BigInt::operator%(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    rez->ModulationS(buf);
    return *rez;
}
BigInt& BigInt::operator%=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->ModulationS(buf);
    return *this;
}
BigInt& BigInt::operator^(const BigInt& integer)
{
    BigInt *rez = new BigInt(this);
    BigInt *buf = new BigInt(integer);
    rez->DegreedS(buf);
    return *rez;
}
BigInt& BigInt::operator^=(const BigInt& integer)
{
    BigInt *buf = new BigInt(integer);
    this->DegreedS(buf);
    return *this;
}
const bool BigInt::operator==(const BigInt& integer)
{
    if (Sign == integer.Sign) // знак
        if (size == integer.size) // кол-во разрядов
        {
            int i = 0, j = 0;;
            while(true)
            {
                if(i == size)
                    break;
                if(Integer[i] > integer.Integer[j])
                    return false;
                else if(Integer[i] < integer.Integer[j])
                    return false;
                else
                {
                    i++; j++;
                }
            }
            return true;
        }
    return false;
}
const bool BigInt::operator!=(const BigInt& integer)
{
    if (Sign == integer.Sign) // знак
        if (size == integer.size) // кол-во разрядов
        {
            int i = 0, j = 0;;
            while(true)
            {
                if(i == size)
                    break;
                if(Integer[i] > integer.Integer[j])
                    return true;
                else if(Integer[i] < integer.Integer[j])
                    return true;
                else
                {
                    i++; j++;
                }
            }
            return false;
        }
    return true;
}
const bool BigInt::operator<(const BigInt& integer) //-149 <-127 но не работает...
{
    if(Sign == true && integer.Sign == false)
        return true;
    if(Sign != integer.Sign)
        return false;
    if(size > integer.size) // кол-во разрядов
        return Sign;
    if(size < integer.size)
        return !Sign;
    int i = 0, j = 0;;
    while(true)
    {
        if(i == size)
            break;
        if(Integer[i] > integer.Integer[j])
            return Sign;
        else if(Integer[i] < integer.Integer[j])
            return !Sign;
        else
        {
            i++; j++;
        }
    }
    return false;
}
const bool BigInt::operator>(const BigInt& integer)
{
    if(Sign == false && integer.Sign == true)
        return true;
    if(Sign != integer.Sign)
        return false;
    if(size > integer.size) // кол-во разрядов
        return !Sign;
    if(size < integer.size)
        return Sign;
    int i = 0, j = 0;;
    while(true)
    {
        if(i == size)
            break;
        if(Integer[i] > integer.Integer[j])
            return !Sign;
        else if(Integer[i] < integer.Integer[j])
            return Sign;
        else
        {
            i++; j++;
        }
    }
    return false;
}
const bool BigInt::operator<=(const BigInt& integer)
{
    if(Sign == true && integer.Sign == false)
        return true;
    if(Sign != integer.Sign)
        return false;
    if(size > integer.size) // кол-во разрядов
        return Sign;
    if(size < integer.size)
        return !Sign;
    int i = 0, j = 0;;
    while(true)
    {
        if(i == size)
            break;
        if(Integer[i] > integer.Integer[j])
        return Sign;
        else if(Integer[i] < integer.Integer[j])
        return !Sign;
        else
        {
            i++; j++;
        }
    }
        return true;
}
const bool BigInt::operator>=(const BigInt& integer)
{
    if(Sign == false && integer.Sign == true)
        return true;
    if(Sign != integer.Sign)
        return false;
    if(size > integer.size) // кол-во разрядов
        return !Sign;
    if(size < integer.size)
        return Sign;
    int i = 0, j = 0;;
    while(true)
    {
        if(i == size)
            break;
        if(Integer[i] > integer.Integer[j])
            return !Sign;
        else if(Integer[i] < integer.Integer[j])
            return Sign;
        else
        {
        i++; j++;
        }
    }
    return true;
}
std::istream &operator>>(std::istream &_in, BigInt &integer)
{
    char buf, *buffer;
    integer.size = 0;
    _in.get(buf);
    if(buf == '-')
    {
        integer.Sign = true;
        _in.get(buf);
    }
    else if(buf == '+')
    {
        integer.Sign = false;
        _in.get(buf);
    }
    else if(isdigit(buf))
    integer.Sign = false;
    else
    {
        throw std::invalid_argument("Error input stream.\n");
        return _in;
    }
    int i = 0;
    while(buf == '0' && isdigit(buf))
    {
        _in.get(buf);
    }
    size_t a = 0, b, c, d;
    integer.Integer = (char*)malloc(a);
    while(!_in.eof() && isdigit(buf))
    {
        integer.size++;
        b = integer.size + 1; c = integer.size - 1; d = integer.size;
        buffer = (char*)malloc(b);
        memcpy((void*)buffer, (void*)integer.Integer, c);
        buffer[i] = buf;
        free(integer.Integer);
        integer.Integer = (char*)malloc(b);
        memcpy((void*)integer.Integer, (void*)buffer, d);
        free((void*)buffer);
        i++;
        _in.get(buf);
    }
    integer.Integer[i] = 0;
    return _in;
}
std::ostream &operator<<(std::ostream &_out, BigInt &integer)
{
    if(!&integer)
    return _out;
    if(!integer.Integer || !integer.size)
    {
    _out<<'0';
    return _out;
    }
    if(integer.Sign)
    _out<<'-';
    for(int i = 0; i < integer.size; i++)
    _out<<integer.Integer[i];
    return _out;
}
