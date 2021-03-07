// Implements a dictionary's functionality
// ./speller text
//./speller dictionaries/large text
// ./speller dictionaries/small text

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Number of the words
int countWord = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashInt = hash(word);
    node *head = table[hashInt];
    while (head!=NULL)
    {
        if (strcasecmp(head->word,word)==0)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }
    return false;
}

// Hashes word to a number
// Hash Function credit to djb2 by Dan Bernstein
// found on StackOverflow.com
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash = 5381;
    int c;

    while ((c = tolower(*word++))) // hash number for Upper and Lower Characters are different
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fp;
    char word[LENGTH + 1];

    fp = fopen(dictionary, "r");
    if (fp==NULL)
    {
        printf("Error: can't open file");
        return false;
    }

    while (fscanf(fp,"%s",word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return NULL;
        }
        strcpy(n->word, word);
        int hashInt = hash(word); // get a hash number back
        n->next = table[hashInt];
        table[hashInt] = n;
        countWord++;
    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countWord;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i< N; i++)
    {
        node *cursor = table[i];
        while (cursor!=NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
