/**
 * @author Sehyun Cho
 * Panther ID: 6284494
 * 
 * I affirm that I wrote this program myself without any help from any
 * other people or sources from the internet.
 *
 * MPI program that count number of prime numbers in the numbers from 1 to
 * n where n is long integer. 
 * ======================================================================
 * The value for n which should be set in the program using a constant should
 * be 25000.
 * Each process will test its share of the cases.
 * Each process should not print out any primes that it finds, but it should
 * keep a running total.
 * Before the process finishes, it should print out its ID number and its
 * count of primes that it found.
 * The master process should end with printing a total for the count of the
 * number of primes and the tital amount of time taken to find all the
 * primes.
 * =======================================================================
 * Running this with 7 processors << Goal
 */

// Import Headers
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)
// set value of N as 25000
#define N 25000

// Find prime number function
int findPrime(int id, int prime)
{
	// declare count varaible
	int count;
	//conditional loop to find not prime number
	for(int i = 2; i <= (prime / 2); i++)
		if(prime % i == 0)
			return 0;
	//not prime if the number is 0 or 1
	if(prime == 0 || prime == 1)
		return 0;
	// increment of count vaiable
	count++;
	return 1;
}
// Main function
int main(int argc, char *argv[])
{
	int count;            /* Solutions found by this proc */
	double elapsed_time;  /* Time to find, count solutions */
	int global_count;     /* Total number of solutions */
	int i;
	int id;               /* Process rank */
	int p;                /* Number of processes */
  
	char hostname[1024];

	MPI_Init (&argc, &argv);

	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	
	/* Start timer */
	MPI_Barrier (MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();
	
	count = 0;
	// Iterating counter by findPrime, inclusive 25000
	for (i = id; i <= N; i += p)
		count += findPrime(id, i);
	
	// print id and number of primes each process
	printf("ID: %d | Number of primes: %d\n", id, count);

	MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0,
			MPI_COMM_WORLD);
	/* Stop timer */
	elapsed_time += MPI_Wtime();
	if (!id)
	{
		printf ("Execution time %8.6f\n", elapsed_time);
		fflush (stdout);
	}
	MPI_Finalize();
	if (!id)
	{
		printf ("There are %d prime numbers.\n", global_count);
	}
	// end program
	return 0;
}
