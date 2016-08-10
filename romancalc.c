#include "romancalc.h"

/* int roman2base10(char roman_digit) 
 * convert roman digit to base10 value
 * 
 * @param char roman_digit  : I V X  L   C  D   M      Invalid Digit
 * @return int base10 value : 1 5 10 50 100 500 1000   0
 */
int roman2base10(char roman_digit){
  int base10;
  switch(roman_digit){
  case 'I' :
    base10 = 1;
    break;
  case 'V':
    base10 = 5;
    break;
  case 'X':
    base10 = 10;
    break;
  case 'L':
    base10 = 50;
    break;
  case 'C':
    base10 = 100;
    break;
  case 'D':
    base10 = 500;
    break;
  case 'M':
    base10 = 1000;
    break;
  default:
    base10 = 0;   /* ERROR - roman numbers don't have zero */
  }
  return base10;
}

/* int chk_for_valid_roman_digit(char roman_digit) 
 * @param char roman_digit
 *   ONLY valid roman_digits:  M D C L X V I
 * @return 
 *   0 - SUCCESS, input is a valid roman_digit
 *   1 - ERROR, input IS NOT a valid roman_digit    
 */

int chk_for_valid_roman_digit(char roman_digit){
  int ec;
  switch(roman_digit) {
  case 'I' :
    ec = 0;
    break;
  case 'V' :
    ec = 0;
    break;
  case 'X' :
    ec = 0;
    break;
  case 'L' :
    ec = 0;
    break;
  case 'C' :
    ec = 0;
    break;
  case 'D' :
    ec = 0;
    break;
  case 'M' :
    ec = 0;
    break;
  default:
    ec = 1;
  }
  return ec;
}

/*
 * 0 - ERROR : if there's invalid digit detectect
 * strlen(p) - number of roman digits in the input string
 * FIXME: ERROR Reporting is not consistent !!!
 */
int chk_for_valid_roman_num(char *p){
  char *q = &p[0];
  int i;
  for (i = 0; i < strlen(p); i++){
    char roman_digit = *q++;
    if (chk_for_valid_roman_digit(roman_digit) != 0){
      return 0;
    }
  }
  return strlen(p);
}

int getRomanNumber(char *p){
  printf( "Enter a Roman Number : ");
  scanf("%s", p);             /* scanf waits till you enter at least 1 char */
  //printf("str :  %s \n", p);
  //printf("strlen(str) : %ld\n", strlen(p));
  return chk_for_valid_roman_num(p);
}

/*  int toBase10fromRoman(char *p)
 *  @param  char *p   Input- uncompacted or compacted roman numeral
 *  @return int sum   base10 number representation of Input
 *  if a subtractive appears with a I, X, or C to the left of a "larger" symbol
 *  we need to substitute the pair for the correct numeric value
 *  
*/

int toBase10fromRoman(char *p){

  char *q = &p[0];        //char[] arrays are 0-based
  int i;
  int len = strlen(p);    // strlen is 1-based number 6 means 6 digits
  char d0;                // process our romans 2 at a time
  char d1;
  int sum = 0;

  for (i = 0; i < len; i++){

    d0 = *q++;        // d0:d1 form sliding window over digits in our roman number
    if (i < len-1){
      d1 = *q;
    }else{
      d1 = 'e';
    }

    if (d1 != 'e'){
      //printf("i: %d d0: %c  d1: %c\n", i, d0, d1);
      if (roman2base10(d0) < roman2base10(d1)) {
        //printf("found a subtractive pair\n");
        sum = sum + (roman2base10(d1) - roman2base10(d0));
        //printf("sum: %d\n", sum);
        i++;    // inc ptrs to skip fwd by 1 when u hit a subtractive pair
        *q++;        
      } else {
        sum = sum + roman2base10(d0);
        //printf("sum: %d\n", sum );
      }
    } else {
      sum = sum + roman2base10(d0);
      //printf("sum: %d\n", sum );
    }
  }
  return sum;
}

/**
 * The replace function
 *
 * Searches all of the occurrences using recursion
 * and replaces with the given string
 * @param char * o_string The original string
 * @param char * s_string The string to search for
 * @param char * r_string The replace string
 * @return void The o_string passed is modified
 */
void replace(char * o_string, char * s_string, char * r_string) {
      //a buffer variable to do all replace things
      char buffer[1024];
      //to store the pointer returned from strstr
      char * ch;
 
      //first exit condition
      if(!(ch = strstr(o_string, s_string)))
              return;
 
      //copy all the content to buffer before the first occurrence of the search string
      strncpy(buffer, o_string, ch-o_string);
 
      //prepare the buffer for appending by adding a null to the end of it
      buffer[ch-o_string] = 0;
 
      //append using sprintf function
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
 
      //empty o_string for copying
      o_string[0] = 0;
      strcpy(o_string, buffer);
      //pass recursively to replace other occurrences
      return replace(o_string, s_string, r_string);
 }

/* int searchAndReplace(char *p)
 * Parse string of roman numbers & do s&r of all known 'subtractive' forms 
 * 
 * Per Lawrence Turner Ph.D., Professor of Mathematics and Physics, retired
 * @ Southwestern Adventist University (REF: http://turner.faculty.swau.edu/):
 * 
 * The only subtractive forms are:
 *                        Start at the top of the table biggest 1st &
 * DCCCC  CM    900       Search for 1st Col, Replace w 2nd Column 
 * CCCC   CD    400
 * LXXXX  XC     90
 * XXXX   XL     40
 * VIIII  IX      9 
 * IIII   IV      4
 *
 * @param char *p input  <- a valid uncompacted or compacted roman numeral
 *                output -> input modified by doing s&r of all subractive forms
 * @return
 *    0 - SUCCESS
 */

int searchAndReplace(char *p){

  //                    0         1        2       3       4       5
  char *s_str[] = {"DCCCC", "CCCC", "LXXXX", "XXXX", "VIIII", "IIII"};
  char *r_str[] = {"CM",    "CD",   "XC",    "XL",   "IX",    "IV"  };
  int i;
  
  for (i = 0; i < 6; i++){
    //printf("o_string: %s s_string: %s  r_string: %s \n", p, s_str[i], r_str[i]);
    replace(p, s_str[i], r_str[i]);
  }
  return 0;
}

/*                                               0    1  2   3  4  5 6
 *          Inputs:            B < base10  A  <  M    D  C   L  X  V I
 *                              |          |    1000 500 100 50 10 5 1
 *                              |          |
 * int getRomansFromBase10(int dividend, int divisor, int quotient, int remainder)
 *  |                                                    |             |
 *  ec Outputs                                          B/A           B%A 
 *  0 - Succes
 *  1 - Error (divide by zero)
 */
int getRomansFromBase10(int dividend, int divisor, int *quotient, int *remainder){
  if (divisor > 0){
    *quotient = dividend/divisor;
    *remainder = dividend%divisor;
    //printf("quotient: %d remainder: %d", (int) *quotient, (int) *remainder);
    return 0;
  } else {
    return 1;
  }
}

/* int toRomanFromBase10(int base10, char *roman)
 * @param int base10 - input  a base10 num bt 1 & 3999
 * @param char *roman- output base10 converted to a compacted roman numeral
 *                     caller allocates memory for char *roman
 * @return 
 *   0 - Success
 *   1 - Error   base10 input is out-of-range  base10 <= 0 || base10 > MAX_ROMAN 
 */
int toRomanFromBase10(int base10, char *roman){
  
  if ((base10 <= 0)||(base10 > MAX_ROMAN)){
    return 1; // ERROR - 0 is a invalid Roman Number:   1 < Valid Romans < 3999
  }
  
  char romans[] = { 'M',  'D', 'C','L','X','V','I'}; // roman digits
  int divisors[] = {1000, 500, 100, 50, 10, 5,  1};  // divisors
  int quotients[]= { 0,    0,   0,  0,   0, 0,  0};   // resulting quotients
  
  // 1 figure out how many roman digits we got in our base10 -> quotients[]
  int remainder;
  int i;
  for (i=0; i < 7; i++){
    getRomansFromBase10(base10, divisors[i], &quotients[i], &remainder);
    //printf("i: %d base10: %d divisors[i]: %d quotients[i]: %d remainder: %d \n", i, base10, divisors[i], quotients[i], remainder);
    if (quotients[i] >= 1){
      base10 = remainder;
    }
  }
  
  //char substr[100];
  char *substr = (char *) malloc(100);
  // roman[0]="";
  roman[0]='\0';
  int j;
  // 2 formulate char string of the roman digits we find in our base10 number
  //printf("substr: %s, roman: %s\n", substr, roman);
  for (i=0; i < 7; i++){
    if (quotients[i] != 0 ){
      for (j=0; j < quotients[i]; j++){
        //printf("i: %d j: %d substr: %s romans[i]: %c \n", i, j, substr, romans[i]);
        strncat(substr, &romans[i], 1);       // collect our romans into a substr
      }
      //printf("roman: %s  substr: %s\n", roman, substr);
      strncat(roman, substr, strlen(substr)); // and stick em to the output string
      substr[0]='\0';                         // then empty our substr for the next loop

      //printf("roman: %s\n", roman);
    }
  }
  // 3 compact the resulting roman numeral by doing s&r of all the subtractive forms 
  searchAndReplace(roman);
  //printf("roman num out: %s\n", roman);
  
  free(substr);
  
  return 0;   // SUCCESS
}

/* int add2Romans( char *b, char *a, char *result)
 * @param char *b  input roman number b
 * @param char *a  input roman number a
 * @param char *result  output b+a
 * @return
 *  0 - success  result = b + a
 * ERRORS
 *  1 - invalid inputs: invalid digits detected in roman numerals a or b
 *      if [ (a || b) != ['M' || 'D' || 'C' || 'L' || 'X' || 'V' || 'I'] 
 *  2 - invalid inputs: inputs a or b are out of range
 *      if [ (a <= 0)||(b <= 0)||(a > 3999)||(b > 3999) ]
 *  3 - invalid output, b+a will result in a out of range number   
 *      if (a + b) > 3999 
 */
int add2Romans(char *b, char *a, char *result){
  // validate roman numeral inputs - check for valid roman digits
  //printf("chk_for_valid_roman_num(b): %d\n", chk_for_valid_roman_num(b));
  //printf("chk_for_valid_roman_num(a): %d\n", chk_for_valid_roman_num(a));
  if ( (chk_for_valid_roman_num(b) == 0) || (chk_for_valid_roman_num(a) == 0) ){
    return 1;
  }
  // validate inputs - check for out-of-range condition
  if ((toBase10fromRoman(b) > MAX_ROMAN) || (toBase10fromRoman(a) > MAX_ROMAN)){
    return 2;
  }
  if ( ( toBase10fromRoman(b) + toBase10fromRoman(a) ) > MAX_ROMAN ){
    return 3;
  }
  
  int base10 = toBase10fromRoman(b) + toBase10fromRoman(a);
  toRomanFromBase10(base10,result);
  return 0;
}

/* int subtract2Romans( char *b, char *a, char *result)
 * @param char *b  input roman number b
 * @param char *a  input roman number a
 * @param char *result  output b-a
 * @return 
 *  0 - success    result = b-a
 * ERRORS
 *  1 - invalid inputs: invalid digits detected in roman numerals a or b
 *      if [ (a || b) != ['M' || 'D' || 'C' || 'L' || 'X' || 'V' || 'I'] 
 *  2 - invalid inputs: inputs a or b are out of range
 *      if [ (a <= 0)||(b <= 0)||(a > 3999)||(b > 3999) ]
 *            \\\\\\\\////////
 *            this is a given since you can't represent zero with roman digits
 *  3 - invalid output: result is going to be out of range  or negative
 *      if (b <= a) - resulting in a negative number
 */

int subtract2Romans(char *b, char *a, char *result){
  // validate inputs - check for invalid roman digits in the input strings
    if ( (chk_for_valid_roman_num(b) == 0) || (chk_for_valid_roman_num(b) == 0) ){
    return 1;
  }
  // validate inputs - check for out-of-range condition, MAX_ROMAN = 4999 
  if ((toBase10fromRoman(b) > MAX_ROMAN) || (toBase10fromRoman(a) > MAX_ROMAN)){
    return 2;
  }
  if ( toBase10fromRoman(b) <= toBase10fromRoman(a) ){
    return 3;
  }
  
  int base10 = toBase10fromRoman(b) - toBase10fromRoman(a);
  toRomanFromBase10(base10,result);
  return 0;
}
