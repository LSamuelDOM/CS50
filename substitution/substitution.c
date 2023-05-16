#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Main
int main(int argc, string argv[])
{
    //
    string key = argv[1];

    // Check if has more than 2, or less than 2 args. Return 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if argv[1] has 26 chars. Return 1
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // If all until here is ok, the program start.
    else
    {
        // First thing is valid the key.
        for (int i = 0, lenght = strlen(argv[1]); i < lenght; i++)
        {
            // This if is most important thing to valid key, will check if isn't alpha and if is the same char as last one.
            if (!(isalpha(argv[1][i]) && argv[1][i] != argv[1][i - 1]))
            {
                printf("Error!, invalid key format!\n");
                return 1;
            }
        }

        // Here where the program really starts, if everything is ok.
        // Variable to store every char on user input.
        char letter;
        string text = get_string("plaintext: ");
        printf("ciphertext: ");

        // For will check if a text char is lower or upper, else will print it.
        for (int i = 0, lenght = strlen(text); i < lenght; i++)
        {
            letter = text[i];

            // If text char is lowercase will execute this block of codes.
            if (islower(letter))
            {
                letter = tolower(key[letter - 'a']);
            }
            // If text char is uppercase will execute this block of codes.
            else if (isupper(letter))
            {
                letter = toupper(key[letter - 'A']);
            }
            // At the end will print the letter.
            printf("%c", letter);
        }

        // This part just end the program with a new line, and return 0, that means everything is right.
        printf("\n");
        return 0;
    }
}