/*
log.c by Patrik Setterberg, 2018

Logging related functions for sort.c
See sort.c for more information.
*/

#include "header.h"

FILE *log_file;

/* Error messages */
char *err_msg[] =
{
    "Could not open file.\n",           // 0
    "Check file function failed.\n",    // 1
    "Sorting failed.\n",                // 2
    "Error reading input.\n",           // 3
    "Could not load output file.\n"     // 4
};


/*
Error log - Writes error message to log file.
*/
void err_log(int errmsg)
{
    // Open log file
    if(!open_log())
    {
        return;
    }

    print_time(log_file);
    fprintf(log_file, "Attempted to sort file %s.\n", numfile);
    fprintf(log_file, "Program failed to execute correctly. ERROR MESSAGE: %s\n", err_msg[errmsg]);
    fclose(log_file);

    return;
}

/*
Open log - Checks whether log file exists. If it doesn't, function creates it.
*/
bool open_log(void)
{
    // If log file cannot be read (it probably doesn't exist)
    if((log_file = fopen("sort_log.txt", "r")) == NULL)
    {
        // Create it (open in write mode)
        if((log_file = fopen("sort_log.txt", "w")) == NULL)
        {
            fprintf(stderr, "ERROR: Failed to create log file.\n");
            return false;
        }
        else
        {
            fprintf(log_file, "SORT LOG\n");
            fprintf(log_file, "========\n\n");
            fclose(log_file);
        }
    }
    else
    {
        fclose(log_file);
    }

    // Open log file (in append mode)
    if((log_file = fopen("sort_log.txt", "a")) == NULL)
    {
        fprintf(stderr, "Could not open log file.\n");
        return false;
    }

    return true;
}

/*
Print time - Prints current date and time into log file
*/
void print_time(FILE *log_file)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(log_file, "%d-%d-%d %02d:%02d:%02d - ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return;
}

/*
Write log - Opens sort_log.txt and logs (successful) program execution results.
*/
void write_log(int int_count, int sort_choice, double sort_time, int search_number, int search_result, double search_time)
{
    // Open log file
    if(!open_log())
    {
        return;
    }

    print_time(log_file);
    fprintf(log_file, "Successfully sorted numbers in %s.\n", numfile);
    fprintf(log_file, "Sorted %d numbers in %f seconds using %s Sort.\n", int_count, sort_time, algs[sort_choice-1]);

    // If search found a file
    if (search_result == 1)
    {
        fprintf(log_file, "Search found number %d in %f seconds.\n\n", search_number, search_time);
    }
    else if (search_result == 2)
    {
        fprintf(log_file, "Searched for number %d for %f seconds. Number could not be found.\n\n", search_number, search_time);
    }
    else
    {
        fprintf(log_file, "\n");
    }

    fclose(log_file);
    return;
}