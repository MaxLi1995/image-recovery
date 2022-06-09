#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int const_size = 512;
//takes 1 argument which is the input file
int main(int argc, char *argv[])
{
    //promt the user if not entered commandline argument properly
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //open your file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //since you are going to write multiple file, keep track using i
    int i = 0;
    bool opened = false;
    // make space for string ***.jpg in memory
    char file_name[8];
    FILE *output;
    uint8_t block[const_size];
    //loop over your file 512 btye at a time
    while (fread(block, const_size, 1, file))
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
        {
            // if opened then close and start a new output file
            if (opened)
            {
                fclose(output);
            }
            sprintf(file_name, "%03i.jpg", i);
            output = fopen(file_name, "w");
            opened = true;
            i++;
        }
        //continue writing if already writing
        if (opened)
        {
            fwrite(&block, const_size, 1, output);
        }
    }
    //close your file and output file
    fclose(file);
    fclose(output);
}