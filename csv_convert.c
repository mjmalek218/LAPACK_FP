/* This code will convert data in csv text format into matrix data to be easily
   manipulated. Possible later additions will also be to */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.c"

/* Need to essentially iterate through the file, parse the integer data, put it into 
   a matrix. Also may include options in this file to download data from quandl/etc... */

void get_text_linenum(FILE*); // only operates on csv text file

struct matrix* csv_to_matrix(const char* file_name);


/* This needs to return a pointer to the struct as opposed to passing a pointer 
   to it because */
struct matrix* csv_to_matrix(const char* file_name)
{
  // in our context this will be dates 
  int num_lines;

  FILE* file = fopen(filename, "r");

  if (file == NULL)
    {
      fprintf(stderr, "Error: file could not be opened");
      exit(0);
    }

  /* First get the number of lines in the files so we can appropriately allocate
     memory. */
  int num_lines = get_text_linenum(file);


  /* Next, allocate a matrix of the appropriate size. It will have one less row
     than the file, since the first row is text denoting the categories. */
  
  

}




