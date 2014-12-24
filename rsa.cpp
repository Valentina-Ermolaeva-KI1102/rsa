#include <fstream>
#include "rsa.h"
#include "hash.h"
#include "generationSimpleFile.h"
#define		RNet		30

char* getSimpleNum(std::ifstream &ifst)
{
	char *simple_num = new char[10];
	ifst>>simple_num;
	return simple_num;
}

char* intToChar(int a)
{
    char *num = new char[10];
    if(!a) return "0";
    int max_d = 0, k = a, j = 0, i = 0, p = 1;
    while(k)
    {
        max_d++;
        k /= 10;
    }
    do
    {
        for(j = 1; j < max_d; j++)
            p *= 10;
        k = a / p;
        a %= p;
        p = 1;
        num[i++] = itoa(k);
        max_d--;
    }while(max_d);
    //num = itoa(a, num, 10);
    num[i] = '\0';
    return num;
}

int charToInt(char *a)
{
    int num = 0;
    for(int i = 0; i < strlen(a); i++)
    {
        num *= 10;
        num += atoi(a[i]);
    }
    //num = atoi(a);
    return num;
}

int Space(std::ifstream &ifst)
{
	char c;
	int  amount = 0;
	while(!ifst.eof())
	{
		ifst.get(c);
		if(c == ' ')
			amount++;
	}
	return amount;
}

void GeneratedKey(char *p_fname, char *q_fname, char *e_fname, char *name)
{
    BigInt P(p_fname, false), Q(q_fname, false), E(e_fname, false);
    BigInt N = P * Q, Fi, FiEl("1"), D("1");
    Fi = (P - BigInt("1")) * (Q - BigInt("1"));
	int amount = 5761456;
	/*std::ifstream num("simpleNum.txt");
	amount = Space(num);
	num.close();*/
	std::ifstream ifst("simpleNum.txt");
	if(!ifst)
	{
		GenetateSimpleList();
		ifst.open("simpleNum.txt");
	}
	int **degree, i;
	char *buf_ch = new char[10];
    BigInt A = BigInt(&Fi), B, buf_bi;
	degree = new int *[2];
	for(i = 0; i < 2; i ++)
		degree[i] = new int [amount];
	memset(degree[0], 0, 4 * amount);
	memset(degree[1], 0, 4 * amount);
	i = 0;
	bool end = true;
	while(end)
	{
		buf_ch = getSimpleNum(ifst);
        if((A % BigInt(buf_ch)) == BigInt("0"))
		{
            A /= BigInt(buf_ch);
			degree[0][i] = charToInt(buf_ch);
			degree[1][i]++;
			i = 0;
			ifst.seekg (0, ifst.beg);
		}
		else
			i++;
        if(A == BigInt("1"))
			end = false;
	}
	ifst.close();
	for(i = 0; i < amount; i++)
	{
		if(degree[0][i] != 0)
		{
            A = B = BigInt(intToChar(degree[0][i]));
            A ^= BigInt(intToChar(degree[1][i]));
            B ^= BigInt(intToChar(degree[1][i] - 1));
			buf_bi = A - B;
			FiEl *= buf_bi;
		}
	}
	FiEl--;
    BigInt DegreeNet[RNet];
	DegreeNet[0] = D * E;
	DegreeNet[0] %= Fi;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= Fi;
	}
    BigInt degreeNum[RNet];
    degreeNum[0] = BigInt("1");
	for(int i = 1; i < RNet; i++)
        degreeNum[i] = degreeNum[i-1] * BigInt("2");
    BigInt I("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(FiEl >= I + degreeNum[j])
		{
			D *= DegreeNet[j];
			D %= Fi;
			I += degreeNum[j];
		}
		else
			j--;
	}
	char fname[32];
	strcpy(fname, name);
	strcat(fname, "N.txt");
	N.TextWrite(fname);
	strcpy(fname, name);
	strcat(fname, "D.txt");
	D.TextWrite(fname);
};

void EncodingRSA(char *M_fname, char *n_fname, char *e_fname, char *d_fname)
{
	std::ifstream in(M_fname);
	int *M_hash = (int*)md5(&in), i;
    BigInt M(intToChar(M_hash[3])), N(n_fname, false), E(e_fname, false), D(d_fname, false);
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[2]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[1]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[0]));
    BigInt Code("1"), Encode("1");
    BigInt DegreeNet[RNet];
	DegreeNet[0] = M;
	DegreeNet[0] %= N;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= N;
	}
    BigInt degreeNum[RNet];
    degreeNum[0] = BigInt("1");
	for(int i = 1; i < RNet; i++)
        degreeNum[i] = degreeNum[i-1] * BigInt("2");
    BigInt I("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(E >= I + degreeNum[j])
		{
			Code *= DegreeNet[j];
			Code %= N;
			I += degreeNum[j];
		}
		else
			j--;
	}
	/////////////////////////////
	DegreeNet[0] = Code;
	DegreeNet[0] %= N;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= N;
	}
    I = BigInt("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(D >= I + degreeNum[j])
		{
			Encode *= DegreeNet[j];
			Encode %= N;
			I += degreeNum[j];
		}
		else
			j--;
	}
	/////////////////////////////
	M.TextWrite("hash.txt");
	Code.TextWrite("code.txt");
	Encode.TextWrite("encode.txt");
	if( M % N == Encode)
		std::cout<<"OK\n";
	else
		std::cout<<"NOT OK\n";
}

void EDSRSA(char *M_fname, char *n_fname, char *e_fname, char *d_fname)
{
	std::ifstream in(M_fname);
	int *M_hash = (int*)md5(&in), i;
    BigInt M(intToChar(M_hash[3])), N(n_fname, false), E(e_fname, false), D(d_fname, false);
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[2]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[1]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[0]));
    BigInt Signature("1"), Encode("1");
    BigInt DegreeNet[RNet];
	DegreeNet[0] = M;
	DegreeNet[0] %= N;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= N;
	}
    BigInt degreeNum[RNet];
    degreeNum[0] = BigInt("1");
	for(int i = 1; i < RNet; i++)
        degreeNum[i] = degreeNum[i-1] * BigInt("2");
    BigInt I("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(D >= I + degreeNum[j])
		{
			Signature *= DegreeNet[j];
			Signature %= N;
			I += degreeNum[j];
		}
		else
			j--;
	}
	/////////////////////////////
	DegreeNet[0] = Signature;
	DegreeNet[0] %= N;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= N;
	}
    I = BigInt("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(E >= I + degreeNum[j])
		{
			Encode *= DegreeNet[j];
			Encode %= N;
			I += degreeNum[j];
		}
		else
			j--;
	}
	/////////////////////////////
	M.TextWrite("hash.txt");
	Signature.TextWrite("signature.txt");
	Encode.TextWrite("encode.txt");
	if( M % N == Encode)
		std::cout<<"OK\n";
	else
		std::cout<<"NOT OK\n";
}

void EncodingEDSRSA(char *M_fname, char *nA_fname, char *eA_fname, char *dA_fname, char *nB_fname, char *eB_fname, char *dB_fname)
{
	std::ifstream in(M_fname);
	int *M_hash = (int*)md5(&in), i;
    BigInt  M(intToChar(M_hash[3])), NA(nA_fname, false), EA(eA_fname, false), DA(dA_fname, false);
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[2]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[1]));
    M *= BigInt("10000000000"); M += BigInt(intToChar(M_hash[0]));
    BigInt NB(nB_fname, false), EB(eB_fname, false), DB(dB_fname, false);
    BigInt Signature("1"), Code("1"), Encode("1"), CheckSign("1");
    BigInt DegreeNet[RNet];
	DegreeNet[0] = M;
	DegreeNet[0] %= NA;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= NA;
	}
    BigInt degreeNum[RNet];
    degreeNum[0] = BigInt("1");
	for(int i = 1; i < RNet; i++)
        degreeNum[i] = degreeNum[i-1] * BigInt("2");
    BigInt I("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(DA >= I + degreeNum[j])
		{
			Signature *= DegreeNet[j];
			Signature %= NA;
			I += degreeNum[j];
		}
		else
			j--;
	}
	//////////////////////////////
	DegreeNet[0] = Signature;
	DegreeNet[0] %= NB;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= NB;
	}
    I = BigInt("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(EB >= I + degreeNum[j])
		{
			Code *= DegreeNet[j];
			Code %= NB;
			I += degreeNum[j];
		}
		else
			j--;
	}
	//////////////////////////////
	DegreeNet[0] = Code;
	DegreeNet[0] %= NB;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= NB;
	}
    I = BigInt("0");
	for(int j = RNet-1; j >= 0;)
	{
		if(DB >= I + degreeNum[j])
		{
			Encode *= DegreeNet[j];
			Encode %= NB;
			I += degreeNum[j];
		}
		else
			j--;
	}
	//////////////////////////////
	DegreeNet[0] = Encode;
	DegreeNet[0] %= NA;
	for(i = 1; i < RNet; i++)
	{
		DegreeNet[i] = DegreeNet[i-1] * DegreeNet[i-1];
		DegreeNet[i] %= NA;
	}
    I = BigInt("0");
	for(int j = RNet - 1; j >= 0;)
	{
		if(EA >= I + degreeNum[j])
		{
			CheckSign *= DegreeNet[j];
			CheckSign %= NA;
			I += degreeNum[j];
		}
		else
			j--;
	}
	//////////////////////////////
	M.TextWrite("hash.txt");
	Code.TextWrite("code.txt");
	Encode.TextWrite("encode.txt");
	CheckSign.TextWrite("checksign.txt");
	if( M % NA == CheckSign)
		std::cout<<"OK\n";
	else
		std::cout<<"NOT OK\n";
}
