#include <fstream>
#include <iostream>
#include <malloc.h>
#include <cstring>
#include <string.h>
#include <stdexcept>
class BigInt
{
    public:
char* Integer;
bool Sign; //false - '+'; true - '-'
int size;
void Update(char *integer);
public:
BigInt(char *integer);
BigInt(char *FName, bool Binary);
BigInt();
BigInt(int integer);
BigInt(BigInt *integer);
BigInt* BinaryRead(char *FName);
BigInt* TextRead(char *FName);
void BinaryWrite(char *FName);
void TextWrite(char *FName);
friend void BinaryWrite(BigInt *integer, char *FName);
friend void TextWrite(BigInt *integer, char *FName);
//
BigInt* Summary(BigInt* integer);
BigInt* Subtraction(BigInt* integer);
BigInt* Multiplication(BigInt* integer);
BigInt* Degreed(BigInt* integer);
BigInt* Division(BigInt* integer);
BigInt* Modulation(BigInt* integer);
BigInt* DegreeToTen(BigInt* integer);
void SummaryS(BigInt* integer);
void SubtractionS(BigInt* integer);
void MultiplicationS(BigInt* integer);
void DegreedS(BigInt *integer);
void DivisionS(BigInt* integer);
void ModulationS(BigInt* integer);
void Clear();
char* Print();
void hello();
//унарный =
const BigInt & operator=(const BigInt& integer);
//бинарный +
BigInt& operator+(const BigInt& integer);
//унарный -
BigInt& operator-();
//бинарный -
BigInt& operator-(const BigInt& integer);
//префиксна инкремент
BigInt& operator++(); // косяк SumS
// потфиксная
BigInt& operator++(int);
//префиксна декремент
BigInt& operator--();
// потфиксная
BigInt& operator--(int);
//бинарный +=
BigInt& operator+=(const BigInt& integer);
//бинарный -=
BigInt& operator-=(const BigInt& integer);
//бинарный *
BigInt& operator*(const BigInt& integer);
//бинарный *=
BigInt& operator*=(const BigInt& integer);
//бинарный /
BigInt& operator/(const BigInt& integer);
//бинарный /=
BigInt& operator/=(const BigInt& integer);
//бинарный %
BigInt& operator%(const BigInt& integer);
//бинарный %=
BigInt& operator%=(const BigInt& integer);
//бинарный ^
BigInt& operator^(const BigInt& integer);
//бинарный ^=
BigInt& operator^=(const BigInt& integer);
//бинарный ==
const bool operator==(const BigInt& integer);
//бинарный !=
const bool operator!=(const BigInt& integer);
//бинарный <
const bool operator<(const BigInt& integer);
//бинарный >
const bool operator>(const BigInt& integer);
//бинарный <=
const bool operator<=(const BigInt& integer);
//бинарный >=
const bool operator>=(const BigInt& integer);
friend std::istream &operator>>(std::istream& _in, BigInt& integer);
friend std::ostream &operator<<(std::ostream& _out, BigInt& integer);
~BigInt();
};
void BinaryWrite(BigInt *integer, char *FName);
void TextWrite(BigInt *integer, char *FName);
int atoi(char ch);
char itoa(int i);
char* shiftRight(char *integer, int p);
char* divisionInTwo(char *integer);
