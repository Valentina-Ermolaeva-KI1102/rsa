#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include "hash.h"

unsigned int F(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) | ((~x) & z));
}
unsigned int G(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & z) | (y & (~z)));
}
unsigned int H(unsigned int x, unsigned int y, unsigned int z)
{
	return (x ^ y ^ z);
}
unsigned int I(unsigned int x, unsigned int y, unsigned int z)
{
	return (y ^ (x | (~z)));
}
unsigned int Cyclic_shift(unsigned int x, int y)
{
	return x << y | x >> (32-y);
}
unsigned int* md5(std::ifstream *in)
{
	int lenght, size = 64, rest, i;
	in->seekg(0, std::ios::end);
	lenght = in->tellg();
	in->seekg(0, std::ios::beg);
	bool end = false;
	rest = lenght % 64;
	unsigned char *msg_for_hash = new unsigned char[size];
	char buf;
	unsigned int MD5[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476}, AA, BB, CC, DD;
	unsigned int T[64];
	for(int l = 0; l < size; l++)
		T[l]= pow(2,32)*fabs(sin(l + 1));
	unsigned int *X=(unsigned int*)(msg_for_hash);
	while(!in->eof() && !end)
	{
		for(i = 0; i < size; i++)
		{
			in->get(buf);
			if(in->eof())
			{
				if(i < 55)
				{
					msg_for_hash[i] = 0x80;
					for(i++; i < 56; i++)
						msg_for_hash[i] = 0;
					long long bit_length = (unsigned int)(lenght)*8; //����� ��������� � �����.
					for(int i = 0; i < 8; i++) //��������� 8 ����
						msg_for_hash[size - 8 + i] = (unsigned char)(bit_length >> i * 8);
					break;
				}
				else
				{
					msg_for_hash[i] = 0x80;
					for(i++; i < size; i++)
						msg_for_hash[i] = 0;
					end = true;
					break;
				}
			}
			msg_for_hash[i] = buf;
		}
		if(end)
		{
			for(i++; i < 56; i++)
				msg_for_hash[i] = 0;
			long long bit_length = (unsigned int)(lenght)*8; //����� ��������� � �����.
			for(int i = 0; i < 8; i++) //��������� 8 ����
				msg_for_hash[size - 8 + i] = (unsigned char)(bit_length >> i * 8);
			end = false;
		}
		for (int i = 0; i < size/16; i++)
		{
			AA = MD5[0];
			BB = MD5[1];
			CC = MD5[2];
			DD = MD5[3];
			//round 1
			for(int j = 0; j < 4; j++)
			{
				MD5[0] = MD5[1] + Cyclic_shift((MD5[0] + F(MD5[1],MD5[2],MD5[3]) + X[i + (j * 4) % 16] + T[j * 4]), 7);
				MD5[3] = MD5[0] + Cyclic_shift((MD5[3] + F(MD5[0],MD5[1],MD5[2]) + X[i + (j * 4 + 1) % 16] + T[j * 4 + 1]), 12);
				MD5[2] = MD5[3] + Cyclic_shift((MD5[2] + F(MD5[3],MD5[0],MD5[1]) + X[i + (j * 4 + 2) % 16] + T[j * 4 + 2]), 17);
				MD5[1] = MD5[2] + Cyclic_shift((MD5[1] + F(MD5[2],MD5[3],MD5[0]) + X[i + (j * 4 + 3) % 16] + T[j * 4 + 3]), 22);
			}
			//round 2
			for(int j = 0; j < 4; j++)
			{
				MD5[0] = MD5[1] + Cyclic_shift((MD5[0] + G(MD5[1],MD5[2],MD5[3]) + X[i + (j * 4 + 1) % 16 ] + T[j * 4 + 16]), 5);
				MD5[3] = MD5[0] + Cyclic_shift((MD5[3] + G(MD5[0],MD5[1],MD5[2]) + X[i + (j * 4 + 6) % 16] + T[j * 4 + 17]), 9);
				MD5[2] = MD5[3] + Cyclic_shift((MD5[2] + G(MD5[3],MD5[0],MD5[1]) + X[i + (j * 4 + 11) % 16] + T[j * 4 + 18]), 14);
				MD5[1] = MD5[2] + Cyclic_shift((MD5[1] + G(MD5[2],MD5[3],MD5[0]) + X[i + (j * 4) % 16] + T[j * 4 + 19]), 20);
			}
			//round 3
			for(int j = 0; j < 4; j++)
			{
				MD5[0] = MD5[1] + Cyclic_shift((MD5[0] + H(MD5[1],MD5[2],MD5[3]) + X[i + (j * 4 + 5) % 16] + T[j * 4 + 32]), 4);
				MD5[3] = MD5[0] + Cyclic_shift((MD5[3] + H(MD5[0],MD5[1],MD5[2]) + X[i + (j * 4 + 8) % 16] + T[j * 4 + 33]), 11);
				MD5[2] = MD5[3] + Cyclic_shift((MD5[2] + H(MD5[3],MD5[0],MD5[1]) + X[i + (j * 4 + 11) % 16] + T[j * 4 + 34]), 16);
				MD5[1] = MD5[2] + Cyclic_shift((MD5[1] + H(MD5[2],MD5[3],MD5[0]) + X[i + (j * 4 + 14) % 16] + T[j * 4 + 35]), 23);
			}
			//round 4
			for(int j = 0; j < 4; j++)
			{
				MD5[0] = MD5[1] + Cyclic_shift((MD5[0] + I(MD5[1],MD5[2],MD5[3]) + X[i + (j * 4) % 16] + T[j * 4 + 48]), 6);
				MD5[3] = MD5[0] + Cyclic_shift((MD5[3] + I(MD5[0],MD5[1],MD5[2]) + X[i + (j * 4 + 7) % 16] + T[j * 4 + 49]), 10);
				MD5[2] = MD5[3] + Cyclic_shift((MD5[2] + I(MD5[3],MD5[0],MD5[1]) + X[i + (j * 4 + 14) % 16] + T[j * 4 + 50]), 15);
				MD5[1] = MD5[2] + Cyclic_shift((MD5[1] + I(MD5[2],MD5[3],MD5[0]) + X[i + (j * 4 + 5) % 16] + T[j * 4 + 51]), 21);
			}
			// recording result of rounds;
			MD5[0] += AA;
			MD5[1] += BB;
			MD5[2] += CC;
			MD5[3] += DD;
		}
	}
	return MD5;
}
