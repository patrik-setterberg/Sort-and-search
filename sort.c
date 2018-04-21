/*
SORT by Patrik Setterberg, 2018

A mostly useless program written as an exercise which sorts a set of INTEGERS
using several different sorting algorithms.

* Can sort data in ascending or descending order.
* Takes input from file** specified as command line argument (see USAGE below)
* Options to output data either to console or file: FILENAME_sorted.txt
* Option to search for a number in file.
* Displays limited statistics after sorting.
* Logs results of sorting in a log file (sort_log.txt).

INCLUDED SORTING ALGORITHMS
* Bubble Sort
* Selection Sort
* Insertion Sort
* Merge Sort

USAGE
Execute program as follows: ./sort yourfile.txt
Follow instructions in console

** INPUT FILE NOTES
Program accepts any number (up to INT_MAX = 2147483647) of integers, positive or negative,
from specified .txt file. File may only contain integers, negative signs (-), spaces, tabs and
line-breaks; no letters or symbols are allowed. List of integers may contain duplicates.

Unsorted list of numbers for testing purposes in numbers.txt (100 numbers),
many_numbers.txt (2,000 numbers), and so_many_numbers.txt (10,000 numbers)
generated at https://www.random.org/
*/

#include "header.h"

char *numfile, *outfilename; // extern declared in header.h
char *sorted_suffix = "_sorted.txt";
double search_time; // extern declared in header.h
FILE *fp;
int filename_len, int_count = 0, j = 0, order, sort_choice;
int errmsg; // see log.c for error messages
int search_choice, search_number, search_result = 0;


int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>.txt\n", argv[0]);
        return 1;
    }

    // Attempt to open file
    numfile = argv[1];
    fp = fopen(numfile, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        errmsg = 0;
        err_log(errmsg);
        return 2;
    }

    /* Check file content for illegal characters, numbers sizes
       and count number of integers in file. */
    int_count = check_file(fp);
    if (int_count == 0)
    {
        errmsg = 1;
        err_log(errmsg);
        fclose(fp);
        return 3;
    }

    // Set name for output file
    outfilename = NULL;
    filename_len = strlen(numfile) - 4; // discards ".txt"
    outfilename = malloc(filename_len + SUFFIX_LEN);
    memcpy(outfilename, numfile, filename_len);
    outfilename[filename_len] = '\0';
    strcat(outfilename, sorted_suffix);


    // Initialize array for numbers
    int numbers[int_count];

    // Fill array with numbers
    while (fscanf(fp, "%d", &numbers[j]) > 0)
    {
        j++;
    }

    // Close file
    fclose(fp);

    printf("Welcome to Sort!\n");
    printf("================\n\n");

    // Get desired order (ascending or descending)
    order = get_order();

    // List algorithm choices
    list_algs();

    sort_choice = get_sort_choice();

    // Prompt user for choice of algorithm and call appropriate sorting function
    if (sort(numbers, int_count, sort_choice) == 1)
    {
        printf("Data sorted successfully!\n");
        printf("\nWould you like to search for a number?\n");
        printf("1. Yes\n");
        printf("2. No\n");
    }
    else
    {
        errmsg = 2;
        err_log(errmsg);
        fprintf(stderr, "ERROR: Sorting failed.\n");
        return 4;
    }

    // Search
    do
    {
        search_choice = get_input();

        switch(search_choice)
        {
            // Get number to search for, send it to search
            case 1:
                printf("\nWhat number would you like to find?\n");

                search_number = get_input();

                // Timer for statistics
                clock_gettime(CLOCK_MONOTONIC_RAW, &search_start);

                search_result = search(search_number, numbers, int_count);

                clock_gettime(CLOCK_MONOTONIC_RAW, &search_end);

                // Calculate time required to search
                search_time = (search_end.tv_nsec - search_start.tv_nsec) / 1000000000.0 +
                        (search_end.tv_sec  - search_start.tv_sec);
                break;

            // If user doesn't want to search for number, break out and move on
            case 2:
                break;

            default:
                printf("Choice must be 1 or 2.\n");
        }
    }
    while (search_choice != 1 && search_choice != 2);

    // Output sorted data, either to console or to file
    output(numbers, int_count, outfilename, order);

    free(outfilename);

    if(search_result > 0)
    {
        switch(search_result)
        {
            case 1:
                printf("Number found! %d is in %s.\n\n", search_number, argv[1]);
                break;
            case 2:
                printf("Could not find number %d in file %s.\n\n", search_number, argv[1]);
                break;
        }
    }

    // Print some basic statistics
    statistics(numbers, int_count, sort_choice, search_choice);

    // Log results in log file
    write_log(int_count, sort_choice, sort_time, search_number, search_result, search_time);

    return 0;
}

