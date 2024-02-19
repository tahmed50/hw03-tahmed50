# HW 03 - C Bit Field Utilities

## Introduction

The goal of this assignment is to:

- Learn about manipulating bits ("bit twiddling") in C
- Learning about the implementation of integer numbers, and how we can take advantage of that implementation to perform non-numeric tasks using integers.

We have learned that the C language uses *integer* data types to keep track of integer numbers, and that those integer data types are implemented as bit vectors using two's complement number representation. The length of the bit vector depends on which integer data type is used.

|Type|Length|
|:---:|  ----:|
|char| 8|
|short| 16 |
|int | 32 |
|long| 64 |

We typically use an integer variable to keep track of a single whole number. For this project, we will demonstrate that we can divide a bit vector into multiple fields, and provide utilities to extract or insert numbers into these bit fields using C bit twiddling techniques.

We can manage sub-fields using any integer data type, but we will concentrate on 64 bit long integers for this assignment. We will use the convention that a sub-field is described using

- The bit position of the most significant (leftmost) bit of the field within the 64 bit long integer bit vector,
- And the length of the field.

The bit positions starts at the rightmost, least significant bit (0), and count up to the leftmost, most significant bit, which is bit 63 for a long integer. For example, the bit field that starts at position 11 and has a length of 5 can be illustrated using the following table:

| 63 |62 | ... | 12 | 11 | 10 | 9 | 8 | 7 | 6 | ... | 2 | 1 | 0 |
|---|---|----|-|---|----|---|---|----|----|---|---|---|---|
| x | x | ...| x | 1 | 1| 0 | 1 | 0 | x | ... | x | x | x | x |

In this example, the sub-fields that starts at position 11 and has a length of 5 contains the value 0b11010, no matter what values are in the other bit positions (represented by *x*) in the rest of the 64 bit long integer.

That value may represent a five bit unsigned binary value of 16+8+2=26, or may represent a two's complement signed value of -6 (by flipping the bits and adding 1, -0b00110.) Our subfield utilities must support both interpretations.

For this homework, we will implement five C functions to manipulate bit fields within an unsigned long integer target variable:

- `int getBit(int bn,unsigned long val)` : extracts a single bit value at position bn from the target variable `val`, and returns an integer 0 or 1 depending on the value of the bn'th bit in val.
- `void setBit(int bn,int new,unsigned long *val)` : Sets the value of the `bn` bit in the target variable `val` to the value in `new`. The bn'th bit in val is set to 1 if new is non-zero, or 0 if new is zero.
- `long getBitFld(int bs,int len,unsigned long val)` : extracts a subfield starting at position `bs` for a length of `len` from the target variable `val` and returns a signed long integer that represents the result treated as a 64 bit signed two's complement value.
- `unsigned long getBitFldU(int bs,int len,unsigned long val)` : extracts a subfield starting at position `bs` for a length of `len` from the target variable `val` and returns an unsigned long integer that represents the result treated as a 64 bit unsigned binary number.
- `void setBitFld(int bs,int len,unsigned long new,unsigned long *val)` : inserts the value represented by the rightmost `len` bits of `new` (which may be signed or unsigned) into the unsigned long target pointed to by `val` starting at position `bs` for length `len`.

## Provided to you

This homework repository already contains some infrastructure to get you started, as follows:

### bitFields.h and bitFields.c

These files make up the bit-twiddling library. The bitFields.h file declares five functions described above whose definitions will eventually end up in bitFields.c

The definition of these functions is not complete. I have provided correct implementations of the `getField` and `setField` functions for you, but you must finish the code in bitFields.c by writing implementations for `getBitFld`, `getBitFldU`, and `setBitFld`.

### testBitFields.c

This is some code I have provided for you to unit test the bitFields functions. It uses the functions in the way they were intended, and prints results based on that usage. If there are bugs in the bitFields functions, running this code will print out obvious incorrect results in a way that should make it easy to debug.

### Makefile

I have provided a Makefile with several targets:

- `test` - run the testBitFields executable
- `gdb` - run gdb on the testBitFields executable.
- `testBitFields` - builds the testBitFields executable
- `clean` removes all the files Makefile can create

## Coding the project

After reading through this readme, complete the function definitions for the three undefined bitFields functions in bitFields.c, and then `make test` to see if you have everything correct.

## Hints and Suggestions

First, read through the Professors [How to Perform Bit Twiddling in C](https://www.cs.binghamton.edu/~tbartens/HowTo/Bit_Twiddle.html).

1. When bit twiddling, remember that a literal value is treated as a 32 bit integer **unless** it has an "L" suffix!

   I have spent hours and hours debugging code such as `(1<<pos & value)`, where `value` is a 64 bit (long) value, and `pos` is a position between 0 and 63. The bug is that `1<<pos` says shift a **32** bit value by `pos` bits. If `pos` is greater than 31, the result is undefined, which means the C compiler can put whatever it wants into the result! The correct code is `(1L<<pos & value)`.

2. The simplest solution to the get and set multiple bit field problem is to use the `setBit` and `getBit` functions to read and write a single bit at a time. You may use this solution and get full credit, but if you do so, you will miss out on the real benefit of this assignment, which is to learn how to bit twiddle. See the [How to Perform Bit Twiddling in C](https://www.cs.binghamton.edu/~tbartens/HowTo/Bit_Twiddle.html) for alternatives.

3. There are many correct answers to this problem. Any valid solution is acceptable.

## Submitting the Homework

When you have finished coding and testing your bitFields.c functions, make sure you do a final git commit and push to update your main git repository. Then, retrieve the 16 digit git hash code either from browsing your updated repository on the web, or using the command `git rev-parse HEAD` on the command line. Paste the git hash code in the Brightspace HW03 assignment. You may resubmit as many times as you would like to. Only the last submission will be graded.

## Grading Criteria

Your repository will be downloaded onto an LDAP machine at the level corresponding to the hash code retrieved from Brightspace, and compiled and run using the Makefile. Your code will be tested with the testBitFields.c program provided to you, and with an unpublished test program that performs similar tests. The results will be compared to correct results. The assignment is worth 10 points, and the following deductions will occur:

- -10 if your code matches or is significantly similar to any other student's code.
- -8 If your code does not attempt to address the problem.
- -8 if testBitFields does not compile
- Up to -4 if there are mismatches on the published test case
- Up to -4 points per test if there are incorrect results on the unpublished test case
- -1 if testBitFields produces warning  messages when compiled
- -1 if your repository contains any executable files
- -2 for each 24 hours (or part of 24 hours) the submission is late. After 5 days, there will be a -10 deduction.
