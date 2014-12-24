#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

unsigned int F(unsigned int x, unsigned int y, unsigned int z);

unsigned int G(unsigned int x, unsigned int y, unsigned int z);

unsigned int H(unsigned int x, unsigned int y, unsigned int z);

unsigned int I(unsigned int x, unsigned int y, unsigned int z);

unsigned int Cyclic_shift(unsigned int x, int y);

unsigned int* md5(std::ifstream *in);
