/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f(0,100] infile outfile\n");
        return 1;
    }
    
    // checking for resize factor
    if (atoi (argv[1]) <= 0 || atoi (argv[1]) > 100) // (0, 100] meaning excluding 0 to including 100
    {
        fprintf (stderr, "Usage: .resize f(0,100] infile outfile. f should be a floating point value.\n");
        return 2;
    }

    // remember filenames and factors to be resized
    int f = atoi (argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    /*bftype contains ASCII = "BM" or decimal =6677 or hexadecimal = 0x424d to make sure it is a BMP file.
      bfOffBits is (14 + 40) = 54 for a 24 bit BMP file which is used only for bmp.h by BITMAPFILEHEADER & BITMAPINFOHEADER
      biSize = 40 for the BMP file used in bmp.h by the struct BITMAPINFOHEADER
      biBitCount = 24 for 24 bit BMP as RGB 
      biCompression = 0 for uncompressed file*/
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int input_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
   int input_width = bi.biWidth;
   int input_height = bi.biHeight;
    
    //updating header files width and height for output
    bi.biWidth = ceil (bi.biWidth * f);
    bi.biHeight = ceil (bi.biHeight * f);
    
     //dettermine padding for scanlines of output file
    int output_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //updating rest of header files for output 
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + output_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(input_height); i < biHeight; i++)
    {
        for (float scale_height = 0; scale_height < f; scale_height++)
        {
            // skip over padding, if any
            fseek(inptr, (54 + ((input_width * sizeof(RGBTRIPLE) + input_padding) * i)), SEEK_SET);
            
            // iterate over pixels in scanline
            for (int j = 0; j < input_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                //resizing horizontal pixels by f factor
                for (float scale_width = 0; scale_width < f; scale_width++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < output_padding; k++)
            {
                fputc(0x00, outptr);
            } 
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
