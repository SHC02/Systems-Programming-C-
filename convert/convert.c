#include <stdio.h>
/**
 * @author Sehyun Cho(6284494)
 * I affirm that I wrote this program myself without any help from
 * any other people or sources from the internet.  
 */
double conversion(double milimeters)
{
	return milimeters * 0.0338;
}
int main()
{
	double milimiters;

	printf("=====Convert Milimeters=====\n");
	printf("Milimeters\tOunces");
 	printf("\n10\t\t%0.4f", conversion(10));
	printf("\n18\t\t%0.4f", conversion(18));
	printf("\n30\t\t%0.4f", conversion(30));
	printf("\n58\t\t%0.4f\n", conversion(58));	
        printf("============================\n");
	return 0;
}

