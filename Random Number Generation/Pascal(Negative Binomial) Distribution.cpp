#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define SIZE_MAX 100000   // Num of Random number
#define ITR_MAX 300
#define R 100             // Num of successes, If R=1 then Geometric Distribution.
#define P (float)1/2      // Pascal Distribution applies only to Bernoulli Trial

// This function returns the number of times of failure 
// until an event with probability P succeeds R times
int Pascal(void) { 
	float U;
	int x = 0, i = 0;

	while(i<R) {
		// Generate a random number between 0 and 1
		U = (float)rand() / RAND_MAX;
		if(U < 0) U *= -1;

		// Success when the generated random number is less than P
		if(U < P) i++;
		else x++;

		// If it fails over ITR_MAX times, it thinks it failed ITR_MAX times
		if(x > ITR_MAX) {
			x = ITR_MAX;
			break; 
		}
	}

	return x;
}

int main(void) {
	int i, x; 
	float sum = 0, avg = 0, var = 0, oavg, ovar;
	float r = R, p = P;
	static int count[ITR_MAX];
	
	srand((unsigned)time(NULL));

	// Generate a random number following Pascal(negative binomial) distribution
	for(i=0; i<SIZE_MAX; i++) {
		x = Pascal();
		sum += x;
		var += x*x;

		count[x-1]++; // Range of Output is 1~100
	}

	// Compute avg value and var value of generated numbers
	avg = sum/SIZE_MAX;
	var = (var/SIZE_MAX) - (avg*avg);
	oavg = r*(1-p)/p;
	ovar = r*(1-p)/(p*p);

	// Print result
	printf("R*(1-P)/P : %.6f, R*(1-P)/P^2 : %.6f\n", oavg, ovar);
	printf("Avg of Generated Numbers : %.6f, Var of Generated Numbers : %.6f\n", avg, var);
	printf("\n");

	// Data export
	FILE *ofp = fopen("Pascal.txt", "wt");

	for(i=0; i<ITR_MAX; i++)
		fprintf(ofp, "%d\n", count[i]);

	fclose(ofp);

	return 0;
}