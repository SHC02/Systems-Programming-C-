/**
 * @author Sehyun Cho
 * Panther ID: 6284494
 * 
 * I affirm that I wrote this program myself without any help from any
 * other people or sources from the internet.
 *
 * Developing multi-process program.
 * Extend the myshell.c programn and add pipelines and I/O directions.
 *
 * The shell program should recognize:
 * =======================================================================
 * 1. ">" 'Redirect standard output' from a command to a file.
 * If the file already exists, it will be erased and overwritten without waring.
 * Example) COP4338$ ls > 1
 * COP4338$ sort myshell.c >2
 * Implement the shell that invoke these commands that wire up the standard
 * I/O so that they "chain" up as expected.
 * 
 * 2.">>" 'Append standard output' from a command to a file if the file exists;
 * does not exist, create one.
 * Example) COP4338$ sort myshell.c >> 1
 * COP4338$ echo "Add a Line" >> 1
 *
 * 3."<" 'Redirect the standard input' to be from a file, rather than the 
 * keyboard.
 * Example) COP4338$ sort < myshell.c
 * COP4338$ sort < myshell.c > 1
 * COP4338$ sort > 1 < myshell.c
 * The second and third examples are the same: the sort program reads the
 * file named "myshell.c" as standard input, sorts it, and then writes 
 * to the file named 1.
 *
 * 4 "|" 'Pass the standard output' of one command to another for further pro
 * cessing.
 * Example) COP4338$ ls | sort
 * COP4338$ sort < myshell.c | grep main | cat > output
 * =======================================================================
 * Make sure have parent process fork the children and wire them up using
 * pipes accordingly.
 * Spaces separating tokens in the command line.
 * There could be more than two command chained by pipes, like the secomd exam
 * ple above.
 *
 */

// Import headers 
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// defining maximum arguments and buffer size
#define MAX_ARGS 20
#define BUFSIZE 1024

// get_args method
int get_args(char* cmdline, char* args[]) 
{
	int i = 0;
       	/* if no args */
	if((args[0] = strtok(cmdline, "\n\t ")) == NULL)
	{	
		return 0;
	}	
	while((args[++i] = strtok(NULL, "\n\t ")) != NULL)
	{
		// if number of arguments reach over maximum
		if(i >= MAX_ARGS) 
		{
			printf("Too many arguments!\n");
			exit(1);
		}
       	}
	/* the last one is always NULL */
	return i;
}

// Execute method 
void execute(char* cmdline) 
{
       	// Declare variables
	int pid, async;
	char* args[MAX_ARGS];
	char* inName;
	char* outName;
	int write, read, append;
	int i;
	FILE* input_file;
	FILE* output_file;
	int in, out;

	// Number of arguments check
	int nargs = get_args(cmdline, args);
	if(nargs <= 0)
	{
		return;
	}
	// Either "quit", "exit" user typed to end program.
	if(!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
	{
	       	exit(0);
	}
	/* check if async call */
	if(!strcmp(args[nargs-1], "&"))
	{
	       	async = 1; args[--nargs] = 0; 
	}
	else
	{
		async = 0;
	}	
	// statement active while iterator is smaller than number of arguments 
	// redirecting for ">", "<"
	// append for ">>"  
	while(i < nargs)
	{
		// when arguments find ">"
		if(!strcmp(args[i], ">"))
		{
			// write is active and set
			write = 1;
			outName = args[i + 1];
			args[i] = 0, args[i++] = 0;
		}
		// when arguments find "<"
		else if(!strcmp(args[i], "<"))
		{
			// read is active and set
			read = 1;
			inName = args[i + 1];
			args[i] = 0, args[i++] = 0;
		}
		// when arguments find ">>"
		else if(!strcmp(args[i], ">>"))
		{
			// append is active and set
			append = 1;
			outName = args[i + 1];
			args[i] = 0, args[i++] = 0;
		}
		// otherwise, iterating
		else
		{
			i++;
		}
	}

	pid = fork();
	
	if(pid == 0)
	{
		// when write is active
		if(write == 1)
		{
			// output file as "write" mode
			if((output_file = fopen(outName, "w")) != NULL)
			{
				out = fileno(output_file);
				dup2(out, STDOUT_FILENO);
			}
			// otherwise, return
			else
			{
				return;
			}
		}
		// when read is active
		if(read == 1)
		{
			// input file as "read" mode
			if((input_file = fopen(inName, "r")) != NULL)
			{
				in = fileno(input_file);
				dup2(in, STDIN_FILENO);
			}
			// otherwise, return
			else
			{
				return;
			}
		}
		// when append is active
		if(append == 1)
		{
			// set output file as "append" mode
			if((output_file = fopen(outName, "a")) != NULL)
			{
				out = fileno(output_file);
				dup2(out, STDOUT_FILENO);
			}
			// otherwise, return
			else
			{
				return;
			}
		}
		/*child process*/
		execvp(args[0], args);
		
		/*return only when exec fails*/
		perror("exec failed");
		exit(-1);
	}
	/*parent process*/
	else if (pid > 0)
	{
		if(!async)
		{
			waitpid(pid, NULL, 0);
		}
		else
		{
			printf("this is an async call\n");
		}
	}
	// when error occurred
	else
	{
			perror("fork failed");
			exit(1);
	}
}

// function that count pipes, similar as get_args funcion
// Could not figure out how to apply on execute method...
int pipeCheck(char* cmdline, char* args[])
{
	int i = 0;
	
	if((args[0] = strtok(cmdline, "|")) == NULL)
	{
		return 0;
	}
	while((args[++i] = strtok(NULL, "|")) != NULL);
	{
		if(i > MAX_ARGS)
		{
			printf("Too many arguments!\n");
			exit(1);
		}
	}
	return i;
}

// Main function
int main(int argc, char* argv[])
{
	// Declare buffer size of cmdline
	char cmdline[BUFSIZE];

	//execute until user type "exit" or "quit"
	for(;;) 
	{
		printf("COP4338$ ");
		if(fgets(cmdline, BUFSIZE, stdin) == NULL)
		{
			perror("fgets failed");
			exit(1);
		}
		// execute command line
		execute(cmdline);
	}
	// end program
	return 0;
}
