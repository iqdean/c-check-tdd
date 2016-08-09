#include "romancalc.h"

int main () {

  /* allocate char[] for roman number 1 */

  char *num1;
  char *num2;
  char *num3;
  num1 = (char *) malloc(100);   /* strlen(num1) = 0 at this point */ 
  num2 = (char *) malloc(100);
  num3 = (char *) malloc(100);
  char *num4 = (char *) malloc(100);
  
  // test chk_for_valid_roman_num(*p) & chk_for_roman_digit(char roman_digit)
  while (getRomanNumber(num1) == 0) {
    printf("You entered invalid Roman Number, try again \n");
  }

  while (getRomanNumber(num2) == 0) {
    printf("You entered invalid Roman Number, try again \n");
  }

  // test toBase10fromRoman(char *roman)
  printf("toBase10fromRoman(%s): %d\n", num1, toBase10fromRoman(num1));
  printf("toBase10fromRoman(%s): %d\n", num2, toBase10fromRoman(num2));

  int base10 = toBase10fromRoman(num2);

  // test toRomanFromBase10(base10, char *roman)
  if (toRomanFromBase10(base10, num3) == 0) {
    printf(" %d > toRomanFromBase10 > %s \n", base10, num3);
  } else {
    printf(" %d > toRomanFromBase10 > ERROR \n", base10);
  }
  
  // test add2Romans(char *b, char *a, char *result)
  int ec = add2Romans(num1, num2, num4);
  if (ec == 0){
    printf("add2Romans(%s + %s = %s)\n", num1, num2, num4);
    printf("toBase10fromRoman(%s): %d\n", num4, toBase10fromRoman(num4));
  } else {
    printf("add2Romans(%s + %s) resulted in ERROR: %d\n", num1, num2, ec);
  }
   
  // test subtract2Romans(char *b, char *a, char *result)  result = b-a
  ec = subtract2Romans(num4, num2, num3);
  if (ec == 0){
    printf("subtract2Romans(%s - %s = %s)\n", num4, num2, num3);
    printf("toBase10fromRoman(%s): %d\n", num3, toBase10fromRoman(num3));
  } else {
    printf("subtract2Romans(%s - %s) resulted in ERROR: %d\n", num4, num2, ec);
  }
 
   
  free(num1);
  free(num2);
  free(num3);
  free(num4);
  
  return 0;
}
