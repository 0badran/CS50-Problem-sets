// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// I got some advice from chatGpt
// https://chatgpt.com/share/43e33685-85bf-41f8-a821-4fe2bc3c1740

// Update each letter to uppercase and return new string
char *strtoupper(const char *s);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Global variable to track each word added to dictionary
int count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Get the index for the own node in hash table.
    int hash_index = hash(word);
    node *ptr = table[hash_index];
    // Check if the not found node.
    if (ptr == NULL)
    {
        return false;
    }
    // Convert the whole word to uppercase for comparison
    char *word_upper = strtoupper(word);
    // Iterate on each node in a linked list
    while (ptr != NULL)
    {
        // Return true if found a word in dictionary
        if (strcmp(ptr->word, word_upper) == 0)
        {
            free(word_upper);
            return true;
        }
        ptr = ptr->next;
    }
    // Else return false
    free(word_upper);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // Read each word in the file
    char tmp[LENGTH + 1];
    while (fscanf(source, "%s", tmp) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            free(source);
            return false;
        }

        char *word = strtoupper(tmp);
        strcpy(new_node->word, word);
        free(word);
        // Add each word to the hash table
        int hash_index = hash(new_node->word);
        if (table[hash_index])
        {
            new_node->next = table[hash_index];
        }
        else
        {
            new_node->next = NULL;
        }
        table[hash_index] = new_node;
        count++;
    }
    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = tmp->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}

// Update each letter to uppercase and return new string
char *strtoupper(const char *s)
{
    int n = strlen(s);
    char *result = malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        result[i] = toupper(s[i]);
    }
    result[n] = '\0';
    return result;
}
