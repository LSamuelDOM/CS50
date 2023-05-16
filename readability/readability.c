#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Functions prototype
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// Main
int main(void)
{
    // Get user input
    string text = get_string("Text: ");

    // Call three functions and store their returns
    int a = count_letters(text);
    int b = count_words(text);
    int c = count_sentences(text);

    float L = ((float)a / (float)b) * 100;
    float S = ((float)c / (float)b) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // Check if grade is more than 16 or less than 1, or will print the grade number
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Count letters in the text parameter
int count_letters(string text)
{
    int letters = 0;
    int lenght = strlen(text);
    for (int i = 0; i < lenght; i++)
    {
        // If the char in text[i] is upper will apply lower
        if (isupper(text[i]))
        {
            text[i] = tolower(text[i]);
        }
        // Counter
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
    }
    return letters;
}

// Count words in the text parameter
int count_words(string text)
{
    int words = 0;
    int space = 32;
    int lenght = strlen(text);
    // Spaces counter
    for (int i = 0; i < lenght; i++)
    {
        if (text[i] == space)
        {
            words++;
        }
    }

    // If it has a word in the input it will add a word, that's because we don't have a space at the end of the last word
    if (words > 0)
    {
        words++;
    }
    return words;
}

// Count sentences in the text parameter
int count_sentences(string text)
{
    int sentences = 0;
    int lenght = strlen(text);
    for (int i = 0; i < lenght; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}