/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // We want to shut down the program if the amount of arguments isn't equal to 2 or isn't equal to 3.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // We transform the "n" string into an integer.
    int n = atoi(argv[1]);

    // If there's a [s] argument, we want the seed to be the number typed by the user, by transforming the argv[2] string into an integer.
    // If there's not a [s] argument, the seed will simply be the time registred by the internal clock at a particular moment, which is pseudorandom.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // We want to print n pseudorandom numbers that can't exceed LIMIT, which is defined to be 65536.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // that's all folks
    return 0; 
}
