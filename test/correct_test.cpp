#include "mdsp.h"
#include <iostream>
#include <stdio.h>

using namespace std;


#define N 1024


int main(int argc,char *argv[])
{
	//产生窗
	FLOATTYPE wind[N];
	window(N,wind,HANN);
	
	//获取修正系数
	FLOATTYPE k = getAMPCorrectFactor(N,wind);
	
	//初始化FFT
	fft fb;
	static FLOATTYPE w[N];
	static INTTYPE br[N];
	fft_init(&fb,N,w,br);
	
	
	//配置数字振荡器
	osc sigGen;
	osc_conifg(&sigGen,1.0,2.0*PI*200/1024,-PI/2);
	
	
	//利用数字振荡器模仿产生信号过程
	static FLOATTYPE x_re[N];
	static FLOATTYPE x_im[N];	
	for(unsigned int i = 0;i < N;i++)
	{
		x_re[i] = osc_generate(&sigGen);
		x_im[i] = 0;
	}
	
	
	//对信号加窗并进行修正
	for(unsigned int i = 0;i < N;i++)
	{
		x_re[i] *= wind[i]*k;
		x_im[i] = 0;
	}
	
	
	//傅里叶变换
	fft2(&fb,x_re,x_im);
	
	
	//利用欧拉公式把直角表示转化成极坐标表示
	eular1(N,x_re,x_im);
	
	//打印数据
	FILE *fwp = fopen("add_window.csv","w");
	for(int i = 0;i < N;i++)
	{
		fprintf(fwp,"%lf\n",x_re[i]);
	}
	fclose(fwp);

	return 0;
}