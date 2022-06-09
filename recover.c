#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int const_size = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    int i = 0;
    bool opened = false;
    char file_name[9];
    FILE *output;
    uint8_t block[const_size];
    while (fread(block, const_size, 1, file))
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
        {
            if (opened)
            {
                fclose(output);
            }
            sprintf(file_name, "%03i.jpg", i);
            output = fopen(file_name, "w");
            opened = true;
            i++;
        }
        if (opened)
        {
            fwrite(&block, const_size, 1, output);
        }
    }
    fclose(file);
    fclose(output);
}