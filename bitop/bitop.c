/*
 * @author Sehyun Cho
 * Panther ID: 6284494
 *
 * I affirm that I wrote this program myself without any help from any
 * other people or sources from the internet.
 *
 * This is the program that manipulate bits in a number entered by the user
 * using the binary representation of the number. The original integer value between
 * 1 to 30000 inclusive using scanf. The integer is unsigned type, output is to the screen.
 * Only bitwise operators must be used and shift bits or use the logical bitwise operators.
 *
 * How this program work:
 * 1. User will enter the beginning integer.
 * 2. Ask user which bit to manipulate, between 0 and 31 refers 2^0 to 2^31 inclusive.
 * 3. Ask user if they want to set or clear the bit(s for set, c for clear).
 * 4. Output the new decimal number.
 * 5. Ask the user if they want to do it again.(y for yes, n for no)
 * 6. The program won't stop until user enter the value 'n' from step 5. 
 */

// Import Headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
	// declare variables
	uint32_t beginInt;
	uint32_t changeBit;
	char setOrClear;
	char yesOrNo;
	int result;

	// Reading user's integer to manipulate
	printf("Please enter the begin integer between 1 and 30000 inclusive: ");
	scanf("%d", &beginInt);
	if(beginInt < 1 || beginInt > 30000)
	{
		printf("Out of bound. The program will end.\n");
		exit(1);
	}

	// do-while loop after reading begin integer
	do
	{
	// another do-while loop preventing not reading different integer after one process done
 	do
	{
	printf("Which bit you want to manipulate? choose between 0 to 31 inclusive: ");
	scanf("%d", &changeBit);
	// if bit is out of bound
	if(changeBit < 0 || changeBit > 31)
	{
		printf("Out of bound. try again number 0 to 31.\n");
	}
	// execute until user put correct value 0 to 31
	}while(changeBit < 0 || changeBit > 31);
	
	printf("Do you want to set or clear the bit?(s or c): ");
	scanf(" %c", &setOrClear);
	// if user choose to set
	if(setOrClear == 's')
	{
		// set input integer according to input bit using bitwise operator
		beginInt |= 1 << changeBit;
		// store as result
		result = beginInt;	
	}
	// if user choose to clear
	else if(setOrClear == 'c')
	{	
		// clear input integer according to input bit using bitwise operator
		beginInt &= ~(1 << changeBit);
		// store as result
		result = beginInt;
	}
	// if input option is neither s nor c, print error message and end program
	else
	{
		printf("Not expected input. The input must be s or c. Program will end.\n");
		exit(1);
	}
	// print result
	printf("Your result is: %d\n", result);

	// Asking user if user want to do it again
	printf("Do you want to do it again?(y/n): ");
	scanf(" %c", &yesOrNo);
	// if user choose 'n'
	if(yesOrNo == 'n')
	{
		printf("Thank you! Good Bye.\n");
	}
	// connected to first do-while loop, execute if user put 'y'
	}while(yesOrNo == 'y');

	// end program
	return 0;
}
