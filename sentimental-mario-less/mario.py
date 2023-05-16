# TODO

# Main function
def main():
    # Variables
    space = " "
    block = "#"
    inp = 0

    # While input isn't valid
    while (inp < 1 or inp > 8):
        try:
            inp = int(input("Height: "))
        except ValueError:
            print("Wrong input, use only int numbers!")

    # Copy input value to height
    height = inp

    # Will print every block and space on grid
    for n in range(height):
        # For space
        for s in range(inp - 1):
            print(space, end="")
        # For block
        for b in range(n + 1):
            print(block, end="")
        print("")
        inp -= 1


main()