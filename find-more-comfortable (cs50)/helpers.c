/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int first_index = 0;
    int last_index = n - 1;
    int middle_index;
    while (first_index <= last_index)
    {
        middle_index = floor ((first_index + last_index) / 2);
        if (values[middle_index] == value)
        {
            return true;
        }
        else if (values[middle_index] < value) 
        {
            first_index = middle_index + 1;
        }
        else if (values[middle_index] > value)
        {
            last_index = middle_index - 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    int counting_sort_array[65536] = {0};
    for (int i = 0; i < n ; i++)
    {
         counting_sort_array[(values[i])] = counting_sort_array[(values[i])] + 1;
    }
    
    int k = -1;
    
    for (int j = 0; j < 65536 ; j++)
    {
        while (counting_sort_array[j] > 0)
        {
            k++;
            
            values [k] = j;
            counting_sort_array[j]--;
        }
    }
    
    
    return;
}
