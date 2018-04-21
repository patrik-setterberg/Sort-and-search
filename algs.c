/*
algs.c by Patrik Setterberg, 2018

Sorting algorithms and search for sort.c
See sort.c for more information.
*/

#include "header.h"

/*
Search - Perform a binary search for user-specified number.
*/
int search(int value, int numbers[], int int_count)
{
    int start = 0, end = int_count-1, mid;

    /* Check if middle element is sought number,
    otherwise adjust search area and try again */
    do

    {
        mid = end - ((end - start) / 2);
        if (numbers[mid] == value)
        {
            // Number found
            return 1;
        }
        else if (value < numbers[mid])
        {
            end = mid-1;
        }
        else if (value > numbers[mid])
        {
            start = mid+1;
        }

    }
    while(end >= start);

    // Number not found
    return 2;
}


/* SORTING ALGORITHMS */
/*
Bubble Sort - Step through list, swaps adjacent values if in wrong order,
              continues until no more swaps are needed.
*/
void bubble_sort(int values[], int n)
{
    int swap_count = 1, i;

    do
    {
        swap_count = 0;

        // Iterate through list
        for (i = 0; i < n - 1; i++)
        {
            // Compare current value with the value next to it.
            // If they're in wrong order, swap them and increase swap counter
            int *a = &values[i], *b = &values[i+1];
            if (values[i] > values[i+1])
            {
                swap(a,b);
                swap_count++;
            }
        }
    }
    while (swap_count != 0); // If no swaps are needed, sorting is done.

    return;
}

/*
Insertion Sort - In one move through array, pull out current value, shift values
                 to make room if necessary and place value in sorted sublist.
*/
void insertion_sort(int numbers[], int int_count)
{
    int i, j, temp;

    for (i = 1; i < int_count; i++)
    {
        temp = numbers[i]; // Copy current number into temp var
        j = i - 1;

        while (j >= 0 && numbers[j] > temp)
        {
            numbers[j + 1] = numbers[j];
            j--;
        }

        // Place number in temp into its position in sorted portion of array.
        numbers[j + 1] = temp;
    }

    return;
}

/*
Merge Sort - Recursively split array into smaller subarrays, sort and then merge subarrays.
             Credit for function logic to https://www.geeksforgeeks.org/merge-sort/
             I am not smart enough.
*/
void merge_sort(int numbers[], int left_ind, int right_ind)
{
    if (left_ind < right_ind)
    {
        // Set middle index
        int mid = left_ind + (right_ind - left_ind) / 2;

        // Sort halves
        merge_sort(numbers, left_ind, mid);         // left half
        merge_sort(numbers, mid + 1, right_ind);    // right half

        // Merge
        merge(numbers, left_ind, mid, right_ind);
    }

    return;
}

/*
Merge subarrays - Helper function for merge sort. Merges two subarray into one larger array.
                  Credit for function logic to https://www.geeksforgeeks.org/merge-sort/
                  I am not smart enough.
*/
void merge(int numbers[], int left, int mid, int right)
{
    int i, j, k;
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Temp arrays
    int l_arr[left_size], r_arr[right_size];

    // Copy numbers into temp arrays
    for (i = 0; i < left_size; i++)
    {
        l_arr[i] = numbers[left + i];
    }
    for (j = 0; j < right_size; j++)
    {
        r_arr[j] = numbers[mid + 1 + j];
    }

    // Set subarray indices for merging
    i = 0;
    j = 0;
    k = left;

    // Merge temp arrays into numbers[]
    while (i < left_size && j < right_size)
    {
        if (l_arr[i] <= r_arr[j])
        {
            numbers[k] = l_arr[i];
            i++;
        }
        else
        {
            numbers[k] = r_arr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining numbers from left temp array into numbers[]
    while(i < left_size)
    {
        numbers[k] = l_arr[i];
        i++;
        k++;
    }

    // Copy any remaining numbers from right temp array into numbers[]
    while (j < right_size)
    {
        numbers[k] = r_arr[j];
        j++;
        k++;
    }

    return;
}

/*
Selection Sort - Steps through list, looking for smallest value and
                 places it in sorted sublist until all items are sorted.
*/
void selection_sort(int values[], int n)
{
    int temp_min; // Temporary mininum (smallest value in unsorted sublist)
    int i, j;

    // Step through array and update left boundary (i)
    for (i = 0; i < n - 1; i++)
    {
        // Find lowest value in array
        temp_min = i;
        for (j = i + 1; j < n; j++)
        {
            if (values[j] < values[temp_min])
                temp_min = j;
        }

        // Swap smallest value with first value
        swap(&values[temp_min], &values[i]);
    }

    return;
}