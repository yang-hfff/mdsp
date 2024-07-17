/*************************************************************
 * Copyright (C) 2024-07-12 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
#ifndef __MDSP_H
#define __MDSP_H

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

#include <stdarg.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif /*PI*/

#define FLOATTYPE double
#define INTTYPE	unsigned int

/*declaration of fft object*/
typedef struct 
{
	INTTYPE n;
	INTTYPE *br;
	FLOATTYPE *wr;  
	FLOATTYPE *wi;
}fft;


/*digital oscillator*/
typedef struct 
{
	FLOATTYPE b;
	FLOATTYPE c;
	FLOATTYPE y_1;
	FLOATTYPE y_2;
}osc;


/*declaration of window type*/
typedef enum
{
	RECT = 0,
	BARTLETT,
	KAISER,/*beta = 4.583*/
	HANN,
	HAMM,
	BLACKMAN,
	FLATTOP,
	NUTTAL,
	BLACKMAN_HARRIS, 
}win;

/* Function prototypes */
void fft_init(fft *obj,INTTYPE n,FLOATTYPE *w,INTTYPE *br);
void fft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im);
void ifft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im);
void eular1(INTTYPE n,FLOATTYPE *re,FLOATTYPE *im);
void eular2(INTTYPE n,FLOATTYPE *am,FLOATTYPE *rho);
void window(INTTYPE n,FLOATTYPE *wd,win wtype);
FLOATTYPE getAMPCorrectFactor(INTTYPE n,FLOATTYPE *wd);
FLOATTYPE getPWRCorrectFactor(INTTYPE n,FLOATTYPE *wd);
void osc_conifg(osc *obj,FLOATTYPE a,FLOATTYPE w,FLOATTYPE p);
FLOATTYPE osc_generate(osc *obj);

#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__MDSP_H*/



