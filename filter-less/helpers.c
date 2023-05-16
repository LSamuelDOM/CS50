#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables for grayscale
    int color_buffer;

    // Grayscale process
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy the average of red with green and blue, and pass it to color_buffer, after that pass the buffer to every rgb pixel.
            color_buffer = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = color_buffer;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables for sepia
    int originalRed;
    int originalGreen;
    int originalBlue;

    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    // Sepia process
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gets original rgb value.
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // Execute sepia math to get the correct color.
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // If any of rgb color pass 255, will be set as 255.
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

            // Set sepia color to original image.
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables for Reflect
    int pixel[3];

    // Refect process
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half = round(width / 2); j < half; j++)
        {
            // Copy left side pixel to temp varible.
            pixel[0] = image[i][width - (j + 1)].rgbtRed;
            pixel[1] = image[i][width - (j + 1)].rgbtGreen;
            pixel[2] = image[i][width - (j + 1)].rgbtBlue;

            // Copy right side pixel to left side.
            image[i][width - (j + 1)].rgbtRed = image[i][j].rgbtRed;
            image[i][width - (j + 1)].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - (j + 1)].rgbtBlue = image[i][j].rgbtBlue;

            // Copy temp varible value to right side.
            image[i][j].rgbtRed = pixel[0];
            image[i][j].rgbtGreen = pixel[1];
            image[i][j].rgbtBlue = pixel[2];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables for blur
    RGBTRIPLE blur_img[height][width];

    float rgb[3];
    float counter = 0;

    // Blur process
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset every variable.
            counter = 0;
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;

            // Start the blur box process.
            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    // Ignore every value that pass the border.
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }

                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }

                    // Copy all near pixels colors to rgb variable.
                    rgb[0] += image[i + row][j + col].rgbtRed;
                    rgb[1] += image[i + row][j + col].rgbtGreen;
                    rgb[2] += image[i + row][j + col].rgbtBlue;
                    counter++;
                }
            }

            // Save a copy of original image with blur effect.
            blur_img[i][j].rgbtRed = round(rgb[0] / counter);
            blur_img[i][j].rgbtGreen = round(rgb[1] / counter);
            blur_img[i][j].rgbtBlue = round(rgb[2] / counter);
        }
    }

    // Pass the correct colors to original image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy all pixels from blur img to image.
            image[i][j].rgbtBlue = blur_img[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blur_img[i][j].rgbtGreen;
            image[i][j].rgbtRed = blur_img[i][j].rgbtRed;
        }

    }
    return;
}
