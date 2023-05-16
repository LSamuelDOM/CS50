#include <cs50.h>
#include <stdio.h>

// My functions declared
void is_valid_card(unsigned long credit_card);
bool is_luhn(unsigned long card_num);
string is_brand(unsigned long card_num);
int num_length(unsigned long card_num);

// Main function
int main(void)
{
    // My credit card variable (I did it as unsigned, because i will only work with positive numbers as card number).
    unsigned long credit_card;

    // Will check if user input is valid.
    do
    {
        credit_card = get_long("Number: ");
    }
    while (credit_card < 0);

    // Will start my function is_valid_card with credit_card as parameter.
    is_valid_card(credit_card);
}

// Here is the most important function, because using it will call the others one.
void is_valid_card(unsigned long credit_card)
{

    int len = num_length(credit_card);
    bool luhn = is_luhn(credit_card);
    string brand = is_brand(credit_card);

    if (len == 13 && luhn == 1)
    {
        printf("%s\n", brand);
    }
    else if (len == 15 && luhn == 1)
    {
        printf("%s\n", brand);
    }
    else if (len == 16 && luhn == 1)
    {
        printf("%s\n", brand);
    }
    else
    {
        printf("INVALID\n");
    }
}

// This function will check if the card number(aka num) is right, using Luhn’s Algorithm.
bool is_luhn(unsigned long card_num)
{
    int sum = 0;

    for (int i = 0; card_num != 0; i++, card_num /= 10)
    {
        if (i % 2 == 0)
        {
            sum += card_num % 10;
        }
        else
        {
            int num = 2 * (card_num % 10);
            sum += num / 10 + num % 10;
        }
    }

    return (sum % 10) == 0;
}

// This function is used to return a brand to my brand variable in is_valid_card function.
// The function works with a simple concept, using numbers like 5e12, where we have a beginning with 5 and 12 digits after that.
string is_brand(unsigned long card_num)
{
    if ((card_num < 5e12 && card_num >= 4e12) || (card_num < 5e15 && card_num >= 4e15))
    {
        return "VISA";
    }
    else if ((card_num < 35e13 && card_num >= 34e13) || (card_num < 38e13 && card_num >= 37e13))
    {
        return "AMEX";
    }
    else if (card_num < 56e14 && card_num >= 51e14)
    {
        return "MASTERCARD";
    }
    else
    {
        return "INVALID";
    }
}

// This function is used to get the length of user credit card input, by dividing by ten until get 0.
int num_length(unsigned long card_num)
{
    int len;
    for (len = 0; card_num != 0; len++)
    {
        card_num /= 10;
    }
    return len;
}