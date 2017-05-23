#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define SIZE_MAX 100000   // Num of Random number
#define M 250             // 250 red balls out of 1000 balls
#define N 1000            // Num of balls
#define K 200             // Num of samples extracted

// This function returns the number of red balls when K balls are drawn
int Hypergeometric(void) {
	float U, n = N, m = M;
	int x = 0, i;

	for(i=0; i<K; i++) {
		// Generate a random number between 0 and 1
		U = (float)rand() / RAND_MAX;
		if(U < 0) U *= -1;

		n--;            // pull a ball
		if(U < m/n) {   // when the red ball is pulled
			m--;        // reduce the number of red balls by one
			x++;        // num of red balls drawn
		}
	}

	return x;
}

int main(void) { 
	int i, x;
	float sum = 0, avg = 0, var = 0, m = M, n = N, k = K, oavg, ovar;
	static int count[K+1];

	srand((unsigned)time(NULL));

	for(i=0; i<SIZE_MAX; i++) {
		x = Hypergeometric();
		sum += x;
		var += x*x;

		count[x-1]++; // Range of Output is 0~200
	}

	// Compute avg value and var value of generated numbers
	avg = sum/SIZE_MAX;
	var = (var/SIZE_MAX) - (avg*avg);
	oavg = m*k/n;
	ovar = oavg*((k-1)*(m-1)/(n-1)-oavg+1);

	// Print result
	printf("M*K/N : %.6f, (M*K/N)*((K-1)*(M-1)/(N-1)-(M*K/N)+1 : %.6f\n", oavg, ovar);
	printf("Avg of Generated Numbers : %.6f, Var of Generated Numbers : %.6f\n", avg, var);
	printf("\n");

	// Data export
	FILE *ofp = fopen("Hypergeometric.txt", "wt");

	for(i=0; i<K; i++)
		fprintf(ofp, "%d\n", count[i]);

	fclose(ofp);

	return 0;
}