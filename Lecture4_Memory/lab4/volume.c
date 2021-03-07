// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// ./volume input.wav output.wav 2.0
// uint8_t int16_t
typedef uint8_t BYTE;
typedef int16_t BIT;
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    BYTE heading[HEADER_SIZE];
    fread(&heading, HEADER_SIZE, 1, input);
    fwrite(&heading, HEADER_SIZE, 1, output);
    // TODO: Read samples from input file and write updated data to output file
    BIT samples;
    while (fread(&samples, 2, 1, input))
    {
        samples = samples * factor;
        fwrite(&samples, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
