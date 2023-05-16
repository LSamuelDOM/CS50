import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    STR = []
    database = []

    # TODO: Read database file into a variable
    with open(sys.argv[1], newline='') as database_file:
        reader = csv.DictReader(database_file)
        for row in reader:
            database.append(row)

    str_list = list(database[0].keys())
    str_list.remove('name')

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        sequence = sequence_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    for str_index in range(len(str_list)):
        current_str = longest_match(sequence, str_list[str_index])
        STR.append(current_str)

    # TODO: Check database for matching profiles
    for person in range(len(database)):
        match = 0
        for str_type in str_list:
            if int(database[person][str_type]) == STR[str_list.index(str_type)]:
                match += 1

        if match == len(STR):
            print(database[person]['name'])
            exit(0)

    print("No match")
    exit(1)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
