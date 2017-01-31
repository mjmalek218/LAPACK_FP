/* Tests for csv processing */

#include "csv_process.c"

void test__csv()
{
  /* First test edge cases */
  const char* Facebook_csv_file = "../Financial_Data/stocks/WIKI-FB.csv"; 

  printf("The number of lines in the Facebook data file should be: 1074 \n");

  printf("The returned number is: %zu \n", get_num_lines(Facebook_csv_file));

  printf("\n");

  printf("The number of categories in the Facebook data file should be: 13\n");

  printf("The returned number is: %zu \n", csv_get_num_categories(Facebook_csv_file));

  printf("\n");

  printf("Now load the data into a matrix and print. Eyeball test. \n");

  print_matrix(stock_csv_to_matrix(Facebook_csv_file));

}


int main()
{
  test__csv();
  
  return 0; 
}
