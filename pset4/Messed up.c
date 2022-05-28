#include "helpers.h"
#include <math.h>
#include <stdio.h>

int sum_for_red(int a,int b);
int sum_for_green(int a, int b);
int sum_for_blue(int a, int b);


int edges_red(int a,int b, int i, int j, RGBTRIPLE image[i][j]);
int edges_green(int a,int b, int i, int j, RGBTRIPLE image[i][j]);
int edges_blue(int a, int b, int i, int j, RGBTRIPLE image[i][j]);

int border_red_3_2_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j]);
int border_green_3_2_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j]);
int border_blue_3_2_matrix(int a, int b, int i , int j, RGBTRIPLE image[i][j]);

int border_red_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j]);
int border_green_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j]);
int border_blue_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j]);

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


                if (image[i][j].rgbtBlue > 255)
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
    for (int i = 0; i < height; i++)
   {
        for (int j = 0; j < width; j++)
        {
            //accounting for the 4 squares at the edges
            if (i == 0 && j == 0)
            {
                int a = i;
                int b = j;
                int sum = 0;
                edges_red(a, b, i, j);
                edges_green(a, b, i, j, image[i][j]);
                edges_blue(a, b, i ,j, image[i][j]);
            }
            if (i == height - 1 && j == 0)
            {
                int x = i - 1;
                int y = j;
                int sum = 0;
                edges_red(x, y, i, j, image[i][j]);
                edges_green(x, y, i, j, image[i][j]);
                edges_blue(x, y, i, j, image[i][j]);
            }
            if (i == (height -1) && j == (width - 1))
            {
                int e = i -1;
                int f = j-1;
                int sum = 0;
                edges_red(e, f, i, j);
                edges_green(e, f, i, j);
                edges_blue(e, f, i, j);

            }
            if (i == 0 && j == (width -1))
            {
                int g = i - 1;
                int h = j - 1;
                int sum = 0;
                edges_red(g, h, i ,j, image[i][j]);
                edges_green(g, h, i, j, image[i][j]);
                edges_blue(g, h, i, j, image[i][j]);
            }

            else
            {   //accounting for the squares along the border excluding the square edges
                if ((i == 0 && j > 0) || (j = (width - 1) && i > 0) || ( i == (height - 1) && j > 0) || (j == 0 && i > 0 ))
                {
                    // 3 x 2 matrix
                    if (i == 0 && j > 0)
                    {
                        int a = i;
                        int b = j - 1;
                        float sum = 0;
                        border_red_3_2_matrix(a, b, i, j);
                        border_green_3_2_matrix(a, b, i, j);
                        border_blue_3_2_matrix(a, b, i, j);
                    }
                    // 2 x 3 matrix
                    if (j == width - 1 && i > 0)
                    {
                        int c = i - 1;
                        int d = j - 1;
                        float sum = 0;
                        border_red_2_3_matrix(c, d, i, j, image[i][j]));
                        border_green_2_3_matrix(c, d, i, j, image[i][j]));
                        border_blue_2_3_matrix(c, d, i, j, image[i][j]));
                    }
                    // 3 x 2 matrix
                    if (i == height - 1 && j > 0)
                    {
                        int e = i - 1;
                        int f = j - 1;
                        float sum = 0;
                        border_red_3_2_matrix(e, f, i, j, image[i][j]);
                        border_green_3_2_matrix(e, f, i, j, image[i][j]);
                        border_blue_3_2_matrix(e ,f, i, j, image[i][j]);

                    }
                    // 2 x 3 matrix
                    if (j == 0 && i > 0)
                    {
                        int g = i - 1;
                        int h = j;
                        float sum = 0;
                        border_red_2_3_matrix(g, h, i, j, image[i][j]);
                        border_green_2_3_matrix(g, h, i, j, image[i][j]);
                        border_blue_2_3_matrix(g, h, i, j, image[i][j]);
                    }

                }
                //accounting for those squares NOT along the border
                else
                {
                    int a = i - 1;
                    int b = j - 1;
                    float sum = 0;
                    sum_for_red(a,b,i,j, image[i][j]));
                    sum_for_green(a,b,i,j, image[i][j]));
                    sum_for_blue(a,b,i,j, image[i][j]));

                }

            }
        }


    }
    return;
}


int sum_for_red(int a,int b, int i, int j, RGBTRIPLE image[i][j])
{

    for (int x = a ; x < a + 2 ; x++)
    {
        for (int y = b; y < b + 2 ; y++ )
        {
            int c = image[a][b].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/9));
    image[i][j].rgbtRed = average_of_sum;
    return image[i][j].rgbtRed;
}

int sum_for_green(int a,int b, int i, int j, RGBTRIPLE image[[i][j])
{

    for (a = i - 1 ; a < i + 2 ; a++)
    {
        for (b = j - 1; b < j + 2 ; b++ )
        {
            int c = image[a][b].rgbtGreen;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/9));
    image[i][j].rgbtGreen = average_of_sum;
}

int sum_for_blue(int a,int b, int i, int j, RGBTRIPLE image[i][j])
{

    for (a = i - 1 ; a < i + 2 ; a++)
    {
        for (b = j - 1; b < j + 2 ; b++ )
        {
            int c = image[a][b].rgbtBlue;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/9));
    image[i][j].rgbtBlue = average_of_sum;
    return image[i][j].rgbtBlue;
}

int edges_red(int a,int b, int i, int j, RGBTRIPLE image[[i][j])
{
  for (a = i ; a < i + 2 ; i++)
    {
        for (b = j; b < j + 2; j++)
        {
            int c = image[a][b].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/4));
    image[i][j].rgbtRed = average_of_sum;
    return image[i][j].rgbtRed;
}

int edges_green(int a,int b, int i, int j, RGBTRIPLE image[i][j])
{
  for (a = i ; a < i + 2 ; i++)
    {
        for (b = j; b < j + 2; j++)
        {
            int c = image[a][b].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/4));
    image[i][j].rgbtGreen = average_of_sum;
    return image[i][j].rgbtGreen;
}

int edges_blue(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (a = i ; a < i + 2 ; i++)
    {
        for (b = j; b < j + 2; j++)
        {
            int c = image[a][b].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/4));
    image[i][j].rgbtBlue = average_of_sum;
    return image[i][j].rgbtBlue;
}

int border_red_3_2_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (int x = a ; x < a + 2 ; x++)
    {
        for (int y = b; y < b + 3 ; y++)
        {
            int c = image[x][y].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].rgbtRed = average_of_sum;
    return image[i][j].rgbtRed;
}

int border_green_3_2_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (int x = a ; x < a + 2 ; x++)
    {
        for (int y = b; y < b + 3 ; y++)
        {
            int c = image[x][y].rgbtGreen;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].rgbtGreen = average_of_sum;
    return image[i][j].rgbtGreen;
}

int border_blue_3_2_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (int x = a ; x < a + 2 ; x++)
    {
        for (int y = b; y < b + 3 ; y++)
        {
            int c = image[x][y].rgbtBlue;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].Blue = average_of_sum;
    return image[i][j].rgbtBlue;
}

int border_red_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (int x = a; x < a + 3; x ++)
    {
        for (int y = b; y < b + 2 ; y++)
        {
            int c = image[x][y].rgbtRed;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].Red = average_of_sum;
    return image[i][j].rgbtRed;
}



int border_green_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    for (int x = a; x < a + 3; x ++)
    {
        for (int y = b; y < b + 2 ; y++)
        {
            int c = image[x][y].rgbtGreen;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].Green = average_of_sum;
    return image[i][j].rgbtGreen;
}

int border_blue_2_3_matrix(int a, int b, int i, int j, RGBTRIPLE image[i][j])
{
    {
    for (int x = a; x < a + 3; x ++)
    {
        for (int y = b; y < b + 2 ; y++)
        {
            int c = image[x][y].rgbtBlue;
            sum = sum + c;
        }
    }
    int average_of_sum = round ((sum/6.0));
    image[i][j].Blue = average_of_sum;
    return image[i][j].rgbtBlue;
    }

}