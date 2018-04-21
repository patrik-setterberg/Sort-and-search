# Sort-and-search
Small number sorting program by Patrik Setterberg, 2018.

A mostly useless program written as an exercise which sorts a set of INTEGERS
using several different sorting algorithms.

* Can sort data in ascending or descending order.
* Takes input from file** specified as command line argument (see USAGE below)
* Options to output data either to console or file: FILENAME_sorted.txt
* Option to search for a number in file. (binary search)
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
