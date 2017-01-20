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
unsigned get_num_lines(FILE*); 

/* This essentially assumes comma-delineated data types. NEW RULE:
   ANY FUNCTION WITH "csv" OUT IN FRONT OF ITS NAME ASSUMES A CSV FILE
   /FORMAT AS INPUT */
unsigned csv_get_num_categories(FILE*);

matrix* csv_to_matrix(const char* file_name);

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

  /* Next, allocate a matrix of the appropriate size. It will have one less row
     than the file, since the first row is text denoting the categories of data */
  matrix* csv_matrix = init_matrix ;
  

}

/* This function will extract the number of lines in the given
   input file stream.  */
unsigned get_num_lines(FILE* file)
{
  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for get_num_lines.");
      exit(0);
    }

  char* line = NULL;
  size_t num_lines = 0;
  size_t len = 0;
  ssize_t read;

  /* size_t seems to just be an unsigned int, whereas ssize_t
     guarantees the return of -1 as well. I believe I recall reading
     in CSPP that ssize_t can only represent roughly half the positive
     values size_t can, as a result of the -1 requirement and 2's complement. */
  size_t lines;
  ssize_t read;

  /* Oh...reason why line is double pointer is because its a pointer to a string...*/
  while ((read = getline(&line, &len, fp)) != -1)
    {
      
    }

    return num_lines;

}
