// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (45 * 'Z') + 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int wordIndex = hash(word);
    node *cursor = table[wordIndex];

    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0){
            return true; // word in dict
        }
        cursor = cursor->next;
    }

    return false; // word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // chose to do math with words
    int total = 0;
    int constant = 7;

    for (int i = 0; i < strlen(word); i++){
        //sum ascii, minus constant
        total += toupper(word[i]);
    }
    total = total - constant;

    return (total % N);
}

int totalNumWords = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // read words in from dict
    char word[46];

    // connect to dict
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        return false;
    }

    while ( fscanf(file, "%s", word) != EOF ){
        // nodes for every word
        node *wordNode = malloc(sizeof(node));

        if (wordNode == NULL) {
            return false;
        }

        strcpy(wordNode->word, word);
        wordNode->next = NULL;

        // for index of the hash, if node is null input wordNode
        int nodeIndex = hash(word);
        if (table[nodeIndex] == NULL) {
            table[nodeIndex] = wordNode;
        } else {
            wordNode->next = table[nodeIndex];
            table[nodeIndex] = wordNode;
        }
        totalNumWords ++;

    }
    fclose(file);

    return true; // load success
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalNumWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i=0; i < N; i++){
        node *head = table[i];
        node *temp = head;
        node *cursor = head;

        while(cursor != NULL){
            // move cursor
            cursor = cursor->next;
            // rm temp node and point to cursor
            free(temp);
            temp = cursor;
        }
    }
    return true; //free'd everything
}
