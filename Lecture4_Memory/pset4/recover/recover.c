/*  Pseudocode
    open memory card
    Repeat until end of card:
        Read 512 bytes into a buffer
        If start of a new JPEG
            If first JPEG
                start writing
            else
                close this JPEG before starting a new JPEG
        Else
            Keep writing to the same img
    close any remaining files*/
/* fread(data, size, number, inptr)
    data: pointer to where to store data you're reading
    size: size of each element to read
    number: number of elements to read
    inptr: FILE * to read from*/
/* fwrite(data, size, number, inptr)
    data: pointer to bytes that will be written to file
    size: size of each element to write
    number: number of elements to write
    inptr: FILE * to write to*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // 512-Byte Blocks, Looking into each Block
    // Look for the correct heading
    // then go to the next block
    int counter = 0;
    int yesJPEG = 0;
    unsigned char buffer[512];
    char filename[10];
    FILE *img = NULL;
    while (fread(&buffer, 512, 1, file))
    {
        // Write the First Headings
        // using JPEG signature for the first 4 Bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8
        &&  buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // bit-wise arithmetic
        {
            // Start a new JPEG
            if (yesJPEG == 0)
            {
                yesJPEG = 1;
            }
            // Else close the current img, and make a new one
            else if (yesJPEG == 1)
            {
                fclose(img);
                counter++;
                yesJPEG = 1;
            }
            sprintf(filename,"%03i.jpg",counter);
            img = fopen(filename, "w");
            fwrite(&buffer, 512, 1, img);
        }
        // Write the rest of the picture until
        // we find the JPEG signature again
        else if (yesJPEG==1)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    // Close files
    fclose(file);
    fclose(img);

    return 0;
}