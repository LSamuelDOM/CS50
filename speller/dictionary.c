// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
FILE *dictionary_file;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *check;
    int hash_info = hash(word);
    int valid = 0;
    check = table[hash_info];

    while (check != NULL)
    {
        if (strcasecmp(check->word, word) == 0)
        {
            check = NULL;
            free(check);
            return true;
        }
        check = check->next;
    }
    check = NULL;
    free(check);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[0] > 96)
    {
        return word[0] - 'a';
    }
    else
    {
        return word[0] - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    dictionary_file = fopen(dictionary, "r");
    if (dictionary_file != NULL)
    {
        char word[LENGTH + 1];
        int initialization[N] = {0};
        int hash_info;

        for (int nmb = 0; nmb < N; nmb++)
        {
            table[nmb] = NULL;
        }

        while (fscanf(dictionary_file, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            hash_info = hash(word);

            strcpy(n->word, word);
            n->next = table[hash_info];
            table[hash_info] = n;
        }
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    node *counter;
    int size_dic = 0;
    for (int i = 0; i < N; i++)
    {
        counter = table[i];
        while (counter != NULL)
        {
            counter = counter->next;
            size_dic++;
        }
    }
    return size_dic;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (dictionary_file != NULL)
    {
        node *cursor;
        node *tmp;

        for (int i = 0; i < N; i++)
        {
            cursor = table[i];
            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
        }
        free(cursor);
        fclose(dictionary_file);
        return true;
    }

    return false;
}
