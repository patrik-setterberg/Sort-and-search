/*
statistics.c by Patrik Setterberg, 2018

Statistical functions for sort.c
See sort.c for more information.
*/

#include "header.h"

/*
Get duplicates - Counts and returns number of any duplicate numbers
*/
int get_duplicates(int numbers[], int int_count)
{
    int dupl_count = 0, i, j;

    for (i = 0; i < int_count; i++)
    {
        // From i + 1, check for duplicate and then break to make sure
        // no duplicates are counted more than once
        for (j = i + 1; j < int_count; j++)
        {
            if (numbers[i] == numbers[j])
            {
                dupl_count++;
                break;
            }
        }
    }

    return dupl_count;
}

/*
Most frequent - Finds and prints the most commonly occurring number in array as well as
                its occurrence count. If two values share maximum count of duplicates,
                only the first occurring value is printed.
*/
void most_freq(int numbers[], int int_count)
{
    int count, freq[int_count], i, j, k, most_freq_num, most_freq_count;

    // Fill frequency array with -1 for now
    for (i = 0; i < int_count; i++)
    {
        freq[i] = -1;
    }

    for (i = 0; i < int_count; i++)
    {
        // Set frequency to 1
        count = 1;

        for (j = i + 1; j < int_count; j++)
        {
            // If a duplicate is found
            if (numbers[i] == numbers[j])
            {
                count++;

                // Make sure to not count frequency for current number again
                freq[j] = 0;
            }
        }

        if(freq[i] != 0)
        {
            // Set frequency to number found by inner loop
            freq[i] = count;
        }
    }

    // Set most_frequent variables to first number
    most_freq_num = numbers[0];
    most_freq_count = freq[0];

    for (k = 1; k < int_count; k++)
    {
        // If current frequency is higher, update most_frequent variables
        if (freq[k] > most_freq_count)
        {
            most_freq_num = numbers[k];
            most_freq_count = freq[k];
        }
    }

    printf("Most frequent number: %d, occurring %d times.\n\n", most_freq_num, most_freq_count);

    return;
}

/*
Statistics - Prints number of integers that were sorted as well as
             how long time sorting and searching required to finish,
             smallest and largest values, median and mean.
             Also prints chosen sorting algorithm and its average-case time complexity.
*/
void statistics(int numbers[], int int_count, int sort_choice, int search_choice)
{
    float mean;
    int i;
    int dupl = 0; // Duplicate numbers in array
    long num_sum = 0;

    // Sum numbers in numbers[]
    for (i = 0; i < int_count; i++)
    {
        num_sum += numbers[i];
    }

    mean = num_sum / int_count;

    printf("Statistics\n");
    printf("==========\n");
    printf("Total count of numbers sorted: %d.\n\n", int_count);

    printf("Smallest value: %d. Largest value: %d.\n", numbers[0], numbers[int_count-1]);
    printf("Median value: %d. Mean value: %g.\n\n", numbers[(int_count-1) / 2], mean);

    // Check for duplicates. If found, print total count and most frequent number + occurrence count
    if((dupl = get_duplicates(numbers, int_count)) > 0)
    {
        printf("Total number of duplicate values: %d.\n", dupl);

        most_freq(numbers, int_count);
    }
    else
    {
        printf("No duplicate numbers found in file.\n\n");
    }

    // Print time required to sort list
    printf("Time required to sort list: %f seconds.\n", sort_time);

    // If user searched for a file, print time required to search
    if(search_choice == 1)
    {
        printf("Time required to search for number: %f seconds.\n\n", search_time);
    }
    else
    {
        printf("\n");
    }

    printf("Data sorted using %s Sort.\n", algs[sort_choice - 1]);
    printf("Average time complexity for algorithm: O(%s).\n", time_complexity[sort_choice - 1]);

    return;
}