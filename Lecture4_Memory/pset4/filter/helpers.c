/*
./filter -g infile.bmp outfile.bmp //grayscale
./filter -s infile.bmp outfile.bmp //sepia
./filter -r infile.bmp outfile.bmp //reflect
./filter -b infile.bmp outfile.bmp //blur
*/

#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /* From Original Picture, take avg value of Red, Blue and Green
       then set Red, Blue and Green to that avg value.
       Make sure the avg value is an integer
    */
    for (int w=0; w < width; w++)
    {
        for (int h=0; h < height; h++)
        {

            int avgPixelValue = round(((float)image[h][w].rgbtBlue
                                     + (float)image[h][w].rgbtGreen
                                     + (float)image[h][w].rgbtRed) / 3);
            image[h][w].rgbtBlue  = (avgPixelValue);
            image[h][w].rgbtGreen = (avgPixelValue);
            image[h][w].rgbtRed   = (avgPixelValue);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
        Valid values 0<= x <= 255
    */
    float sepiaBlue;
    float sepiaGreen;
    float sepiaRed;
    for (int h=0; h < height; h++)
    {
        for (int w=0; w < width; w++)
        {
            sepiaBlue   = 0.393*image[h][w].rgbtRed + 0.769*image[h][w].rgbtGreen + 0.189*image[h][w].rgbtBlue;
            sepiaGreen  = 0.349*image[h][w].rgbtRed + 0.686*image[h][w].rgbtGreen + 0.168*image[h][w].rgbtBlue;
            sepiaRed    = 0.272*image[h][w].rgbtRed + 0.534*image[h][w].rgbtGreen + 0.131*image[h][w].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtBlue  = round(sepiaRed);
            image[h][w].rgbtGreen = round(sepiaGreen);
            image[h][w].rgbtRed   = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width/2; w++)
        {
            RGBTRIPLE temp      = image[h][w];
            image[h][w]         = image[h][width-w-1];
            image[h][width-w-1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE avgValue[height][width];
    for (int h=0; h < height; h++)
    {
        for (int w=0; w < width; w++)
        {
            float sumBlue  = 0.00;
            float sumRed   = 0.00;
            float sumGreen = 0.00;
            float counter  = 0.00;

            for (int hPad=-1; hPad<2; hPad++)
            {
                // If out of index, don't add
                if ((h+hPad < 0) || (h+hPad > height-1))
                {
                    continue;
                }
                for (int wPad=-1; wPad<2; wPad++)
                {
                    // If out of index, don't add
                    if ((w+wPad < 0) || (w+wPad > width-1))
                    {
                        continue;
                    }
                    // Sum each color if index exists
                    sumBlue  += image[h+hPad][w+wPad].rgbtBlue;
                    sumRed   += image[h+hPad][w+wPad].rgbtRed;
                    sumGreen += image[h+hPad][w+wPad].rgbtGreen;
                    // Keep count
                    counter++;
                }
            }
            // Take average of each color
            avgValue[h][w].rgbtBlue  = round(sumBlue/counter);
            avgValue[h][w].rgbtRed   = round(sumRed/counter);
            avgValue[h][w].rgbtGreen = round(sumGreen/counter);
        }
    }
    // Set the calculated blur values and assign to image
    for (int h=0; h < height; h++)
    {
        for (int w=0; w < width; w++)
        {
            image[h][w].rgbtBlue  = avgValue[h][w].rgbtBlue;
            image[h][w].rgbtRed   = avgValue[h][w].rgbtRed;
            image[h][w].rgbtGreen = avgValue[h][w].rgbtGreen;

        }
    }
    return;
}