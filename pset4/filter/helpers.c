#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float a = image[i][j].rgbtRed;
            float b = image[i][j].rgbtGreen;
            float c = image[i][j].rgbtBlue;
            float d = ((a + b + c) / 3);
            int e = round(d);
            image[i][j].rgbtRed = e;
            image[i][j].rgbtGreen = e;
            image[i][j].rgbtBlue = e;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float a = image[i][j].rgbtRed;
            float b = image[i][j].rgbtGreen;
            float c = image[i][j].rgbtBlue;
            int red = (int) round((0.393 * a) + (0.769 * b) + (0.189 * c));
            int green = (int) round((0.349 * a) + (0.686 * b) + (0.168 * c));
            int blue = (int) round((0.272 * a) + (0.534 * b) + (0.131 * c));
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

            if (red > 255 || blue > 255 || green > 255)

            {
                if (red > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

                if (green > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }


                if (blue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        //temporary file to store the value of the a
        for (int j = 0; j < floor(width / 2); j++)

        {

            //Red,a
            int temp1 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][(width - 1) - j].rgbtRed = temp1;


            //Green,b
            int temp2 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][(width - 1) - j].rgbtGreen = temp2;


            //Blue,c
            int temp3 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][(width - 1) - j].rgbtBlue = temp3;
        }
    }

    return;

}
// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    //for each of the pixel in terms of height of the array
    for (int i = 0; i < height; i++)
    {
        //for each of the pixel in terms of width of the array
        for (int j = 0; j < width; j++)
        {
            float sum_of_squares = 0.0;
            int sum_red = 0;
            int sum_blue = 0;
            int sum_green = 0;
            int average_red = 0;
            int average_blue = 0;
            int average_green = 0;
            //loop left and right
            for (int a = -1; a < 2; a++)
            {
                //loop top and bottom
                for (int b = -1; b < 2; b++)
                {
                    if ((i + a >= 0) && (i + a < height) && (b + j >= 0) && (b + j < width))
                    {
                        sum_of_squares = sum_of_squares + 1;
                        float c = temp[i + a][b + j].rgbtRed;
                        float d = temp[i + a][b + j].rgbtGreen;
                        float e = temp[i + a][b + j].rgbtBlue;
                        sum_red = sum_red + c;
                        sum_green = sum_green + d;
                        sum_blue = sum_blue + e;
                    }
                }
            }

            average_red = round(sum_red / sum_of_squares);
            image[i][j].rgbtRed = average_red;
            average_green = round(sum_green / sum_of_squares);
            image[i][j].rgbtGreen = average_green;
            average_blue = round(sum_blue / sum_of_squares);
            image[i][j].rgbtBlue = average_blue;
        }
    }
    return;
}



