/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

#define HEADER_SIZE 54

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile scale\n");
        return 1;
    }
    
    int scale = atoi(argv[1]);
    int scaleLength = strlen(argv[1]);
    
    for (int i = 0; i < scaleLength; i++) // making sure the scale is actually a number
    {
            if (isdigit(argv[1][i]) == 0) {
                printf("Your last argument should be a number (the scale) !\n");
                return 1;
            } 
    }
    
    if (scale < 1 || scale > 100)
    {
        printf("You must insert a scale between 1 and 100 inclusively!\n");
        return 1;          
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi; 
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // save old header attributes
    int oPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oWidth = bi.biWidth;
    int oHeight = abs(bi.biHeight);
    int nPadding = oPadding;
    
    //change some header attributes according to the new dimension of the picture
    if (scale != 1)
    {
        bi.biWidth *= scale;
        bi.biHeight *= scale;
        nPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        bi.biSizeImage = (bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE)) + (nPadding * abs(bi.biHeight));
        bf.bfSize = bi.biSizeImage + HEADER_SIZE; 
    }
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0; i < oHeight; i++)
    {
        // iterate over scale
        for (int j = 0; j < scale; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < oWidth; k++) 
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile scale times
                for (int l = 0; l < scale; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add the new padding
            for (int m = 0; m < nPadding; m++)
            {
                fputc(0x00, outptr);
            }                     
                            
            // go back to the beginning of the scanline
            fseek(inptr, -(oWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
                          
        // skip over the last scanline + padding, if any
        fseek(inptr, ((oWidth * sizeof(RGBTRIPLE)) + oPadding), SEEK_CUR);     
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
