#include "generationSimpleFile.h"

int GenetateSimpleList()
{
	std::ofstream out("simpleNum.txt");
	int beg = 0, end = 100000000, c, start;
	int p;
	bool fl, pr=false;
	int mas[25]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
	int ms[8]={1, 7, 11, 13, 17, 19, 23, 29};
	
	for(int j=0; j<25; j++)
	{
		if(beg<=mas[j] && end>=mas[j])
		{
			out<<mas[j]<<" ";
			pr=true;
		}
	}
	for(start=2; 30*start+1<=end; start++)
	{
		c=30*start;
		for(p=0; p<8; p++)
		{
			if((c+ms[p])%23 && (c+ms[p])%29 && (c+ms[p])%31 && (c+ms[p])%37 && (c+ms[p])%41 && (c+ms[p])%59 && 
				(c+ms[p])%17 && (c+ms[p])%19 && (c+ms[p])%13 && (c+ms[p])%11 && (c+ms[p])%7 && (c+ms[p])%3 && (c+ms[p])%43 && (c+ms[p])%47 && 
				(c+ms[p])%53 && (c+ms[p])%61 && (c+ms[p])%67 && (c+ms[p])%71 && (c+ms[p])%73 && (c+ms[p])%79 && (c+ms[p])%83 && (c+ms[p])%89 && 
				(c+ms[p])%97 && (c+ms[p])%5 && (c+ms[p])%2)
			{
				fl = true;
				int k = int(sqrt((long double)c)+ms[p]);
				for(int i=101; i<=k; i+=2)
					if((c+ms[p])%i==0)
					{
						fl=false;
						continue;
					}
					if(fl)
					{
						if(c+ms[p]>=beg && c+ms[p]<=end)
						{
							out<<c+ms[p]<<" ";
							pr=true;
						}
					}
			}
		}
	}
	out.close();
	return 1;
}
