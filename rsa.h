//#pragma comment(lib, "BigIntDll.lib")
#include "bigInt.h"

char* getSimpleNum(std::ifstream &ifst);

BigInt Func_El(BigInt Fi, BigInt &rez);

char* intToChar(int a);

int charToInt(char *a);

int Space(std::ifstream &ifst);

void GeneratedKey(char *p_fname, char *q_fname, char *e_fname, char *name);

void EncodingRSA(char *M_fname, char *n_fname, char *e_fname, char *d_fname);

void EDSRSA(char *M_fname, char *n_fname, char *e_fname, char *d_fname);

void EncodingEDSRSA(char *M_fname, char *nA_fname, char *eA_fname, char *dA_fname, char *nB_fname, char *eB_fname, char *dB_fname);
