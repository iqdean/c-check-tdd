/* 
 * File:   romancalc.h
 * Author: iqdean
 *
 * Created on August 9, 2016, 12:11 AM
 */

#ifndef ROMANCALC_H
#define ROMANCALC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ROMAN NUMERALS 101
 * Roman numerals are written as combinations of the seven letters in the table below. 
 * char romans[] = { 'M',  'D', 'C','L','X','V','I'}; // roman digits
 * int divisors[]= { 1000, 500, 100, 50, 10, 5,  1};  // divisors 
 * 
 * The concept of "Zero" did not exist in Europe for a long time; thus, there is no 
 * roman numeral symbol for "Zero". The lowest number you can create from Roman 
 * Numerals is number 1 = I. 
 * 
 * The biggest number is 3999 = MMMCMXCIX, because there is no letter for number 
 * 5000 and number 4000 would be created as M (letter for 1000) and the letter 
 * for 5000.
 * 
 */

#define MAX_ROMAN 3999

int roman2base10(char roman_digit);
int chk_for_valid_roman_digit(char roman_digit);
int chk_for_valid_roman_num(char *p);
int getRomanNumber(char *p);
int toBase10fromRoman(char *p);
void replace(char * o_string, char * s_string, char * r_string);
int searchAndReplace(char *p);
int getRomansFromBase10(int dividend, int divisor, int *quotient, int *remainder);
int toRomanFromBase10(int base10, char *roman);
int add2Romans(char *b, char *a, char *result);
int subtract2Romans(char *b, char *a, char *result);

#endif /* ROMANCALC_H */

