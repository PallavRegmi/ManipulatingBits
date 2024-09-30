/* 
 * CS:APP Data Lab 
 * 
 * Pallav Regmi 101909797
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

/*
 * bitCount - returns the count of number of 1's in a 32-bit word.
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Approach:
 *     - We use a mask to select specific bits from the word, then sum the number of 1s in small groups
 *       (such as every 4 bits). This reduces the problem step by step.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // mask to select every fourth bit: 0001000100010001 (hex: 0x11) repeated for all bits
    int mask1 = 0x11 | (0x11 << 8);
    // create a mask that extends to all 32 bits
    int mask2 = mask1 | (mask1 << 16);
    
    // Apply the mask and shift bits to sum groups of 4 bits
    int sum = x & mask2;
    sum += (x >> 1) & mask2;
    sum += (x >> 2) & mask2;
    sum += (x >> 3) & mask2;

    // Add upper and lower 16 bits together
    sum = sum + (sum >> 16);

    // Prepare another mask to add groups of 4 bits (nibbles)
    mask1 = 0xF | (0xF << 8);
    
    // Sum the nibbles (4 bits each)
    sum = (sum & mask1) + ((sum >> 4) & mask1);
    
    // Final sum in 6 bits, return the result
    return (sum + (sum >> 8)) & 0x3F;
}

/*
 * bitNor - returns ~(x | y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Approach:
 *     - Apply De Morgan's law: ~(x | y) is equivalent to ~x & ~y.
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    // De Morgan's law: ~(x | y) = ~x & ~y
    return ~x & ~y;
}

/*
 * byteSwap - swaps the nth byte and the mth byte of a 32-bit word.
 *   Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *             byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *   Approach:
 *     - Extract the nth and mth bytes by shifting them to the lowest 8 bits.
 *     - Clear the positions of nth and mth bytes in the original number.
 *     - Swap the extracted bytes into each other's positions.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 2
 */
int byteSwap(int x, int n, int m) {
    // Calculate the shift amount for nth and mth bytes (8 bits per byte)
    int n_shift = n << 3; 
    int m_shift = m << 3; 

    // Extract the nth and mth bytes by shifting and masking with 0xFF
    int n_byte = (x >> n_shift) & 0xFF;
    int m_byte = (x >> m_shift) & 0xFF;

    // Create a mask to clear the nth and mth byte positions in x
    int mask = (0xFF << n_shift) | (0xFF << m_shift);
    
    // Clear the nth and mth bytes, then place the swapped bytes
    x = x & ~mask; // clear bytes
    return x | (n_byte << m_shift) | (m_byte << n_shift); // swap and set bytes
}

/*
 * ezThreeFourths - multiplies a number by 3/4 and rounds toward 0.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *   Approach:
 *     - Multiply the number by 3 using (x << 1) + x.
 *     - Apply a bias to handle rounding correctly for negative numbers.
 *     - Divide by 4 using a right shift.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    // Multiply by 3: (x * 3) = (x << 1) + x
    int mul3 = (x << 1) + x;

    // Calculate bias for negative numbers to round toward zero
    int bias = (mul3 >> 31) & 3;

    // Divide by 4 with rounding toward zero
    return (mul3 + bias) >> 2;
}

/*
 * float_abs - Returns bit-level equivalent of the absolute value of a floating-point number.
 *   Both the argument and result are passed as unsigned int's, but they represent
 *   floating-point values.
 *   When the argument is NaN, the original value is returned.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&, if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    // Mask to clear the sign bit (keeps everything else)
    unsigned mask = 0x7FFFFFFF;

    // Apply mask to get the absolute value
    unsigned absVal = uf & mask;

    // NaN check: NaN has exponent bits all set to 1 and a non-zero fraction
    unsigned NaN = 0x7F800000;
    if (absVal > NaN) {
        return uf; // Return original value if NaN
    }

    return absVal;
}

/*
 * float_neg - Returns bit-level equivalent of the negation of a floating-point number.
 *   Both the argument and result are passed as unsigned int's, but they represent
 *   floating-point values.
 *   When the argument is NaN, the original value is returned.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&, if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    // Mask to clear the sign bit
    unsigned mask = 0x7FFFFFFF;

    // NaN check: NaN has exponent bits all set to 1 and a non-zero fraction
    unsigned NaN = 0x7F800000;
    unsigned negated = uf ^ 0x80000000; // Toggle the sign bit

    // Return original value if NaN
    if ((uf & mask) > NaN) {
        return uf;
    }

    return negated;
}

/*
 * isAsciiDigit - Returns 1 if the integer corresponds to an ASCII digit (0x30 <= x <= 0x39).
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *   Approach:
 *     - Calculate if x is within the range [0x30, 0x39] by comparing to the bounds.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // Check if x is greater than or equal to 0x30 (48)
    int lowerBound = x + (~0x30 + 1); // x - 0x30

    // Check if x is less than or equal to 0x39 (57)
    int upperBound = 0x39 + (~x + 1); // 0x39 - x

    // Return 1 if x is within range, otherwise 0
    return !(lowerBound >> 31) & !(upperBound >> 31);
}

/*
 * isPositive - Returns 1 if x is positive, 0 otherwise.
 *   Example: isPositive(-1) = 0.
 *   Approach:
 *     - Check if the sign bit is 0 and the number is non-zero.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // Check if the sign bit is 0 (non-negative) and x is not zero
    return !(x >> 31) & !!x;
}