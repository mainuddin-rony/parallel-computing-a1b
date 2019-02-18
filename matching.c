#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "pixel.h"
#include "matching.h"


// For thread function arguments
typedef  struct {

	//TODO  What's needed here?

} arguments;


// The thread function should only be visible inside this file.
void *	doWork(void * args);


/** Replace all pixels that match the target (within the given tolerance) with newColor.
    @param  array the array of pixels
    @param	length the number of pixels in the array
    @param	target the pixel color to replace
	@param	tolerance the maximum difference between color channels for matching colors
	@param	newColor the color that replaces pixels matching the target
*/
void replaceAllMatching(pixel array[], int length, pixel target, int tolerance, pixel newColor){

	for(int i = 0; i<length; i++){
	
		array[i] = replaceMatching(array[i], target, tolerance, newColor);
	}
}


/** Replace all pixels that match the target (within the given tolerance) with newColor. 
	This is a parallel implementation that will use no more than nthreads threads. It 
	may elect to use fewer threads under some circumstances. The return value is the
	number of threads actually used.
	
	@param	nthreads the number of threads available to use.
    @param  array the array of pixels
    @param	length the number of pixels in the array
    @param	target the pixel color to replace
	@param	tolerance the maximum difference between color channels for matching colors
	@param	newColor the color that replaces pixels matching the target
	
	@return	the number of threads actually used.
*/
int pReplaceAllMatching(int nthreads, pixel array[], int length, pixel target, int tolerance, pixel newColor){
    
	//TODO
	
	   
    return nthreads;
}

void * doWork(void * args){
    
    //TODO 
	    
    return NULL; // We won't use the return value, since results are written directly
    			 // to the pixel array.
}

/** If pixel p matches the target pixel color g, then
 *  return newColor. Otherwise, return pixel p. A pair of pixels only
 *  match if all of their three color channels differ by less than tolerance.
 *  @param p the original pixel
 	@param target the color to replace
 	@param tolerance the difference threshold
 	@param newColor the color that replaces pixels that match the target color
 */
pixel replaceMatching(pixel p, pixel target, int tolerance, pixel newColor){
    
    
    if ( abs(p.red   -  target.red)   < tolerance &&
         abs(p.green -  target.green) < tolerance &&
         abs(p.blue  -  target.blue)  < tolerance
       ) {
        return newColor;
    } else {
        
        return p;
    }
}
