# TODO
from cs50 import get_float

# I made the code almost the same as in c problem, to understand how different is each command.
# I know i can solve it with less lines, but i want to repeat old cash.c as python.
# And to check if has a differece between the speed of python and c, as showed in class.


# Main Function
def main():

    # Call a function called get cents, return the user input
    cents = get_cents()

    # Call a function called calculate_quarters, return how much quarters is needed.
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Call a function called calculate_dimes, return how much dimess is needed.
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Call a function called calculate_nickels, return how much dimess is needed.
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Call a function called calculate_pennies, return how much pennies is needed.
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Will make a sum of all coins, and print it.
    sum_coins = quarters + dimes + nickels + pennies
    print(sum_coins)


# Will get and return user input.
def get_cents():

    cents = 0
    while cents <= 0:
        cents = get_float("Change owed: ")

    return int(cents * 100)


# Get cents as input, and return quarters.
def calculate_quarters(cents):
    quarters = 0
    while cents >= 25:
        cents -= 25
        quarters += 1

    return quarters


# Get cents as input, and return dimes.
def calculate_dimes(cents):
    dimes = 0
    while cents >= 10:
        cents -= 10
        dimes += 1

    return dimes


# Get cents as input, and return nickels.
def calculate_nickels(cents):
    nickels = 0
    while cents >= 5:
        cents -= 5
        nickels += 1

    return nickels


# Get cents as input, and return pennies.
def calculate_pennies(cents):
    pennies = 0
    while cents >= 1:
        cents -= 1
        pennies += 1

    return pennies


main()