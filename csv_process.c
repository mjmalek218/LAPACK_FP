/* This code will convert data in csv text format into matrix data to be easily
   manipulated. Possible later additions will also be to */

/* Need to essentially iterate through the file, parse the integer data, put it into 
   a matrix. Also should include options in this file to download data from quandl/etc... */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.c"
#include <string.h>

// TODO should put this into a header probably. Let's see how many declarations
// develop. 
size_t get_num_lines(const char*); 

/* This essentially assumes comma-delineated data types. NEW RULE:
   ANY FUNCTION WITH "csv" OUT IN FRONT OF ITS NAME ASSUMES A CSV FILE
   /FORMAT AS INPUT */
size_t csv_get_num_categories(const char*);

matrix* stock_csv_to_matrix(const char*);

/* This needs to return a pointer to the struct as opposed to passing a pointer 
   to it because we don't know the size of the matrix yet. */
matrix* stock_csv_to_matrix(const char* file_name)
{

  /* First get the dimensions */
  size_t num_lines = get_num_lines(file_name);

  size_t num_categories = csv_get_num_categories(file_name);

  /* Next, allocate a matrix of the appropriate size. It will have one less row
     than the file, since the first row is text denoting the categories of data */
  matrix* stock_matrix = init_matrix(num_lines-1, num_categories);

  int i,j;

  
  FILE *file = fopen(file_name, "r");

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for stock_csv_to_matrix");
      exit(0);
    }

  size_t size_buf = 0;
  char* cur_line = NULL;
  ssize_t num_read;

  char* cur_fp;
  
  /* skip immediately to the next line in the stream since
     first line is categories*/
  getline (&cur_line, &size_buf, file);

  /* Now we load the numbers into the matrix */
  for (i = 1; i <= num_lines - 1; i++)
    {
      /* First retrieve the line */
      num_read = getline (&cur_line, &size_buf, file);

      /* Then iterate through */
      for (j = 1; j <= num_categories; j++)
	{
	  cur_fp = strtok(cur_line, ",");
	  set_elem(stock_matrix, i, j, (fp) atoi(cur_fp));
	}
    }

  /* Print to confirm */
  print_matrix(stock_matrix);

  /* ALWAYS free */
  free_matrix(stock_matrix);
}

/* This function will extract the number of lines in a file. 
   It should take in the string name of the file as opposed to
   a file as input, since a stream could currently point to any
   arbitrary location in a file yielding an incorrect solution. */
size_t get_num_lines(const char* file_name)
{
  FILE *file = fopen(file_name, "r");

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for get_num_lines");
      exit(0);
    }

  /* n will be the length of the line most likely */
  size_t num_lines = 0, n = 0;
  char *buf = NULL;
  ssize_t num_read;
  

  /* Buffering should happen automatically so no need to buffer here tbh.
     For debugging later note that getline is a POSIX routine and not
     part of the C standard library. (SO NOT PORTABLE BeYOND LINUX)
     Recall POSIX is a family of standards
     specified by the IEEE computer society for maintaining compatiblity
     between OS's */
  while (-1 != (num_read = getline (&buf, &n, file)))
    {
      num_lines++;
    }

  /* clean up */
  fclose (file);
  free (buf);
  
  return num_lines;
}

size_t csv_get_num_categories(const char* file_name)
{

  FILE *file = fopen(file_name, "r");

  if (file == NULL)
    {
      fprintf(stderr, "Error: File could not be opened for csv_get_num_categories");
      exit(0);
    }

  /* n will be the length of the line most likely */
  size_t num_char = 0, buf_size = 0;
  char *line = NULL;

  num_char = getline (&line, &buf_size, file);

  /* Now we just iterate through the line and look for commas. 
     Initialized to one because there is always one more category
     than the number of delineating commas */
  int i, num_categories = 1;
  for (i = 0; i < num_char; i++)
    {
      if (line[i] == ',')
	{
	  num_categories++;
	}
    }

  return num_categories;
}

