/*************************************************************
 * Copyright (C) 2024-07-12 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/
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
	double *wr;  
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



