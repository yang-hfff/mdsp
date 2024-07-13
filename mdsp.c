/*************************************************************
 * Copyright (C) 2024-07-12 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "mdsp.h"
#include "math.h"


//generate twinkle coe and bit reverse
void fft_init(fft *obj,INTTYPE n,FLOATTYPE *w,INTTYPE *br)
{
	INTTYPE i,j;

	obj->n = n;
	obj->wr = w;
	obj->wi = w + n/2;
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
		obj->wr[i] = (FLOATTYPE)cos(2.0*PI*1.0/n*i);
		obj->wi[i] = (FLOATTYPE)(-1.0*sin(2.0*PI*1.0/n*i));
	}
}


//fft base 2
void fft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im)
{
	INTTYPE i,j,k,u,d,di,wn;
	FLOATTYPE tr,ti;

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
				d = u+i;

				//index of w
				wn = (k*obj->n)/(di);

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
void ifft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im)
{
	INTTYPE i,j,k,u,d,di,wn;
	FLOATTYPE tr,ti;

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
				d = u+i;

				//index of w
				wn = (k*obj->n)/(di);

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


//imag-real to polar form
void eular1(INTTYPE n,FLOATTYPE *re,FLOATTYPE *im)
{
	INTTYPE i;
	FLOATTYPE temp;

	for(i = 0;i < n;i++)
	{
		temp = re[i];
		re[i] = (FLOATTYPE)sqrt(temp*temp + im[i]*im[i]);
		im[i] = (FLOATTYPE)atan2(im[i],temp);
	}
}

//polar to imag-real form
void eular2(INTTYPE n,FLOATTYPE *am,FLOATTYPE *rho)
{
	INTTYPE i;
	FLOATTYPE temp;

	for(i = 0;i < n;i++)
	{
		temp = am[i];
		am[i] = (FLOATTYPE)(temp*cos(rho[i]));
		rho[i] = (FLOATTYPE)(temp*sin(rho[i]));
	}
}




