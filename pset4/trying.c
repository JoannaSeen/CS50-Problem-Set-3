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
            float d = ((a + b + c )/3);
            int e = round (d);
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
            int red = (int) round ((0.393 * a) + (0.769 * b) + (0.189 * c));
            int green = (int) round ((0.349 * a) + (0.686 * b) + (0.168 * c));
            int blue = (int) round ((0.272 * a) + (0.534 * b) + (0.131 * c));
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
   //temporary file to store the value of the a
   {
        for (int j = 0; j < floor(width/2); j++)

        {

            //Red,a
            int temp1 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width-1)-j].rgbtRed;
            image[i][(width-1)-j].rgbtRed = temp1;


            //Green,b
            int temp2 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width-1)-j].rgbtGreen;
            image[i][(width-1)-j].rgbtGreen = temp2;


            //Blue,c
            int temp3 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width-1)-j].rgbtBlue;
            image[i][(width-1)-j].rgbtBlue = temp3;
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
            image[i][j].rgbtRed = 0;
            image[i][j].rgbtBlue = 0;
            image[i][j].rgbtGreen
        }
    }

    for (int i = 0; i < height; i++)
   {
        for (int j = 0; j < width; j++)
        {
            //accounting for the 1st left top of the 4 squares at the edges
            if (i == 0 && j == 0)
            {
                //2x2 matrix
                float sum_red1= 0;
                float sum_green1 = 0;
                float sum_blue1 = 0;
                for (int a = i ; a < 2 ; a++)
                {
                    for (int b = j; b < 2; b++)
                    {
                        //Summation of the 2x2 matrix for red
                        float c1 = temp[a][b].rgbtRed;
                        sum_red1 = sum_red1 + c1;
                        //Summation of the 2x2 matrix for green
                        float x1 = temp[a][b].rgbtGreen;
                        sum_green1 = sum_green1 + x1;
                        //Summation of the 2x2 matrix for blue
                        float y1 = temp[a][b].rgbtBlue;
                        sum_blue1 = sum_blue1 + y1;
                    }
                }
                //Assigning the average value of the sum to the red
                int average_of_sum_red1 = round ((sum_red1)/4.0);
                image[i][j].rgbtRed = average_of_sum_red1;
                //Assigning the average value of the sum to the green
                int average_of_sum_green1 = round ((sum_green1)/4.0);
                image[i][j].rgbtGreen = average_of_sum_green1;
                //Assigning the average value of the sum to the blue
                int average_of_sum_blue1 = round ((sum_blue1)/ 4.0);
                image[i][j].rgbtBlue = average_of_sum_blue1;

                if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                {
                    if (image[i][j].rgbtRed > 255)
                    {
                        image[i][j].rgbtRed = 255;
                    }

                    if (image[i][j].rgbtBlue > 255)
                    {
                    image[i][j].rgbtBlue = 255;
                    }


                    if (image[i][j].rgbtGreen > 255)
                    {
                        image[i][j].rgbtGreen = 255;
                    }
                }
            }
            //acounting for the 2nd left bottom of the 4 squares at the edges
            else if (i == (height - 1) && (j == 0))
            {

                //2x2 matrix
                float sum_red2 = 0;
                float sum_green2 = 0;
                float sum_blue2 = 0;

                for (int a = i - 1; a < i + 1; a++)
                {
                    for (int b = j ; b < j + 2 ; b++)
                    {
                        //Summation of the 2x2 matrix for red
                        float c2 = temp[a][b].rgbtRed;
                        sum_red2 = sum_red2 + c2;
                        //Summation of the 2x2 matrix for green
                        float x2 = temp[a][b].rgbtGreen;
                        sum_green2 = sum_green2 + x2;
                        //Summation of the 2x2 matrix for blue
                        float y2 = temp[a][b].rgbtBlue;
                        sum_blue2 = sum_blue2 + y2;
                    }
                }
                //Assigning the average value of the sum to the red
                int average_of_sum_red2 = round ((sum_red2)/4.0);
                image[i][j].rgbtRed = average_of_sum_red2;
                //Assigning the average value of the sum to the green
                int average_of_sum_green2 = round ((sum_green2)/4.0);
                image[i][j].rgbtGreen = average_of_sum_green2;
                //Assigning the average value of the sum to the blue
                int average_of_sum_blue2 = round ((sum_blue2)/ 4.0);
                image[i][j].rgbtBlue = average_of_sum_blue2;

                if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                {
                    if (image[i][j].rgbtRed > 255)
                    {
                        image[i][j].rgbtRed = 255;
                    }

                    if (image[i][j].rgbtBlue > 255 )
                    {
                    image[i][j].rgbtBlue = 255;
                    }


                    if (image[i][j].rgbtGreen > 255)
                    {
                        image[i][j].rgbtGreen = 255;
                    }
                }
            }
            //accounting for 3rd right bottom of the 4 squares at the edges
            else if (i == (height -1) && j == (width - 1))
            {
                //2x2 matrix
                float sum_red3 = 0;
                float sum_green3 = 0;
                float sum_blue3 = 0;

                for (int a = i - 1; a < i + 1 ; a++)
                {
                    for (int b = j - 1 ; b < j + 1 ; b++)
                    {
                        //Summation of the 2x2 matrix for red
                        float c3 = temp[a][b].rgbtRed;
                        sum_red3 = sum_red3 + c3;
                        //Summation of the 2x2 matrix for green
                        float x3 = temp[a][b].rgbtGreen;
                        sum_green3 = sum_green3 + x3;
                        //Summation of the 2x2 matrix for blue
                        float y3 = temp[a][b].rgbtBlue;
                        sum_blue3 = sum_blue3 + y3;
                    }
                }
                //Assigning the average value of the sum to the red
                int average_of_sum_red3 = round ((sum_red3)/4.0);
                image[i][j].rgbtRed = average_of_sum_red3;
                //Assigning the average value of the sum to the green
                int average_of_sum_green3 = round ((sum_green3)/4.0);
                image[i][j].rgbtGreen = average_of_sum_green3;
                //Assigning the average value of the sum to the blue
                int average_of_sum_blue3 = round ((sum_blue3)/ 4.0);
                image[i][j].rgbtBlue = average_of_sum_blue3;

                if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                {
                    if (image[i][j].rgbtRed > 255 )
                    {
                        image[i][j].rgbtRed = 255;
                    }

                    if (image[i][j].rgbtBlue > 255 )
                    {
                    image[i][j].rgbtBlue = 255;
                    }


                    if (image[i][j].rgbtGreen > 255)
                    {
                        image[i][j].rgbtGreen = 255;
                    }
                }
            }
            //accounting for 4th right top of the 4 squares at the edges
            else if (i == 0 && j == (width -1))
            {
                //2x2 matrix
                float sum_red4 = 0;
                float sum_green4 = 0;
                float sum_blue4 = 0;

                for (int a = i ; a  < 2; a++)
                {
                    for (int b = j - 1 ; b < j + 1 ; b++)
                    {
                        //Summation of the 2x2 matrix for red
                        float c4 = temp[a][b].rgbtRed;
                        sum_red4 = sum_red4 + c4;
                        //Summation of the 2x2 matrix for green
                        float x4 = temp[a][b].rgbtGreen;
                        sum_green4 = sum_green4 + x4;
                        //Summation of the 2x2 matrix for blue
                        float y4 = temp[a][b].rgbtBlue;
                        sum_blue4 = sum_blue4 + y4;
                    }
                }
                //Assigning the average value of the sum to the red
                int average_of_sum_red4 = round ((sum_red4)/4.0);
                image[i][j].rgbtRed = average_of_sum_red4;
                //Assigning the average value of the sum to the green
                int average_of_sum_green4 = round ((sum_green4)/4.0);
                image[i][j].rgbtGreen = average_of_sum_green4;
                //Assigning the average value of the sum to the blue
                int average_of_sum_blue4 = round ((sum_blue4)/ 4.0);
                image[i][j].rgbtBlue = average_of_sum_blue4;

                if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                {
                    if (image[i][j].rgbtRed > 255)
                    {
                        image[i][j].rgbtRed = 255;
                    }

                    if (image[i][j].rgbtBlue > 255)
                    {
                    image[i][j].rgbtBlue = 255;
                    }


                    if (image[i][j].rgbtGreen > 255)
                    {
                        image[i][j].rgbtGreen = 255;
                    }
                }
            }
            //accounting for the squares along the border excluding the 4 square edges
            else
            {
                if ((i == 0 && j > 0) || (j == (width - 1) && i > 0) || ( i == (height - 1) && j > 0) || (j == 0 && i > 0))
                {
                   // 3 x 2 matrix
                   //accounting for the squares along the border of the 1st top column excluding the 4 square edges
                    if (i == 0 && j > 0)
                    {
                        float sum_red5 = 0;
                        float sum_green5 = 0;
                        float sum_blue5 = 0;

                        for (int a = i; a < 2 ; a++)
                        {
                            for (int b = j - 1 ; b < 3 ; b++)
                            {
                               //Summation of the 3x2 matrix for red
                                float c5 = temp[a][b].rgbtRed;
                                sum_red5 = sum_red5 + c5;
                                //Summation of the 3x2 matrix for green
                                float x5 = temp[a][b].rgbtGreen;
                                sum_green5 = sum_green5 + x5;
                                //Summation of the 3x2 matrix for blue
                                float y5 = temp[a][b].rgbtBlue;
                                sum_blue5 = sum_blue5 + y5;
                            }
                        }
                        //Assigning the average value of the sum to the red
                        int average_of_sum_red5 = round ((sum_red5)/6.0);
                        image[i][j].rgbtRed = average_of_sum_red5;
                        //Assigning the average value of the sum to the green
                        int average_of_sum_green5 = round ((sum_green5)/6.0);
                        image[i][j].rgbtGreen = average_of_sum_green5;
                        //Assigning the average value of the sum to the blue
                        int average_of_sum_blue5 = round ((sum_blue5)/ 6.0);
                        image[i][j].rgbtBlue = average_of_sum_blue5;

                        if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                        {
                            if (image[i][j].rgbtRed > 255)
                            {
                                image[i][j].rgbtRed = 255;
                            }

                            if (image[i][j].rgbtGreen > 255)
                            {
                                image[i][j].rgbtGreen = 255;
                            }
                            if (image[i][j].rgbtBlue > 255)
                            {
                                image[i][j].rgbtBlue = 255;
                            }
                        }
                    }


                    // 2 x 3 matrix
                    //accounting for the squares along the border of the 1st most right row excluding the 4 square edges
                    else if (j == (width - 1) && i > 0)
                    {

                        float sum_red6 = 0;
                        float sum_green6 = 0;
                        float sum_blue6= 0;

                        for (int a = i - 1; a < i + 2 ; a++)
                        {
                            for (int b = j - 1 ; b < j + 1 ; b++)
                            {
                               //Summation of the 2x3 matrix for red
                                float c6 = temp[a][b].rgbtRed;
                                sum_red6 = sum_red6 + c6;
                                //Summation of the 2x3 matrix for green
                                float x6 = temp[a][b].rgbtGreen;
                                sum_green6 = sum_green6 + x6;
                                //Summation of the 2x3 matrix for blue
                                float y6 = temp[a][b].rgbtBlue;
                                sum_blue6 = sum_blue6 + y6;
                            }
                        }
                        //Assigning the average value of the sum to the red
                        int average_of_sum_red6 = round ((sum_red6)/6.0);
                        image[i][j].rgbtRed = average_of_sum_red6;
                        //Assigning the average value of the sum to the green
                        int average_of_sum_green6 = round ((sum_green6)/6.0);
                        image[i][j].rgbtGreen = average_of_sum_green6;
                        //Assigning the average value of the sum to the blue
                        int average_of_sum_blue6 = round ((sum_blue6)/ 6.0);
                        image[i][j].rgbtBlue = average_of_sum_blue6;


                        if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                        {
                            if (image[i][j].rgbtRed > 255)
                            {
                                image[i][j].rgbtRed = 255;
                            }

                            if (image[i][j].rgbtGreen > 255)
                            {
                                image[i][j].rgbtGreen = 255;
                            }

                            if (image[i][j].rgbtBlue > 255)
                            {
                                image[i][j].rgbtBlue = 255;
                            }
                        }

                    }
                     // 3 x 2 matrix
                    //accounting for the squares along the border of the last bottom column excluding the 4 square edges
                    else if (i == (height - 1) && j > 0)
                    {
                        float sum_red7 = 0;
                        float sum_green7 = 0;
                        float sum_blue7 = 0;

                        for (int a = i - 1; a < i + 1 ; a++)
                        {
                            for (int b = j - 1 ; b < j + 2 ; b++)
                            {
                               //Summation of the 3x2 matrix for red
                                float c7 = temp[a][b].rgbtRed;
                                sum_red7 = sum_red7 + c7;
                                //Summation of the 3x2 matrix for green
                                float x7 = temp[a][b].rgbtGreen;
                                sum_green7 = sum_green7 + x7;
                                //Summation of the 3x2 matrix for blue
                                float y7 = temp[a][b].rgbtBlue;
                                sum_blue7 = sum_blue7 + y7;
                            }
                        }
                        //Assigning the average value of the sum to the red
                        int average_of_sum_red7 = round ((sum_red7)/6.0);
                        image[i][j].rgbtRed = average_of_sum_red7;
                        //Assigning the average value of the sum to the green
                        int average_of_sum_green7 = round ((sum_green7)/6.0);
                        image[i][j].rgbtGreen = average_of_sum_green7;
                        //Assigning the average value of the sum to the blue
                        int average_of_sum_blue7 = round ((sum_blue7)/ 6.0);
                        image[i][j].rgbtBlue = average_of_sum_blue7;

                         if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                         {
                            if (image[i][j].rgbtRed > 255)
                            {
                                image[i][j].rgbtRed = 255;
                            }

                            if (image[i][j].rgbtGreen > 255)
                            {
                                image[i][j].rgbtGreen = 255;
                            }
                            if (image[i][j].rgbtBlue > 255)
                            {
                                image[i][j].rgbtBlue = 255;
                            }

                         }
                    }
                     // 2 x 3 matrix
                     //acounting for square along the border of the 1st left row excluding the 4 square edges
                    else if (j == 0 && i > 0 )
                    {
                        float sum_red8 = 0;
                        float sum_green8 = 0;
                        float sum_blue8 = 0;

                        for (int a = i - 1; a < i + 2 ; a++)
                        {
                            for (int b = j; b < j + 2 ; b++)
                            {
                               //Summation of the 2x3 matrix for red
                                float c8 = temp[a][b].rgbtRed;
                                sum_red8 = sum_red8 + c8;
                                //Summation of the 2x3 matrix for green
                                float x8 = temp[a][b].rgbtGreen;
                                sum_green8 = sum_green8 + x8;
                                //Summation of the 2x3 matrix for blue
                                float y8 = temp[a][b].rgbtBlue;
                                sum_blue8 = sum_blue8 + y8;
                            }
                        }
                        //Assigning the average value of the sum to the red
                        int average_of_sum_red8 = round ((sum_red8)/6.0);
                        image[i][j].rgbtRed = average_of_sum_red8;
                        //Assigning the average value of the sum to the green
                        int average_of_sum_green8 = round ((sum_green8)/6.0);
                        image[i][j].rgbtGreen = average_of_sum_green8;
                        //Assigning the average value of the sum to the blue
                        int average_of_sum_blue8 = round ((sum_blue8)/ 6.0);
                        image[i][j].rgbtBlue = average_of_sum_blue8;

                         if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                         {
                            if (image[i][j].rgbtRed > 255)
                            {
                                image[i][j].rgbtRed = 255;
                            }

                            if (image[i][j].rgbtGreen > 255)
                            {
                                image[i][j].rgbtGreen = 255;
                            }

                            if (image[i][j].rgbtBlue > 255)
                            {
                                image[i][j].rgbtBlue = 255;
                            }
                         }

                    }
                    //accounting for those squares NOT along the border excluding the 4 square edges
                    else
                    {
                        float sum_red9 = 0;
                        float sum_green9 = 0;
                        float sum_blue9 = 0;

                        for(int a = i - 1; a < j + 2; a++)
                        {
                            for (int b = j - 1; b < i + 2; b++)
                            {
                                //Summation of the 2x3 matrix for red
                                float c9 = temp[a][b].rgbtRed;
                                sum_red9 = sum_red9 + c9;
                                //Summation of the 2x3 matrix for green
                                float x9 = temp[a][b].rgbtGreen;
                                sum_green9 = sum_green9 + x9;
                                //Summation of the 2x3 matrix for blue
                                float y9 = temp[a][b].rgbtBlue;
                                sum_blue9 = sum_blue9 + y9;

                            }
                        }
                        //Assigning the average value of the sum to the red
                        int average_of_sum_red9 = round ((sum_red9)/9.0);
                        image[i][j].rgbtRed = average_of_sum_red9;
                        //Assigning the average value of the sum to the green
                        int average_of_sum_green9 = round ((sum_green9)/9.0);
                        image[i][j].rgbtGreen = average_of_sum_green9;
                        //Assigning the average value of the sum to the blue
                        int average_of_sum_blue9 = round ((sum_blue9)/ 9.0);
                        image[i][j].rgbtBlue = average_of_sum_blue9;


                         if (image[i][j].rgbtRed > 255 || image[i][j].rgbtBlue > 255 || image[i][j].rgbtGreen > 255)
                         {
                            if (image[i][j].rgbtRed > 255)
                            {
                                image[i][j].rgbtRed = 255;
                            }

                            if (image[i][j].rgbtGreen > 255)
                            {
                                image[i][j].rgbtGreen = 255;
                            }
                            if (image[i][j].rgbtBlue > 255)
                            {
                                image[i][j].rgbtBlue = 255;
                            }

                         }

                    }

                }
            }

        }
   }
   return;
}