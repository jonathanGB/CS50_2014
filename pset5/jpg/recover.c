/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define BLOCK 512 

int main(int argc, char* argv[])
{
    // initialization of constants and variables
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK];
    int count = 0;
    char title[8];
    int hundreds = 0;
    int tens = 0;
    int units = 0;
    
    // open the flash card file
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }
    
    // looking for the first jpg
    while(true)
    {
       fread(&buffer, BLOCK, 1, inptr);
       
       if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
       {
            break;
       }
    }
    
    // writing the first BLOCK of the first jpg
    FILE* outptr = fopen("000.jpg", "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create the outfile.\n");
        return 3;
    }    
    fwrite(&buffer, BLOCK, 1, outptr);
    
    // main loop
    while(true)
    {
        // EOF?
        if(fread(&buffer, BLOCK, 1, inptr) == 0)
        {
            fclose(inptr);
            fclose(outptr);
            break;
        }
        
        // beginning of a new jpg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            fclose(outptr);
            count++;
            
            // decompose the number and create the new jpg title
            hundreds = count / 100;
            tens = count / 10;
            units = count % 10;
            
            sprintf(title, "%i%i%i.jpg", hundreds, tens, units);
            
            
            outptr = fopen(title, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create the outfile.\n");
                return 3;
            }    
        }
        
        fwrite(&buffer, BLOCK, 1, outptr);
    }
}
