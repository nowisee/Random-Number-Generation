#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define SIZE_MAX 100000   // Num of Random number
#define N 100             // Num of Trials, if N=1 then Bernoulli Distribution
#define P (float)1/3      // Probability of event occurrence

// This func returns the total number of successes of events 
// with a probability of P in N runs
int Binomial(void) {
	float U;
	int x = 0, i;

	for(i=0; i<N; i++) {
		// Generate a random number between 0 and 1
		U = (float)rand() / RAND_MAX;
		if(U < 0) U *= -1;   

		// If the generated random number is less than P, it is considered successful
		if(U < P) x++;
	}

	return x;
}

int main(void) { 
	int i, x;
	float sum = 0, avg = 0, var = 0, std;
	static int count[N+1];

	srand((unsigned)time(NULL));

	// Generate a random number following binomial distribution
	for(i=0; i<SIZE_MAX; i++) {
		x = Binomial();
		sum += x;
		var += x*x;

		count[x]++; // Range of Output is 0~N
	}

	// Compute avg value and var value of generated numbers
	avg = sum/SIZE_MAX;
	var = (var/SIZE_MAX)-(avg*avg);
	std = sqrt(var);

	// Print result
	printf("n*p : %.6f, n*p*(1-p) : %.6f\n", N*P, N*P*(1-P));
	printf("Avg of Generated Numbers : %.6f, Var of Generated Numbers : %.6f\n", avg, var);
	printf("\n");

	// Data export
	FILE *ofp = fopen("Binomial.txt", "wt");

	for(i=0; i<N+1; i++)
		fprintf(ofp, "%d\n", count[i]);

	fclose(ofp);

	return 0;
}