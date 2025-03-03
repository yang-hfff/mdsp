#include "mdsp.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define N 64


int main(int argc,char *argv[])
{
	FLOATTYPE wind[N];
	
	window(N,wind,NUTTAL);
	
	for(int i = 0;i < N;i++)
	{
		printf("%lf\n",wind[i]);
	}

	return 0;
}