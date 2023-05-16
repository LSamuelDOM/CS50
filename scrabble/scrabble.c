#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Functions Prototype
int compute_score(string word);
void winner(int score1, int score2);

// Main Function
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Call winner function
    winner(score1, score2);

    return 0;
}

// Will get the score from each player
int compute_score(string word)
{
    // Function Variables
    int points = 0;
    int lenght = strlen(word);

    // For will repeat for each character on user input
    for (int i = 0, j = 0; i < lenght; i++)
    {
        // Check if the character is lowercase
        if (islower(word[i]))
        {
            word[i] = word[i] - 32;
        }

        // Only alphabetic letters will earn points, another kind of character will be ignored
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            j = word[i] - 'A';
            points = points + POINTS[j];
        }
    }
    return points;
}

// This function is used to check who wins (i used if's a lot, i have to find a way to possibly improve it)
void winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else if (score2 == score1)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Error!\n");
    }
}
