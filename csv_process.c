/* This code will convert data in csv text format into matrix data to be easily
   manipulated. Possible later additions will also be to */

/* Need to essentially iterate through the file, parse the integer data, put it into 
   a matrix. Also should include options in this file to download data from quandl/etc... */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.c"

// TODO should put this into a header probably. Let's see how many declarations
// develop. 
size_t get_num_lines(const char*); 

/* This essentially assumes comma-delineated data types. NEW RULE:
   ANY FUNCTION WITH "csv" OUT IN FRONT OF ITS NAME ASSUMES A CSV FILE
   /FORMAT AS INPUT */
size_t csv_get_num_categories(const char*);

matrix* csv_to_matrix(const char*);

/* This needs to return a pointer to the struct as opposed to passing a pointer 
   to it because we don't know the size of the matrix yet. */
matrix* stock_csv_to_matrix(const char* file_name)
{
  // in our context each row will correspond to a day of data  
  int num_lines;

  FILE* file = fopen(filename, "r");

  if (file == NULL)
    {
      fprintf(stderr, 
	      "Error: file could not be opened for stock_csv_to_matrix function. ");
      exit(0);
    }

  /* First get the dimensions */
  int num_lines = get_num_lines(file);

  int num_categories = ;

  /* Next, allocate a matrix of the appropriate size. It will have one less row
     than the file, since the first row is text denoting the categories of data */
  matrix* csv_matrix = init_matrix ;
}

/* This function will extract the number of lines in a file. 
   It should take in the string name of the file as opposed to
   a file as input, since a stream could currently point to any
   arbitrary location in a file yielding an incorrect solution. */
size_t get_num_lines(const char* filename)
{
  FILE *file = fopen(filename);

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for get_num_lines.");
      exit(0);
    }

  /* n will be the length of the line most likely */
  size_t lines = 0, n = 0;
  char *buf = NULL;

  /* Buffering should happen automatically so no need to buffer here tbh.
     For debugging later note that getline is a POSIX routine and not
     part of the C standard library. Recall POSIX is a family of standards
     specified by the IEEE computer society for maintaining compatiblity
     between OS's */
  while (getline (&buf, &n, file))
    {
      lines++;
    }

  /* clean up */
  fclose (file);
  free (buf);

  return num_lines;
}

size_t csv_get_num_categories(const char* filename)
{

  FILE *file = fopen(filename);

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for get_num_lines.");
      exit(0);
    }

  /* n will be the length of the line most likely */
  size_t lines = 0, n = 0;
  char *buf = NULL;

  char* output = getline ( // FINISH FINSIH

  /* Now we just iterate through the line and look for commas */
  
}


matrix* csv_to_matrix(const char* filename)
{

  FILE *file = fopen(filename);

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for get_num_lines.");
      exit(0);
    }


}

