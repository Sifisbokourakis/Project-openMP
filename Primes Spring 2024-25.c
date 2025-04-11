/*Mpokourakis Iosif 4439*/

#include <stdio.h>
#include <omp.h> 

#define UPTO 10000000

long int count,      /* number of primes */
         lastprime;  /* the last prime found */


void serial_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;

	for (i = 0; i < (n-1)/2; ++i) {    /* For every odd number */
		num = 2*i + 3;

		divisor = 1;
		do 
		{
			divisor += 2;                  /* Divide by the next odd */
			quotient  = num / divisor;  
			remainder = num % divisor;  
		} while (remainder && divisor <= quotient);  /* Don't go past sqrt */

		if (remainder || divisor == num) /* num is prime */
		{
			count++;
			lastprime = num;
		}
	}
}


void openmp_primes(long int n) {
	long int i, num, divisor, quotient, remainder;

	if (n < 2) return;
	count = 1;                         /* 2 is the first prime */
	lastprime = 2;
	#pragma omp parallel for private(i, num, divisor, quotient, remainder) num_threads(2)
	for(i = 0; i < (n-1)/2; ++i){
		num = 2*i + 3;
		divisor = 1;
		do{
			divisor += 2;
			quotient = num / divisor;
			remainder = num % divisor;
		}while (remainder && divisor <= quotient);
		if(remainder || divisor == num){
			#pragma omp critical
			{ 
				count ++;
				lastprime = num;
			}
		}
	}
}


int main()
{
	double start_time, end_time; 

	printf("Serial and parallel prime number calculations:\n\n");
	
	/* Time the following to compare performance 
	 */
	start_time = omp_get_wtime();
	serial_primes(UPTO);
	end_time = omp_get_wtime();        /* time it */
	printf("[serial] count = %ld, last = %ld (time = %6f seconds)\n", count, lastprime, end_time - start_time);
	
	start_time = omp_get_wtime();
	openmp_primes(UPTO);
	end_time = omp_get_wtime();        /* time it */
	printf("[openmp] count = %ld, last = %ld (time = %6f seconds)\n", count, lastprime, end_time - start_time);
	
	return 0;
}
