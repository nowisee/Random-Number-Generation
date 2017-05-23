#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define PI 3.141592
#define SIZE_MAX 10000     // Num of Random number
#define RANGE_NUM 1000     // Subset number of Sample Space

double InverseGaussian(float mean, float sigma) {  // Inverse func of Gaussian
	float U1, U2;
	float x, z;

	// Generate a random number between 0 and 1 following a uniform distribution
	U1 = (float)rand() / RAND_MAX; 
	U2 = (float)rand() / RAND_MAX;
	
	// This fomula following gaussian distribution when avg is 0 and std is 1
	z = sqrt(-2*log(U1)) * cos(2*PI*U2); 

	// This fomula following gaussian distribution when avg is 'mean' and std is 'sigma'
	x = mean + (sigma * z);

	return x;
}

int main(void) {
	int i, j;
	float x, temp;
	float pre_avg, pre_std;
	float sum = 0, avg = 0, var = 0, std = 0;
	static int count[RANGE_NUM];

	srand((unsigned)time(NULL));

	printf("Predefine Avg : ");
	scanf("%f", &pre_avg);
	printf("Predefine Std : ");
	scanf("%f", &pre_std);

	// Generate a random number following gaussian distribution
	for(i=0; i<SIZE_MAX; i++) {
		x = InverseGaussian(pre_avg, pre_std);
		sum += x;
		var += x*x;
        
		// Range of Output is (-5<x<=-4.95), (-4.95<x<=-4.90), ... , (4.95<x<5.00)
		for(j=0; j<RANGE_NUM; j++) {  
			temp = -5 + (float)j/100;
			if(temp < x && x <= temp+(float)1/100) {
				count[j]++;
				break;
			}
		}
	}

	// Compute avg value and std value of generated numbers
	avg = sum/SIZE_MAX;
	var = (var/SIZE_MAX) - (avg*avg);
	std = sqrt(var);

	// Print result
	printf("\n");
	printf("Predefined avg : %.6f, Predefined std : %.6f\n", pre_avg, pre_std);
	printf("Avg of Generated Numbers : %.6f, Std of Generated Numbers : %.6f\n", avg, std);
	printf("\n");

	// Data export
	FILE *ofp = fopen("Gaussian.txt", "wt");

	for(i=0; i<RANGE_NUM; i++)
		fprintf(ofp, "%d\n", count[i]);

	fclose(ofp);

	return 0;
}