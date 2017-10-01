#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //check that there is 1 command-line argument
    if (argc != 2)
    {
        fprintf(stderr,"You must input 1 command-line argument.");
        return 1;
    }


    // open memory card file and make sure not NULL
    FILE *memory_file = fopen(argv[1], "r");
    if (memory_file == NULL)
    {
        fprintf(stderr, "Your input file cannot be opened for reading.\n");
        return 2;
    }


    //use buffer for storage
    unsigned char buffer[512];

    //initialize count of jpeg files as 0
    int jpeg_count = 0;
    //initialize new_file
    FILE *jpeg_file = NULL;
    //declare a string for the jpeg file's name
    char jpeg_name[8];



    //read into buffer & repeat until we reach end of memory card file
    while (fread(buffer, 1, 512, memory_file) == 512)
    {
        //if we're at beginning of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //if found a jpeg before, close out current one
            if (jpeg_count != 0)
            {
                fclose(jpeg_file);
            }

            //otherwise, open a new JPEG, w filename: ###.jpg
            sprintf(jpeg_name, "%03i.jpg", jpeg_count);
            jpeg_file = fopen(jpeg_name, "w");
            jpeg_count ++;
        }

        if (jpeg_count > 0)
        {
            fwrite(buffer, 1, 512, jpeg_file);
        }
    }

    fclose(memory_file);
    fclose(jpeg_file);

    return 0;

}