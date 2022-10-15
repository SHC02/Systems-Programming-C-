/*
  @author Sehyun Cho
  Panther ID: 6284494
  I affirm that I wrote this program myself without any help from any 
  other people or sources from the internet.
  
  Salary calculator that do bonuses and raises to a base salary 
  as well as a veterans bump. Taxes will be deducted from the 
  salary as well. Using getopt to parse the command line, to get salary.

  -b: 5000 bonus on top of the salary, adds to the base.
  -r: multiplies the base by percentage and adding up.
  -v: 6000 bonus on top of the salary, adds to the base.
  -t: multiplies the base by percentage and subtracting.
  
  getopt command line below:

  usage: salary [-bv] [-r rnum] -t tnum base

*/

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Main fuction
int main(int argc, char **argv)
{	
	// Declare variables
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int tnum, rnum = 0;
	int tflag = 0;
	int base;
	double rAmount, vBonus, bBonus, tax, salary;

	// Declare usage
	static char usage[] = "usage %s [-bv] [-r rnum] -t tnum value\n";
	// Switch statement - Since 'r' and 't' take argument, ':' contain.
	while ((c = getopt (argc, argv, "vr:bt:")) != -1)
	{
		switch(c)
		{
			case 'v':
				// Assign bonus 6000 if case v
				vBonus = 6000;
				break;
			case 'r':
				rnum = atoi(optarg);
				// Restrict r value in between 2 and 10
				if(rnum < 2 || rnum > 10)
				{
					fprintf(stderr, "%s:Error. The rnum should be between 2 and 10.\n");
					exit(1);
				}
				rAmount = rnum * 0.01;
				break;
			case 'b':
				// Assign bonus 5000 if case b
				bBonus = 5000;
				break;
			case 't':
				tnum = atoi(optarg);
				// Restrict t value in between 5 and 30
				if(tnum < 5 || tnum > 30)
				{
					fprintf(stderr, "%s:Error. The tnum should be between 5 and 30.\n");
					exit(1);
				}
				tflag = 1;
				tax = tnum * 0.01;
				break;
			case '?':
				// case '?' shows marks as an error
				err = 1;
				break;
		}
	}

	// If tflag is 0
	if(tflag == 0)
	{
		// Print error message since t is mandatory.
		fprintf(stderr, "%s: Missing taxes.\n", "result");
		exit(1);
	}
 
	// Arguments after the command line options
	if(optind < argc)
	{
		base = atoi(argv[optind]);
		// Restrict base value in between 20000 and 90000
		if(base < 20000 || base > 90000)
		{
			fprintf(stderr, "%s: Error. Base salary should be between 20000 and 90000.\n", argv[0]);
			exit(1);
		}
		// If base value qulitfies, calculates the salary.
		else
		{
			salary = base;
			salary += vBonus;
			salary = salary + (salary * rAmount);
			salary += bBonus;
			salary = salary - (salary * tax);	
		}
		// After calculation, print the salary in two decimal places.
		printf("result: %0.2f\n", salary);
		exit(0);
	}
}
