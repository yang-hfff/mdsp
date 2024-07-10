/***
*mdsp.h - definitions for digital signal process
*
*       Copyright (c) Yang Haifeng. All rights reserved.
*
*Purpose:
*       This file contains fft&ifft,fir&iir(filter part are not complete yet!!!)
*       this library is suitable for every version of c/c++,and suitable for every machine.
*       [ANSI-C/C99/C11/C++]
*
*       [Public]
*
****/
#ifndef __MDSP_H
#define __MDSP_H

#ifndef PI
#define PI 3.14159265358979323846
#endif /*PI*/

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

/*declaration of fft object*/
typedef struct 
{
	unsigned int n;
	unsigned int *br;
	double *wr;  /*(can n->n/2?)*/
	double *wi;
}fft;

/* Function prototypes */
void fft_init(fft *obj,unsigned int n,double *wr,double *wi,unsigned int *br);
void fft2(fft *obj,double *re,double *im);
void ifft2(fft *obj,double *re,double *im);


#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__MDSP_H*/



