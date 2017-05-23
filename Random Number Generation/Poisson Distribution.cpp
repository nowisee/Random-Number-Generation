#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define SIZE_MAX 100000
#define RANGE_NUM 100
#define LAMBDA 50          // ¥ë = 50

// Generate random exponential variance following exponential distribution when ¥ë=50
float Rexp(void) {
	float U, x;

	// Generate a random number between 0 and 1
	U = (float)rand()/RAND_MAX;
	if(U < 0) U *= -1;

	x = -log(U)/LAMBDA;

	return x;
}

// Generate random number following Poisson distribution 
// using the previously generated exponential variance
float Poisson(void) {
	float i, x, y;

	x = -1;
	i = 0;

	while(i < 1) {
		y = Rexp();
		i += y;
		x++;
	}

	return x;
}

int main(void) { 
	int i, j;
	float x[SIZE_MAX], sum=0, avg=0, var=0, lambda=LAMBDA;
	static int count[RANGE_NUM];

	srand((unsigned)time(NULL));

	for(i=0; i<SIZE_MAX; i++) {
		x[i] = Poisson();
		sum += x[i];
		var += x[i]*x[i];
		// Range of Output is (0<x<=1), (1<x<=2), ... , (99<x<=100)
		for(j=0; j<RANGE_NUM; j++)
			if(j<x[i] && x[i]<=j+1) count[j]++; 
	}

	//Compute avg value and var value of generated numbers
	avg = sum/SIZE_MAX;
	var = (var/SIZE_MAX) - (avg*avg);

	printf("lambda : %.6f\n", lambda);
	printf("Avg of Generated Numbers : %.6f, Var of Generated Numbers : %.6f\n", avg, var);
	printf("\n");

	// Data export
	FILE *ofp = fopen("Poisson.txt", "wt");

	for(i=0; i<RANGE_NUM; i++)
		fprintf(ofp, "%d\n", count[i]);

	fclose(ofp);

	return 0;
}