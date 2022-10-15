// Import Headers
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "bmplib.h"

/*
 * @author Sehyun Cho
 * Panther ID: 6284494
 * 
 * I affirm that I wrote this program myself without any help from any
 * other people or sources from the internet.
 *
 * This program manipulates 24-bit uncompressed bmp file.
 * -s: scale the image by a scale factor of 2 or 3 as indicated on the command line with a 2 or 3
 * -r: rotate the image by a multiple of 90 degrees clockwise if positive or counter-clockwise if negative
 * -v: flip the image vertically
 * -f: flip the image horizontally
 * -o: output_file, if missing, use standard output
 *
 * If multiple option types are present, the order for processing the image is that:
 * =========================================================
 * == scale -> rotate -> vertical flip -> horizontal flip == 
 * =========================================================
 *
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 *
 * rows     - the original number of rows
 * cols     - the original number of columns
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 *
 * getopt command line below:
 *
 * usage: [-f | -r degrees |-s scale| -v ] [-o output_file] [input_file]
 *
 */
int enlarge(PIXEL* original, int rows, int cols, int scale,
	    PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  // declare variables
  int row;
  int col;
  int temp1;
  int temp2;

  // return error if either rows or columns 0
  if(rows <= 0 || cols <= 0) return -1;

  // new rows and columns will be expanded by scale
  *newrows = rows * scale;
  *newcols = cols * scale;
  
  // set new pixel dynamic memory allocating
  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
  
  //nested for loop row->col->temp2->temp1
  for(row = 0; row < rows; row++)
	  for(col = 0; col < cols; col++)
		  for(temp2 = 0; temp2 < scale; temp2++)
			  for(temp1 = 0; temp1 < scale; temp1++)
			  {
				  // original pixel
				  PIXEL* o = original + row*cols + col;
				  // new pixel declaration
				  PIXEL* n = (*new) + (*newcols) * (row * scale + temp1) + (col * scale + temp2);
			      // by enlarging process, make it new pixel as original
				  *n = *o;
			  }
  return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation,
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  /*
  Rotate 90 degree = -270 degree
  Rotate 180 degree = -180 degree
  Rotate 270 degree = -90 degree
  Rotate 0 degree = 360 degree, same as original
  */
  // declare variables
  int row, col;

  // setup newrows and newcols
  *newrows = rows;
  *newcols = cols;

  // dynamic memory allocating
  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));

  // if rotation degree is 90, also same as -270 degree
  if(rotation == 90 || rotation == -270)
  {
	  for(row = 0; row < rows; row++)
		  for(col = 0; col < cols; col++)
		  {
			  // original pixel
			  PIXEL* o = original + row * cols + col;
			  // new pixel declaration
			  PIXEL* n = (*new) + (rows * (cols - 1 - col)) + row;
			  // by rotation process, make new pixel as original
			  *n = *o;
		  }
  }
  // else if roation degree is 180, also same as -180 degree
  else if(rotation == 180 || rotation == -180)
  {
	  for(row = 0; row < rows; row ++)
		  for(col = 0; col < cols; col++)
		  {
			  // original pixel
			  PIXEL* o = original + row * cols + col;
			  // new pixel declaration
			  PIXEL* n = (*new) + ((rows -row) * cols) - (col + 1);
			  // by rotation process, make new pixel as original
			  *n = *o;
		  }
  }
  // else if rotation degree is 270, also same as -90 degree
  else if(rotation == 270 || rotation == -90)
  {
	  for(row = 0; row < rows; row++)
		  for(col = 0; col < cols; col++)
		  {
			  // original pixel
			  PIXEL* o = original + row * cols + col;
			  // new pixel declaration
			  PIXEL* n = (*new) + rows * col + (rows - 1 - row);
			  // by rotation process, make new pixel as original
			  *n = *o;
		  }
  }
  // otherwise, rotation degree is 0, same as 360 degree
  else if(rotation == 0 || rotation == 360)
  {
	  for(row = 0; row < rows; row++)
		  for(col = 0; col < cols; col++)
		  {
			  // original pixel
			  PIXEL* o = original + row * cols + col;
			  // new pixel declaration
			  PIXEL* n = (*new) + row * cols + col;
			  // by rotation process, make new pixel as original
			  *n = *o;
		  }
  }
  return 0;
}

/*
 * This method Vertically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

int verticalflip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  // declare variables
  int row;
  int col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  // dynamic memory allocating
  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for(row = 0; row < rows; row++)
	  for(col = 0; col < cols; col++)
	  {
		  //original pixel
		  PIXEL* o = original + row * cols + col;
		  // new pixel declaration
		  PIXEL* n = (*new) + (rows - 1 - row) * cols + col;
		  // make new pixel as original
		  *n = *o;
	  }
  return 0;
}


/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

// Given function(horizontally flip bmp file)
int flip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  // declare variables
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  // dynamic memory allocating
  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++)
    {
      // original pixel 
      PIXEL* o = original + row*cols + col;
      // new pixel declaration
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      // make new pixel as original
      *n = *o;
    }

  return 0;
}

// Main function
int main(int argc, char **argv)
{
  // declare variables
  int r, c;
  int newRows, newCols;
  int scaleDegree;
  int rotationDegree;
  extern char *optarg;
  extern int optind;

  // declaration of flags and error
  int fFlag, rFlag, sFlag, vFlag, oFlag, err;

  // bitmap and new bitmap
  PIXEL *b, *nb;

  // I/O file declaration
  char* input_File = NULL;
  char* output_File = NULL;

  // declare usage 
  static char usage[] = "usage: bmptool [-f | -r degrees |-s scale| -v ] [-o output_file] [input_file]\n";
  
  // Switch statement (":" contains if it takes an argument)
  while((c = getopt (argc, argv, "s:r:vfo:")) != -1)
  {
	  switch(c)
	  {
		  case 's':
			  sFlag = 1;
			  // store scale degree
			  scaleDegree = atoi(optarg);
			  break;
		  case 'r':
			  rFlag = 1;
			  // store rotation degree
			  rotationDegree = atoi(optarg);
			  break;
		  case 'v':
			  vFlag = 1;
			  break;
		  case 'f':
			  fFlag = 1;
			  break;
		  case 'o':
			  oFlag = 1;
			  // set output_File
			  output_File = optarg;
			  break;
		  case'?':
			  err = 1;
			  break;
	  }
  }
  // if error occurs, print usage
  if(err == 1)
  {
	  printf("Error Occurred. Please try again.\n");
	  fprintf(stderr, usage, argv[0]);
	  exit(1);
  }

  // Priority: scale -> rotate -> vertical flip -> horizontal flip
  // Reading file first   
  if(input_File)
  {
	  // read inputfile as filename 
	  readFile(input_File, &r, &c, &b);
  }
  else
  {
	  // otherwise, read example 
	  readFile("example.bmp", &r, &c, &b);
  }

  // when sFlag is on
  if(sFlag == 1)
  {
	  // Only allowed the scaleDegree either 2 or 3
	  if(scaleDegree == 2 || scaleDegree == 3)
	  {
		  // covering multiple condition
		  if(rFlag == 1 || fFlag == 1)
		  {
			  // call enlarge function and set as new
			  enlarge(b, r, c, scaleDegree, &nb, &newRows, &newCols);
			  b = nb;
			  r = newRows;
			  c = newCols;
		  }
		  // covering single condition(preventing from error)
		  else
		  {
			  // call enlarge function and set as new
			  enlarge(b, r, c, scaleDegree, &nb, &newRows, &newCols);
			  r = newRows;
			  c = newCols;
		  }
	  }
	  // otherwise, print error emssage
	  else
	  {
		  // when user enter invalid scale degree
		  printf("The scale degree should be either 2 or 3.\n");
		  fprintf(stderr, usage, argv[0]);
		  exit(1);
	  }
  }
  
  // when rFlag is on
  if(rFlag == 1)
  {
	// Not allow if the roation degree is not multiple of 90 degree
	if(rotationDegree % 90 == 0)
	{
		// covering multiple condition
		if(fFlag == 1 ||(fFlag == 1 && sFlag == 1))
		{
			// call rotate function and set as new
			rotate(b, r, c, rotationDegree, &nb, &newRows, &newCols);
			b = nb;
			r = newRows;
			c = newCols;
		}
		// covering single condition(preventing from error)
		else
		{
			// call rotate function and set as new
			rotate(b, r, c, rotationDegree, &nb, &newRows, &newCols);
			r = newRows;
			c = newCols;
		}
	}
	else
	{
		// when user enter invalid rotation degree
		printf("The rotation degree should be muliply of 90 degree.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
  }

  // when vFlag is on
  if(vFlag == 1)
  {
	  // Call vertical flip function
	  verticalflip(b, &nb, r, c);
  }
  

  // when fFlag is on
  if(fFlag == 1)
  {
	  // Call horizontal flip function
	  flip(b, &nb, r, c);
  }

  // when oFlag is on
  if(oFlag == 1)
  {
	  // Call writeFile function and write newfile as output_File
	  writeFile(output_File, r, c, nb);
  } 

  // freeing bitmap memories
  free(b);
  free(nb);
   
  // End program  
  return 0;
 
}
