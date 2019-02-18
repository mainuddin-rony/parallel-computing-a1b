# makefile for a1b

# The -g flag allows us to use a debugger.
CFLAGS = -g -std=c99

# links the math library
LDFLAGS = -lm -lpthread

#When you are ready to time execution, uncomment the next line
# and (important) type "make clean" at the command line, so all
# build products will be recompiled.
#CFLAGS = -O3 -std=c99


.PHONY: run 
run: rpix
	./rpix texas.tif 50 32 
	
rpix: main.o rgbtiff.o timing.o matching.o
	gcc ${LDFLAGS} main.o matching.o rgbtiff.o timing.o -o rpix
	
main.o: main.c matching.h rgbtiff.h timing.h
	gcc ${CFLAGS} -c main.c
	
rgbtiff.o: rgbtiff.c
	gcc ${CFLAGS} -c rgbtiff.c
	
matching.o: matching.c
	gcc ${CFLAGS} -c matching.c
	
timing.o: timing.c
	gcc ${CFLAGS} -c timing.c
	
.PHONY: clean
clean:
	rm -f  *.o rpix

.PHONY: check
check: rpix
	echo
	./rpix logo.tif 1 4
	diff -s out.tif correct_logo.tif
	echo
	./rpix logo.tif 1 3
	diff -s out.tif correct_logo.tif
	echo
	./rpix texas.tif 50 4
	diff -s out.tif correct_texas.tif
	echo	
	./rpix texas.tif 50 5
	diff -s out.tif correct_texas.tif
	echo
	./rpix texas2.tif 50 4
	diff -s out.tif correct_texas2.tif
	echo
	./rpix texas3.tif 50 4
	diff -s out.tif correct_texas3.tif
	echo
	./rpix texas4.tif 50 4
	diff -s out.tif correct_texas4.tif
	echo 
	./rpix texas4.tif 50 32
	diff -s out.tif correct_texas4.tif

	
