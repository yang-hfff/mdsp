#include "mdsp.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define N 65536

int main(int argc,char *argv[])
{
	fft f;
	static FLOATTYPE w[N];
	static INTTYPE br[N];

	//prepare
	fft_init(&f,N,w,br);

	static FLOATTYPE xr[N];
	static FLOATTYPE xi[N];

	//give x value
	for(unsigned int i = 0;i < N;i++)
	{
		xr[i] = i < 8?1:0;
		xi[i] = 0;
	}

	//do fft
	fft2(&f,xr,xi);
	
	//show
	puts("fft:");
	for(unsigned int i = 0;i < N;i++)
	{
		printf("%lf,%lf\n",xr[i],xi[i]);
	}

	//do ifft
	ifft2(&f,xr,xi);

	//show
	puts("ifft:");
	for(unsigned int i = 0;i < N;i++)
	{
		printf("%lf,%lf\n",xr[i],xi[i]);
	}

	return 0;
}