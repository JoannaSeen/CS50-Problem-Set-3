// Implements a dictionary's functionality

#include <stdbool.h>
#include<string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include "dictionary.h"
int sum_of_word;
int a;

//set at zero meaning false
int success_loading_dictionary = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



//Defining Hashtable size
#define HASHTABLE_SIZE 65536;

// Number of buckets in hash table
const unsigned int N = HASHTABLE_SIZE;



// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //make a temporary pointer called cursor
    for (node *cursor = table[(hash(word))]; cursor != NULL; cursor = cursor -> next)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
//Hash Function obtained from : https://gist.github.com/yangrq1018/e769abd7489ea8f52351b30829796a15
//Another website where the same hash function was found : https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char lower_case[LENGTH + 1];
        lower_case[i] = tolower(word[i]);
        hash = (hash << 2) ^ lower_case[i];
    }
    return hash % HASHTABLE_SIZE;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        sum_of_word = 0;
        char word[LENGTH + 1];
        {
            while (fscanf(file, "%s", word) != EOF)
            {

                node *n = malloc(sizeof(node));

                if (n != NULL)
                {
                    strcpy(n -> word, word);
                    n -> next = NULL;
                    a = hash(word);
        
                    if (table[a] != NULL)
                    {
                        n -> next = table[a];
                        table[a] = n;
                    }

                    else
                    {
                        table[a] = n;
                    }

                    sum_of_word = sum_of_word + 1;
                }

            }

        }
    }
    success_loading_dictionary = 1;
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (success_loading_dictionary == 1)
    {
        return sum_of_word;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Loop through every single hash list
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];

            while (cursor != NULL)
            {
                node *tmp = cursor;
                cursor = cursor -> next;
                free(tmp);
            }

        }
    }
    return true;
}
