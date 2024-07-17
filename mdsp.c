/*************************************************************
 * Copyright (C) 2024-07-12 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#include "mdsp.h"
#include "math.h"


#define square(x)	((x)*(x))

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


//the first type of modified
//zero order Bessel function
static FLOATTYPE bessel0_c1(FLOATTYPE x)
{
	INTTYPE j = 1,m,mj = 1;
	FLOATTYPE y = 1;

	for(m = 1;m < 25;m++)
	{
		mj = mj*m;
		y += (FLOATTYPE)square(pow((double)x/2.0,(double)m)/mj);
	}

	return y;
}

//geneter window factor
void window(INTTYPE n,FLOATTYPE *wd,win wtype)
{
	INTTYPE i;

	if (wtype == RECT)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)1.0;
		}
	}
	else if (wtype == BARTLETT)
	{
		for(i = 0;i < n;i++)
		{
			
			if(i <= (n-1)/2)
			{
				wd[i] = (FLOATTYPE)(2.0*i)/(n-1);
			}
			else 
			{
				wd[i] = (FLOATTYPE)2.0 - (FLOATTYPE)(2*i)/(n-1);
			}
		}
	}
	else if(wtype == KAISER)
	{		
		for(i = 0;i < n;i++)
		{
			wd[i] = bessel0_c1((FLOATTYPE)(4.583*sqrt(1.0 - square(1-2.0/(n-1)*i))))/bessel0_c1((FLOATTYPE)4.583);
		}
	}
	else if (wtype == HANN)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.5*(1.0 - cos(2.0*PI/(n-1)*i)));
		}
	}
	else if (wtype == HAMM)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.54 - 0.46*cos(2*PI/(n-1)*i));
		}
	}
	else if (wtype == BLACKMAN)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.42 - 0.5*cos(2.0*PI/(n-1)*i) + 0.08*cos(4.0*PI/(n-1)*i));
		}
	}
	else if(wtype == FLATTOP)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.21557895 - 0.41663158*cos(2.0*PI/(n-1)*i) + 0.277263158*cos(4.0*PI/(n-1)*i) - 0.083578947*cos(6.0*PI/(n-1)*i) + 0.006947368*cos(8.0*PI/(n-1)*i));
		}
	}
	else if(wtype == NUTTAL)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.3635819 - 0.4891775*cos(2.0*PI/(n-1)*i) + 0.1365995*cos(4.0*PI/(n-1)*i) - 0.010644*cos(6.0*PI/(n-1)*i));
		}
	}
	else if (wtype == BLACKMAN_HARRIS)
	{
		for(i = 0;i < n;i++)
		{
			wd[i] = (FLOATTYPE)(0.35875 - 0.48829*cos(2.0*PI/(n-1)*i) + 0.14128*cos(4.0*PI/(n-1)*i) - 0.01168*cos(6.0*PI/(n-1)*i));
		}
	}
}




//get Amplitude(PEAK-PEAK) correction factor
FLOATTYPE getAMPCorrectFactor(INTTYPE n,FLOATTYPE *wd)
{
	INTTYPE i;
	FLOATTYPE sum = 0;

	for(i = 0;i < n;i++)
	{
		sum += wd[i];
	}

	return (FLOATTYPE)n/sum;
}


//get power(RMS) correction factor
FLOATTYPE getPWRCorrectFactor(INTTYPE n,FLOATTYPE *wd)
{
	INTTYPE i;
	FLOATTYPE sum = 0;

	for(i = 0;i < n;i++)
	{
		sum += square(wd[i]);
	}

	return (FLOATTYPE)sqrt(n/sum);
}


//use different generate sine wave
void osc_conifg(osc *obj,FLOATTYPE a,FLOATTYPE w,FLOATTYPE p)
{
	const FLOATTYPE r = 1;

	obj->b = (FLOATTYPE)(-2.0*r*cos(w));
	obj->c = (FLOATTYPE)(r*r);
	obj->y_2 = (FLOATTYPE)(a*cos(p));
	obj->y_1 = (FLOATTYPE)(a*cos(p)*cos(w) - a*sin(p)*sin(w));
}


//oscillator iter
FLOATTYPE osc_generate(osc *obj)
{
	FLOATTYPE y;

	y = -1*obj->b*obj->y_1 - obj->c*obj->y_2;
	obj->y_2 = obj->y_1;
	obj->y_1 = y;
	
	return y;
}



