#include <fstream>
#include <iostream>
#include "rsa.h"

//5761456
int main(int argc, char *argv[])
{
    int menu = 0;
	char *a_P = new char[24], *a_Q = new char[24], *a_E = new char[24];
	char *b_P = new char[24], *b_Q = new char[24], *b_E = new char[24];
    //if (argc > 6)
    //{
        /*strcpy(a_P, argv[1]);
		strcpy(a_Q, argv[2]);
		strcpy(a_E, argv[3]);
        strcpy(b_P, argv[4]);
		strcpy(b_Q, argv[5]);
        strcpy(b_E, argv[6]);*/
        strcpy(a_P, "AP.txt");
        strcpy(a_Q, "AQ.txt");
        strcpy(a_E, "AE.txt");
        strcpy(b_P, "BP.txt");
        strcpy(b_Q, "BQ.txt");
        strcpy(b_E, "BE.txt");
        std::cout<<"Please choose:\n1 - EncodingRSA\n2 - EDSRSA\n3 - EncodingEDSRSA."<<std::endl;
        std::cin>>menu;
        GeneratedKey(a_P, a_Q, a_E, "A");
        GeneratedKey(b_P, b_Q, b_E, "B");
        switch(menu)
		{
		case 1:
			EncodingRSA("in.txt", "AN.txt", a_E, "AD.txt");
			break;
		case 2:
			EDSRSA("in.txt", "AN.txt", a_E, "AD.txt");
			break;
		case 3:
			EncodingEDSRSA("in.txt", "AN.txt", a_E, "AD.txt", "BN.txt", b_E, "BD.txt");
			break;
		}
    /*}
	else if (argc == 2)
	{
		if(!strcmp("-h", argv[1]) || !strcmp("-H", argv[1]) || !strcmp("-help", argv[1]))
		{
			std::cout<<"This program implements RSA in three modes: encoding, EDS and EDS with encoding\nExample of using:\n rsa.exe file_P_for_A file_Q_for_A file_E_for_A file_P_for_B file_Q_for_B file_E_for_B";
			return 1;
		}
	}
	else
	{
		std::cout<<"Not enough input data\n";
    }*/
	std::cin>>menu;
	return 0;
}

