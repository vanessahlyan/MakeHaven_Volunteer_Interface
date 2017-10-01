#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //make sure there are 3 command line arguments
    if (argc != 4)
    {
        fprintf(stderr, "You must input 3 command-line arguments.\n");
        return 1;
    }


    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];


    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Your enlargement factor n must be positive and less than 100.");
        return 2;
    }

    // open input file and make sure not NULL
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Your input file %s cannot be opened for reading.\n", infile);
        return 3;
    }

    // open output file and make sure not NULL
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create output file %s.\n", outfile);
        return 4;
    }


    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // check if infile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }


    //old dimensions
    int old_Width = bi.biWidth;
    int old_Height = bi.biHeight;

    //determine new dimensions
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int old_padding = (4 - (old_Width* sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine new image size
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    //write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //declare pixel_array for storage
    RGBTRIPLE *pixel_array = malloc(sizeof(RGBTRIPLE) * bi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_Height); i < biHeight; i++)
    {

        int pixel_array_index = 0;

        //iterate over pixels in each scanline of infile
        for (int j = 0; j < old_Width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //write RGB triple to pixel_array n times
            for (int horiz_count = 0; horiz_count < n; horiz_count++)
            {
                *(pixel_array + pixel_array_index) = triple;
                pixel_array_index ++;
            }
        }

        // skip over input file's padding
        fseek(inptr, old_padding, SEEK_CUR);

        //write pixel_array and padding to output file n times
        for (int vertical_count = 0; vertical_count < n; vertical_count++)
        {
            fwrite(pixel_array, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            //write padding to output file
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    //free memory from pixel_array
    free(pixel_array);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}
