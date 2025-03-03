#include "mdsp.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define N 1024


int main(int argc,char *argv[])
{
	osc s;
	
	osc_conifg(&s,1,2*PI/1024*3,0);
	
	for(int i = 0;i < N;i++)
	{
		printf("%lf\n",osc_generate(&s));
	}

	return 0;
}