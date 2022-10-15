/*
 * @author Sehyun Cho
 * Panther ID: 6284494
 *
 * I affirm that I wrote this program myself without any help from any
 * other people or sources from the internet.
 * 
 *
 * The program that sorting words in inputfile in order to ASCII values.
 * Using Binary search technique, initial empty tree reads data from the input file
 * one word at a time, duplicated words will be ignored. Print inorder traversal
 * and free memory for dynamically allocating/deallocating nodes and the buffer for the strings.
 *
 * -c: program needs to compare the strings in uppercase if -c is present.
 *     otherwise, the case stays as read in.
 * -o: program will output the sorted words to the given output file if -o is present.
 *     otherwise, the output shall be the standard output.
 * input_file_name: program will read from the input file if input_file_name is present.
 *                  otherwise, the input will be form the standard input.
 *
 * getopt command line below:
 *
 * usage: bstsort [-c] [-o output_file_name] [input_file_name]
 *
 */

// Import Headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Declaring Node structure as "Node"
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	char *word;
}Node;

// Creating new node when root is NULL state.
struct Node* newNode(char* str)
{
	Node* node;
	// Dynamic memory allocating
	node  = (struct Node*)malloc(sizeof(struct Node));
	node -> word = (char*)malloc(strlen(str));
	// copy the word as str
	strcpy(node -> word, str);
	// set NULL both left and right
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

// Compare strings in Upper case (if -c is present, also case-insensitive)
// if return value > 0, str1 > str2
// if return value < 0, str1 < str2
// if return value == 0, str1 = str2
// making two strings uppercase to make it equal, then compare
int compareString(char *str1, char *str2)
{
	int val;
	while(*str2)
	{
		// assign two strings as uppercase and compare
		val = toupper(*str1) - toupper(*str2);
		if(val)
		{
			return val;
		}
		str1++;
		str2++;
	}
	return *str1;
}

// Otherwise, just read by comparing two strings(case-sensitive)
// if return value > 0, str1 > str2
// if return value < 0, str1 < str2
// if return value == 0, str1 = str2
int compareString2(char *str1, char *str2)
{
	while((*str1 == *str2) && (*str1))
	{
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void insert(Node **root, int cflag, char *str)
{
	// when cflag is active(case-insensitive)
	if(cflag == 1)
	{
		// if root is NULL, create new node
		if(*root == NULL)
		{
			*root = newNode(str);
		}
		// compare strings with using case-insensitive method
		else if(compareString(str, (*root) -> word) > 0)
		{
			insert(&(*root) -> right, cflag, str);
		}
		else if(compareString(str, (*root) -> word) < 0)
		{
			insert(&(*root) -> left, cflag, str);
		}
		else if(compareString(str, (*root) -> word) == 0)
		{
              		return; 
		}
	}
	// otherwise, use different compare method(case-sensitive)
	else if(cflag == 0)
	{
		if(*root == NULL)
		{
			*root = newNode(str);
		}
		// compare strings with using case-sensitive method
		else if(compareString2(str, (*root) -> word) > 0)
		{
			insert(&(*root) -> right, cflag, str);
		}
		else if(compareString2(str, (*root) -> word) < 0)
		{
			insert(&(*root) -> left, cflag, str);
		}
		else if(compareString2(str, (*root) -> word) == 0)
		{
			return;
		}
	}
}

// Inoder printing method
void inorder(struct Node *root, FILE* outFile)
{
	if(root != NULL)
	{
		// Inorder = traversing left->root->right
		inorder((root -> left), outFile);
		fprintf(outFile, "%s\n", (root -> word));
		inorder((root -> right), outFile);
	}
	else
	{
		return;
	}
}

// Reclaim the tree with post-traversal(Free memory)
void reclaimTree(struct Node *root)
{
	// when root is not empty
	if(root != NULL)
	{
		// reclaim tree from the left right and free memory
		reclaimTree(root -> left);
		reclaimTree(root -> right);
		free(root -> word);
		free(root);
	}
	else
	{
		return;
	}
}

// Main function
int main(int argc, char **argv)
{
	// Declare variables
	extern char *optarg;
	extern int optind;
	// Using standard I/O for FILE
	FILE* inFile = stdin;
	FILE* outFile = stdout;
	int cflag = 0;
	int oflag = 0;
	int c = 0;
	int err = 0;
	// storage for the data
	char data[50];
	// The initial tree is empty
	struct Node *root = NULL;

	// Declare the usage
	static char usage[] = "usage: bstsort [-c] [-o output_file_name] [input_file_name]\n";
	
	// Switch statement that ":" contains for o since its take argument
	while((c = getopt (argc, argv, "co:")) != -1)
	{
		switch(c)
		{
			case 'c':
				cflag = 1;
				break;
			case 'o':
				oflag = 1;
				// output file as a write mode
				outFile = fopen(optarg, "w");
				break;
			case '?':
				err = 1;
				break;
		}
	}
	// if error case, print usage.
	if(err)
	{
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	// If there is an input file(inFile)
	if(argv[optind] != NULL)
	{
		if(optind != argc)
		{
			// Open input file as reading mod
			inFile = fopen(argv[optind], "r");
		}
		else
		{
			printf("File is not exists.\n");
			exit(0);
		}
	}
	// from the file, reading if there is a contents
	while(fgets(data, sizeof(data), inFile) != NULL)
	{
		if(compareString2("\n", data) == 0)
		{
			printf("There is no data\n");
		}
		else
		{
			// removing new empty line
			data[strlen(data) - 1] = '\0';
			insert((&root), cflag, data);
		}
	}
	// Using inorder traversal method to print the words.
	inorder(root, outFile);
	// Free memory by using reclaim tree method, before the program ends.
	reclaimTree(root);
	// Exit the program
	exit(0);	
}
