#include "mdsp.h"
#include <iostream>
#include<ctime>

using namespace std;

#define N 16777216

int main(int argc,char *argv[])
{
	fft f;
	static FLOATTYPE w[N];
	static INTTYPE br[N];
	static FLOATTYPE xr[N];
	static FLOATTYPE xi[N];
	clock_t startTime,endTime;
	
	//prepare
	startTime = clock();
	fft_init(&f,N,w,br);
	endTime = clock();
	cout << "init used time:"  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	
	//do fft
	startTime = clock();
	fft2(&f,xr,xi);
	endTime = clock();
	cout << "fft used time:"  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	//do ifft
	startTime = clock();
	ifft2(&f,xr,xi);
	endTime = clock();
	cout << "ifft used time:"  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	return 0;
}