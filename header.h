/*
HEADER.H by Patrik Setterberg, 2018

Header file for Sort
See sort.c for more information
*/

#ifndef HEADER_H
#define HEADER_H

#define ALG_COUNT 4 // Number or sorting algorithms the program can use
#define INT_MAX_LEN 12 // number of digits in limit.h's INT_MIN & INT_MAX (10 + 1 for newline + 1 for negative sign)
#define NEGATIVE_SIGN 45 // ascii for "-", allow for negative numbers
#define SUFFIX_LEN 12 // Length of "_sorted.txt" + 1 (for null terminator)
#define _POSIX_C_SOURCE 199309L // For time.h, declaration of clock_gettime()?

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct timespec sort_start, sort_end, search_start, search_end;

extern double sort_time; // defined in helpers.c
extern double search_time; // defined in sort.c
extern char *numfile, *outfilename; // defined in sort.c

static const char *algs[] = {"Bubble", "Insertion", "Merge", "Selection"};
static const char *time_complexity[] = {"n²", "n²", "n log n", "n²"};


/* SORTING ALGORITHMS */
/*
Bubble Sort
*/
void bubble_sort(int values[], int n);

/*
Insertion Sort
*/
void insertion_sort(int values[], int n);

/*
Merge Sort
*/
void merge_sort(int values[], int left, int right);

/*
Selection Sort
*/
void selection_sort(int values[], int n);

/*
Merge subarrays
*/
void merge(int numbers[], int left, int mid, int right);


/* HELPER FUNCTIONS */
/*
Check file
*/
int check_file(FILE* file);

/*
Check Number Size
*/
bool check_num_size(char *string);

/*
Get input from user
*/
int get_input();

/*
Get order
*/
int get_order();

/*
Get Sort Choice
*/
int get_sort_choice();

/*
List sorting algorithms
*/
void list_algs();

/*
Output data
*/
void output(int numbers[], int int_count, char *outfilename, int order);

/*
Print to console
*/
void print_to_console(int numbers[], int int_count, int order);

/*
Print to File
*/
void print_to_file(int numbers[], int int_count, int order, char *outfilename);

/*
Search
*/
int search(int value, int numbers[], int int_count);

/*
Sort data
*/
int sort(int numbers[], int int_count, int sort_choice);

/*
Swap
*/
void swap(int*, int*);


/* LOGGING */
/*
Error log
*/
void err_log(int errmsg);

/*
Open log
*/
bool open_log(void);

/*
Print time
*/
void print_time(FILE *log_file);

/*
Write log
*/
void write_log(int int_count, int sort_choice, double sort_time, int search_number, int search_result, double search_time);


/* STATISTICS */
/*
Get duplicates
*/
int get_duplicates(int numbers[], int int_count);

/*
Most frequent
*/
void most_freq(int numbers[], int int_count);

/*
Statistics
*/
void statistics(int numbers[], int int_count, int sort_choice, int search_choice);

#endif
