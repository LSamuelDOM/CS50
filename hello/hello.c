#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Here will get the user name using get_string command.
    string name = get_string("What's your name? ");
    // And Here will paste the name as string.
    printf("hello, %s\n", name);
}