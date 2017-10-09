// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

//define the structure node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

//declare hashtable
node *hashtable[500000];

//hash function taken from https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
int hashfunction(char *needs_hashing)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(needs_hashing); i < n; i++)
    {
        hash = (hash << 2) ^ needs_hashing[i];
    }
    return hash % 500000;
}
//declare word_count for size()
int word_count = 0;

//declare boolean for load and unload
bool loaded = false;


// Returns true if word is in dictionary else false, traverse linked lists
bool check(const char *word)
{
    // need a char array for a copy of the word in all lowercase
    int length = strlen(word);
    char lower_word[length + 1];

    for (int i = 0; i < length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    //add null terminator to end of array
    lower_word[length] = '\0';

    //hash copy
    int hash_index = hashfunction(lower_word);

    //initialize cursor at beginning of corresponding linked list in hash table
    node *cursor = hashtable[hash_index];
    //check until the end of linked list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lower_word) == 0)
        {
            return true;
        }
        else
        {
            //check the next node in linked list
            cursor = cursor->next;
        }
    }
    //if haven't found any match by end of linked list, return false
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open the dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        printf("Could not open %s\n.", dictionary);
        return false;
    }

    //initiate all hashtable elements as NULL
    for (int element = 0; element < 500000; element++)
    {
        hashtable[element] = NULL;
    }

    char word[LENGTH + 1];
    //for each word in dictionary_file, put it into the new_node
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        //add to word count
        word_count++;

        //malloc space for a new node to contain each word from dictionary_file
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            printf("Could not malloc a node* for your word.");
            return false;
        }
        //put word in new node
        strcpy(new_node->word, word);

        //hash new_node->word
        int hash_index = hashfunction(word);

        //if hashtable of row hash_index is empty
        if (hashtable[hash_index] == NULL)
        {
            hashtable[hash_index] = new_node;
            new_node->next = NULL;
        }

        else
        {
            //point newnode to original first node- where hashtable[hash_index] was pointing to
            new_node->next = hashtable[hash_index];
            //point head of hash table to new_node
            hashtable[hash_index] = new_node;
        }
    }
    //close the file
    fclose(dictionary_file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int row = 0;
    while (row < 500000)
    {
        //if no items in a certain hashtable[hash_index], then go to next index
        if (hashtable[row] == NULL)
        {
            row++;
        }
        //iterate through nodes in linked list
        else
        {
            while (hashtable[row] != NULL)
            {
                node *cursor = hashtable[row];
                hashtable[row] = cursor-> next;
                free(cursor);
            }
            //done emptying nodes at index, move on to next index
            row++;
        }
    }
    loaded = false;
    return true;
}
