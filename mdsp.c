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
	unsigned int i,j;

	obj->n = n;
	obj->wr = wr;
	obj->wi = wi;
	obj->br = br;

	//use dp generate bit reverse map
	br[0] = 0;
	for(i = 1;i < n;i = (i<<1))
	{
		for(j = i;j < (i<<1);j++)
		{
			br[j] = br[j-i] + n/(i<<1);
		}
	}

	//generate twinkle coe
	for(i = 0;i < n/2;i++)
	{
		wr[i] = cos(2.0*PI*1.0/n*i);
		wi[i] = -1.0*sin(2.0*PI*1.0/n*i);
	}
}


//fft base 2
void fft2(fft *obj,double *re,double *im)
{
	unsigned int i,j,k,u,d,di,wn;
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


	for(i = 1;i < obj->n;i = di)
	{
		di = (i << 1);
		for(j = 0;j < obj->n;j += di)
		{
			for(k = 0;k < i;k += 1)
			{
				//up and down branch
				u = j+k;
				d = j+k+i;

				//index of w
				wn = k*obj->n/(di);

				//twinkle
				tr = re[d];
				ti = im[d];
				re[d] = obj->wr[wn]*tr - obj->wi[wn]*ti;
				im[d] = obj->wr[wn]*ti + obj->wi[wn]*tr;

				//butterfly
				tr = re[u];
				ti = im[u];
				re[u] = tr + re[d];
				im[u] = ti + im[d];
				re[d] = tr - re[d];
				im[d] = ti - im[d];
			}
		}
	}
}





//ifft base 2
void ifft2(fft *obj,double *re,double *im)
{
	unsigned int i,j,k,u,d,di,wn;
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


	for(i = 1;i < obj->n;i = di)
	{
		di = (i << 1);
		for(j = 0;j < obj->n;j += di)
		{
			for(k = 0;k < i;k += 1)
			{
				//up and down branch
				u = j+k;
				d = j+k+i;

				//index of w
				wn = k*obj->n/(di);

				//twinkle
				tr = re[d];
				ti = im[d];
				re[d] = obj->wr[wn]*tr + obj->wi[wn]*ti;
				im[d] = obj->wr[wn]*ti - obj->wi[wn]*tr;

				//butterfly
				tr = re[u];
				ti = im[u];
				re[u] = tr + re[d];
				im[u] = ti + im[d];
				re[d] = tr - re[d];
				im[d] = ti - im[d];
			}
		}
	}
}

