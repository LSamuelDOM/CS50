# TODO

# I made almost the same code as on c, to compare every code command, I can do it with less lines, by using some new codes that has in python.
# Like i used, in line
# Main Function
def main():

    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


# Function used to count each letter in text, return letters.
def count_letters(text):

    letters = 0
    length = len(text)
    text = text.lower()

    for letter in range(length):
        if text[letter] >= 'a' and text[letter] <= 'z':
            letters += 1

    return letters


# Function used to count each word in text, return words
def count_words(text):
    words = 0
    space = " "
    length = text.count(space)
    while length != 0:
        words += 1
        length -= 1

    if words > 0:
        words += 1
    return words


# Function used to count each sentence in text, return sentences.
def count_sentences(text):
    sentences = 0
    length = len(text)
    sentences_mark = ('.', '!', '?')
    for sentence in range(length):
        if text[sentence] in sentences_mark:
            sentences += 1

    return sentences


# Call main function.
main()