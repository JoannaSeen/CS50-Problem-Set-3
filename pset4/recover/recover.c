#include <stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <cs50.h>

bool is_valid_file_to_recover(char *image);
typedef uint8_t BYTE;
//Defining the buffer size
BYTE buffer [512];
//Defining the filename size
char filename[8];
//Rmb to declare img as global variable so that we can close the file
FILE *img;
int jpeg_found_previously = 0;



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        if (argc == 1)
        {
            printf("./recover image\n");
            return 1;
        }
    }

    if (!is_valid_file_to_recover(argv[1]))
    {
        return 1;
    }

    return 0;

}

bool is_valid_file_to_recover(char *image)
{
    int file_number = 0;
    FILE *file = fopen(image, "r");
    {
        if (file == NULL)
        {
            printf("Unable to open file\n");
            return false;
        }
        while (fread(&buffer, sizeof(BYTE), 512, file) == 512)
        {
            //For the start of the 1st jpeg
            //Check for first 4 bytes of the "image"
            if (buffer [0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
                sprintf(filename, "%03i.jpg", file_number);
                //if not the first jpeg file, have to close it first to open a new file to copy it into it
                if (file_number != 0)
                {
                    fclose(img);

                }
                //regardless of the first or subsequent jpeg file, have to open a new file to copy it into it
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                file_number = file_number + 1;
                jpeg_found_previously = 1;

            }
            else
            {
                //if the next jpeg of 512 bytes is not a new jpeg it is a continuation of the previous jpeg, continue writing to the same new file
                if (jpeg_found_previously == 1)
                {
                    fwrite(&buffer, sizeof(BYTE), 512, img);
                }
            }

        }
        fclose(img);
        fclose(file);
        return true;
    }
}
