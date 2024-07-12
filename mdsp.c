/*************************************************************
 * Copyright (C) 2024-07-12 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "mdsp.h"
#include "math.h"


//generate twinkle coe and bit reverse
void fft_init(fft *obj,unsigned int n,double *wr,double *wi,unsigned int *br)
{
	unsigned int r;
	unsigned int i;

	r = (unsigned int)(log((double)n)/log((double)2));

	obj->n = n;
	obj->wr = wr;
	obj->wi = wi;
	obj->br = br;

	br[0] = 0;
	for(i = 1;i < n;i++)
	{
		br[i] = (br[i>>1]>>1)|((i&1)<<(r-1));
	}

	for(i = 0;i < n/2;i++)
	{
		wr[i] = cos(2.0*PI*1.0/n*i);
		wi[i] = -1.0*sin(2.0*PI*1.0/n*i);
	}
}


//fft base 2
void fft2(fft *obj,double *re,double *im)
{
	unsigned int i,j,k;
	double tr,ti;

	//bit reverse
	for(i = 0;i < obj->n;i++)
	{
		if(i < obj->br[i])
		{
			tr = re[i];
			ti = im[i];
			re[i] = re[obj->br[i]];
			im[i] = im[obj->br[i]];
			re[obj->br[i]] = tr;
			im[obj->br[i]] = ti;
		}
	}


	for(i = 1;i < obj->n;i *= 2)
	{
		for(j = 0;j < obj->n;j += 2*i)
		{
			for(k = 0;k < i;k += 1)
			{
				//twinkle
				tr = re[j+k+i];
				ti = im[j+k+i];
				re[j+k+i] = obj->wr[k*obj->n/(2*i)]*tr - obj->wi[k*obj->n/(2*i)]*ti;
				im[j+k+i] = obj->wr[k*obj->n/(2*i)]*ti + obj->wi[k*obj->n/(2*i)]*tr;

				//butterfly
				tr = re[j+k];
				ti = im[j+k];
				re[j+k] = tr + re[j+k+i];
				im[j+k] = ti + im[j+k+i];
				re[j+k+i] = tr - re[j+k+i];
				im[j+k+i] = ti - im[j+k+i];
			}
		}
	}
}





//ifft base 2
void ifft2(fft *obj,double *re,double *im)
{
	unsigned int i,j,k;
	double tr,ti;

	//bit reverse
	for(i = 0;i < obj->n;i++)
	{
		if(i < obj->br[i])
		{
			tr = re[i];
			ti = im[i];
			re[i] = re[obj->br[i]];
			im[i] = im[obj->br[i]];
			re[obj->br[i]] = tr;
			im[obj->br[i]] = ti;
		}
	}


	for(i = 1;i < obj->n;i *= 2)
	{
		for(j = 0;j < obj->n;j += 2*i)
		{
			for(k = 0;k < i;k += 1)
			{
				//twinkle
				tr = re[j+k+i];
				ti = im[j+k+i];
				re[j+k+i] = obj->wr[k*obj->n/(2*i)]*tr + obj->wi[k*obj->n/(2*i)]*ti;
				im[j+k+i] = obj->wr[k*obj->n/(2*i)]*ti - obj->wi[k*obj->n/(2*i)]*tr;

				//butterfly
				tr = re[j+k];
				ti = im[j+k];
				re[j+k] = tr + re[j+k+i];
				im[j+k] = ti + im[j+k+i];
				re[j+k+i] = tr - re[j+k+i];
				im[j+k+i] = ti - im[j+k+i];
			}
		}
	}
}

