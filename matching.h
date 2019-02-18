#ifndef MATCHING_H
#define MATCHING_H

#include "pixel.h"


// We're making these functions publicly visible, so main can call them. 


pixel   replaceMatching(pixel p, pixel target, int tolerance, pixel newColor);
void 	replaceAllMatching(pixel array[], int length, pixel target, int tolerance, pixel newColor);
int  	pReplaceAllMatching(int nthreads, pixel array[], int length, pixel target, int tolerance, pixel newColor);


#endif

