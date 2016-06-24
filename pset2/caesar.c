#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, string argv[])
{
    if (argc != 2)
    {
        printf("usage: ./caesar positive key \n");
        return 1;
    }

    //key is second command line
    int key = atoi(argv[1]);
    string plntxt = GetString();

    for (int i = 0, n = strlen(plntxt); i < n; i++)
    {
        if (isalpha(plntxt[i]))
        {
            if (isupper(plntxt[i]))
            {
                int ascii = plntxt[i] - 65;
                int cipher = (ascii + key) % 26;
                int alpha = cipher + 65;
                printf("%c", alpha);
            }
            else if (islower(plntxt[i]))
            {
                int ascii = plntxt[i] - 97;
                int cipher = (ascii + key) % 26;
                int alpha = cipher + 97;
                printf("%c", alpha);
            }
        } 
        else 
            printf("%c", plntxt[i]);
    } 
    printf("\n");
}
