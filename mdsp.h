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

/* Function prototypes */
void fft_init(fft *obj,INTTYPE n,FLOATTYPE *w,INTTYPE *br);
void fft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im);
void ifft2(fft *obj,FLOATTYPE *re,FLOATTYPE *im);


#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__MDSP_H*/



