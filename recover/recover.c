#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Global variables
int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if has two argcs, only two.
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // All variables.
    BYTE buffer[BLOCK_SIZE];
    char *filename = malloc(8 * sizeof(char));
    int digit = 0;
    int read = 0;

    // Open raw_file with argv name, and create a empty file.
    FILE *raw_file = fopen(argv[1], "r");
    FILE *img = NULL;

    // Try open raw_file.
    if (raw_file == NULL)
    {
        printf("Forensic file couldn't open %s\n", argv[1]);
        return 1;
    }

    // Process every BLOCK in raw_file.
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check if this block is a valid jpg.
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            // Create a new empty file using digit as name.
            sprintf(filename, "%03d.jpg", digit++);
            img = fopen(filename, "w");
        }

        // Write on empty file created above.
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    // Close last file.
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(raw_file);
    free(filename);

    return 0;
}