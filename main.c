//
//  main.c
//  a1b
//
//  Created by Philip Rhodes on 1/24/19.
//  Copyright © 2019 Philip Rhodes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include  <math.h>

#include "pixel.h"
#include "matching.h"
#include "rgbtiff.h"
#include "timing.h"







/** These lines below are function "prototypes". They just tell the compiler
 *  what the function parameter and return types are. 
 */
void  	printPixelArray( pixel arr[], int length);
void  	usage(void);


// Replace all occurrences of Texas Burnt Orange in the given tif image with the much nicer
// UM Navy Blue. The tolerance argument determines how different color channels can be while
// still considered to match.

// Usage: ./rpix <filename> <tolerance> <nthreads>
//        where <filename> is the name of an uncompressed TIFF file,
//        <tolerance> is the maximum difference allowed when matching pixel color channels,
//        and <nthreads> is the number of threads to use. ( >1 invokes the parallel version )
int main(int argc, const char * argv[]) {
   
    if(argc != 4)
        usage();

    
    int height=0, width=0;
    int tolerance = atoi(argv[2]);
    int nthreads = atoi(argv[3]);
    
    unsigned char * bytes = readRGBtiff(argv[1], &width, &height);
    int length = width * height;

    pixel * pixels = (pixel *) bytes;

    pixel texasBurntOrange = {191, 87, 0};    // but this one's worse
    pixel navyBlue = {22, 43, 72}; // UM's majestic Navy Blue
    
    
    if(pixels) {
        
        printf("Successfully opened file: %s\n", argv[1]);
    } else {
        
        fprintf(stderr, "Fatal error in main(): readRGBtiff() returned NULL. \n");
        return 2;
    }

    if(nthreads > 1){
        
        printf("Running parallel code.\n");
     	double then = currentTime();
        int threadsUsed = pReplaceAllMatching(nthreads, pixels, length, texasBurntOrange, tolerance, navyBlue);
        double now = currentTime();
    	printf("%%%%%% paralleltime %.3lf milliseconds.\n", (now - then) * 1000);
    	printf("%%%%# %d threads were used.\n", threadsUsed);

      } else {
        
        printf("Running serial code.\n");
        double then = currentTime();
        replaceAllMatching(pixels, length, texasBurntOrange, tolerance, navyBlue);
        double now = currentTime();
        
        printf("%%%%%% serialtime %.3lf milliseconds.\n", (now - then) * 1000);
    }

    int err = writeRGBtiff("out.tif", bytes, width, height);
    
    if (err){
        
        fprintf(stderr, "Error when writing file: out.tif\n");
        return 3;
    }
    
    return 0; // success !!
}


/** For debugging. Given an array of pixels, this function will print out
 *  the color values in each pixel, up to the specified length.
 */
void  printPixelArray( pixel arr[], int length){
    
    for(int i=0; i<length; i++){
        
        printf("{%u, %u, %u} ", arr[i].red, arr[i].green, arr[i].blue);
    }
    printf("\n");
    
}


/** Print a message to stdout explaining how to run the program, and
 *  then exit with status 1.
 */
void usage(){
    
    printf("Usage: ./rpix <filename> <tolerance> <nthreads>\n");
    printf("        where <filename> is the name of an uncompressed TIFF file,\n");
    printf("        <tolerance> is the maximum difference allowed when matching pixel color channels,\n");
    printf("        and <nthreads> is the number of threads to use. ( >1 invokes the parallel version ).\n");
    exit(1);
}



