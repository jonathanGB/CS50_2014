/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>
#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
 
 void sort(int values[], int n)
{
    int j;
    int k;

    for (int i = 0; i<n ; i++)
    {
    
    int min = values[i];
    
        for (j = i+1; j< n+1; j++) 
        {
            if (values[j] < min)
            {
                min = values[j];
                k = j;
            }
            
        }
    
        if (min != values[i])
        {
            values[k] = values[i];
            values[i] = min;
        }        
    }
}
bool search(int value, int values[], int n)
{
    int max = n;
    int min = 0;
    int length = (max - min) + 1;
    int midpoint = length / 2;
    int count = 0;
    int limit = log (n) + 2; // corresponding to big o of binary search, plus 2 for lack of precision
    
        while (length > 0 && count < limit) 
        {

            if(value > values[midpoint])
            {             
                min = midpoint + 1;
                
                if (min > n)
                {
                    break;
                }
                else if (length > min)
                {
                    length = length - min;
                }
                else
                {
                    length = min - length;
                }
                
                
                if (length/2 == 0) 
                {
                    midpoint = midpoint + 1;
                }
                else
                {
                midpoint = midpoint + (length/2);
                }
            }
            
            else if(value < values[midpoint])
            {
                max = midpoint - 1;
                
                if (max < 0)
                {
                    break;
                }
                length = max + 1;
                
                if (length/2 == 0) 
                {
                    midpoint = midpoint -1;
                }
                else
                {
                midpoint = midpoint - (length/2);
                }
            }
            
            else
            {
                return true;
            }
            
            count++;
          
            }
 
            return false;
}


