/*
helpers.c by Patrik Setterberg, 2018

Functionality for sort.c
See sort.c for more information.
*/

#include "header.h"

int helpers_errmsg;
double sort_time; // extern defined in header.h

/* HELPER FUNCTIONS */
/*
Check File - Checks file's contents and formatting, ensuring only
             integers, negative signs (-), spaces, tabs or newline characters.
*/
int check_file(FILE *file)
{
    int d, i;
    long counter = 0;
    char num_store[INT_MAX_LEN];

    // Check all characters in file
    while ((d = fgetc(file)) > 0)
    {
        if (isdigit(d) || isspace(d) || d == NEGATIVE_SIGN)
        {
            continue;
        }
        else
        {
            fprintf(stderr, "ERROR: File contains non-integer: %c\n", d);
            return 0;
        }
    }

    rewind(file);

    // Count all integers in file
    while (fscanf(file, "%s", num_store) > 0)
    {
        if(!check_num_size(num_store))
        {
            fprintf(stderr, "ERROR: File contains number either too large or too small.\n");
            fprintf(stderr, "Allowed range: %d to %d.\n", INT_MIN, INT_MAX);
            return 0;
        }
        else
        {
            // Also check minus-sign formatting in file
            for (i = 0; i < strlen(num_store); i++)
            {
                if (isdigit(num_store[i]) && num_store[i+1] == NEGATIVE_SIGN)
                {
                    fprintf(stderr, "ERROR: Illegal number formatting detected.\n");
                    fprintf(stderr, "Number immediately followed by negative-sign, e.g. '12-'.\n");
                    return 0;
                }

                if (num_store[i] == NEGATIVE_SIGN && !isdigit(num_store[i+1]))
                {
                    fprintf(stderr, "ERROR: Illegal use of negative sign.\n");
                    fprintf(stderr, "Negative sign not succeeded by number, e.g. '- '.\n");
                    return 0;
                }
            }

            // Increase total number count.
            counter++;

            if(counter > INT_MAX)
            {
                fprintf(stderr, "ERROR: Too many numbers in file. Maximum allowed number count is %d.\n", INT_MAX); // Untested
                return 0;
            }
        }
    }

    rewind(file);

    if (counter == 0)
    {
        fprintf(stderr, "ERROR: Could not find any numbers to sort.\n");
        return 0;
    }

    return counter;
}

/*
Check Number Size - Checks if a number is within range of an integer.
*/
bool check_num_size(char *string)
{
    char *str_store;
    long number;

    number = strtol(string, &str_store, 10);

    if(number >= INT_MIN && number <= INT_MAX)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
Get input - Prompt user for a number response and returns it.
            Ensures no non-int input.
*/
int get_input()
{
    bool is_number;
    char string[1000]; // Big buffer to safeguard against overflow (if user inputs very high number)
    int num;


    do
    {
        // Number is a valid number until proven otherwise
        is_number = true;

        printf("Enter choice: ");

        // Get input from user
        if (fgets(string, sizeof(string), stdin) != NULL)
        {
            // Check string (number) length
            if (strlen(string) > INT_MAX_LEN)
            {
                printf("\nInput string too long.\n");
                is_number = false;
            }

            // Change EOL newline character to null terminator
            string[strlen(string) - 1] = '\0';

            // Check if first char of input is digit or minus sign
            if (!isdigit(string[0]) && string[0] != NEGATIVE_SIGN)
            {
                printf("\nOnly numbers allowed.\n");
                is_number = false;
            }

            // Check if remaining input is a number
            for (int i = 1; i < strlen(string); i++)
            {
                if (!isdigit(string[i]))
                {
                    printf("\nOnly numbers allowed.\n");
                    is_number = false;
                    break;
                }
            }
        }
        else
        {
            helpers_errmsg = 3;
            err_log(helpers_errmsg);
            fprintf(stderr, "Error reading input\n");
            exit(EXIT_FAILURE);
        }

        // Make sure number is larger than INT_MIN and smaller than INT_MAX
        if(!check_num_size(string) && is_number == true)
        {
            is_number = false;
            printf("\nNumber either too small or too large. Allowed range: %d to %d\n", INT_MIN, INT_MAX);
        }

    } while (!is_number);

    num = atoi(string);

    return num;
}

/*
Get order - Decide whether data should be printed in ascending
            or descending order.
*/
int get_order()
{
    int sorting_order = 0;

    printf("Sort data in ascending or descending order?\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");

    while (sorting_order != 1 && sorting_order != 2)
    {
        sorting_order = get_input();

        if(sorting_order != 1 && sorting_order != 2)
        {
            printf("\nChoice must be either 1 or 2.\n");
        }
        else
        {
            printf("\n");
            break;
        }
    }

    return sorting_order;
}

/*
Get Sort Choice - Queries user for choice of sorting algorithm.
*/
int get_sort_choice()
{
    int choice;

    do
    {
        // Get algorithm choice from user
        choice = get_input();
        printf("\n");

        // Upon unacceptable input, notify user and query again
        if (choice < 1 || choice > ALG_COUNT)
        {
            printf("Choice must be 1, 2, 3, or 4.\n");
        }

    } while (choice < 1 || choice > ALG_COUNT); // Repeat until appropriate answer provided

    return choice;
}

/*
List Choices - Prints available algorithms for sorting.
*/
void list_algs()
{
    printf("Please choose sorting algorithm:\n");

    for (int ch = 0; ch < ALG_COUNT; ch++)
    {
        printf("%d. %s Sort\n", ch+1, algs[ch]);
    }
    return;
}

/*
Output - Prompt user for choice of output: console or file
         and print sorted data.
*/
void output(int numbers[], int int_count, char *outfilename, int order)
{
    int outchoice;

    printf("\nPrint sorted data to:\n");
    printf("1. Console\n");
    printf("2. File\n");

    do
    {
        // Get choice from user
        outchoice = get_input();
        printf("\n");

        switch(outchoice)
        {
            // Print to console
            case 1:
                printf("Printing to console...\n\n");
                print_to_console(numbers, int_count, order);
                break;

            // Attempt to create output file and print into it
            case 2:
                printf("Printing to file: %s\n\n", outfilename);
                print_to_file(numbers, int_count, order, outfilename);
                break;

            default:
                printf("Choose either 1 to print to console or 2 to print to file.\n");
        }
    }
    while (outchoice != 1 && outchoice != 2);

    return;
}

/*
Print to console - Prints sorted data to console (stdout).
*/
void print_to_console(int numbers[], int int_count, int order)
{
    printf("Sorted list\n");
    printf("===========\n");

    switch(order)
    {
        // Ascending
        case 1:
            for (int m = 0; m < int_count; m++)
            {
                printf("%d\n", numbers[m]);
            }
            printf("\n");
            break;

        // Descending
        case 2:
            for (int m = int_count-1; m >= 0; m--)
            {
                printf("%d\n", numbers[m]);
            }
            printf("\n");
            break;
    }
    return;
}

/*
Print to file - Prints data to file filename_sorted.txt.
*/
void print_to_file(int numbers[], int int_count, int order, char *outfilename)
{
    int n;
    FILE *outfile = fopen(outfilename, "w");

    if (outfile == NULL)
    {
        helpers_errmsg = 4;
        err_log(helpers_errmsg);
        fprintf(stderr, "Could not load output file.\n");
        exit(EXIT_FAILURE);
    }

    switch(order)
    {
        // Ascending
        case 1:
            for (n = 0; n < int_count; n++)
            {
                fprintf(outfile, "%d\n", numbers[n]);
            }
            break;

        // Descending
        case 2:
            for (n = int_count-1; n >= 0; n--)
            {
                fprintf(outfile, "%d\n", numbers[n]);
            }
            break;
    }

    fclose(outfile);
    return;
}

/*
Sort - Prompt user for choice of sorting algorithm and call appropriate function.
*/
int sort(int numbers[], int int_count, int sort_choice)
{
    int i;

    // Timer for statistics
    clock_gettime(CLOCK_MONOTONIC_RAW, &sort_start);

    // Call sorting algorithm and break out of loop
    switch(sort_choice)
    {
        case 1:
            bubble_sort(numbers, int_count);
            break;
        case 2:
            insertion_sort(numbers, int_count);
            break;
        case 3:
            merge_sort(numbers, 0, int_count - 1);
            break;
        case 4:
            selection_sort(numbers, int_count);
            break;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &sort_end);

    // Calculate time required to sort
    sort_time = (sort_end.tv_nsec - sort_start.tv_nsec) / 1000000000.0 + (sort_end.tv_sec  - sort_start.tv_sec);

    // Check sorting
    for (i = 0; i < int_count-1; i++)
    {
        if(numbers[i] > numbers[i+1])
        {
            return 0;
        }

    }

    return 1;
}

/*
Swap - Swaps one value with another (swap index in array).
*/
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}