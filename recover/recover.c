#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    FILE *image = NULL;
    // Create a buffer for a block of data
    uint8_t buffer[512];
    char filename[8] = {'0'};
    int counter = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (image != NULL)
            {
                fclose(image);
            }
            sprintf(filename, "%03i.jpg", counter);
            image = fopen(filename, "w");
            counter++;
        }
        if (image != NULL)
        {
            fwrite(buffer, 1, 512, image);
        }
    }
    fclose(image);
    fclose(card);
}
