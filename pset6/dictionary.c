/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

node* root = NULL;
node* crawler = NULL;
node* next = NULL;
int words_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int length = strlen(word);
    int index = 0;
    crawler = root;
    
    // do the pointers lead to the end of the word?
    for (int i=0; i<length; i++)
    { 
       if (word[i] == '\'')
        {
            index = 26;
        }
        else
        {
            index = tolower(word[i]) - 'a'; 
        }
        
        // does children[index] point somewhere yet?
        if (crawler->children[index] == NULL)
        {
            return false;       
        }  
                 
        crawler = crawler->children[index];
    }
    
    // Is the final character in reality the end of a valid word?
    if (crawler->is_word == true)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = malloc(sizeof(node));
        crawler = root;
    char actualCharacter = 0;
    char buffer[LENGTH+1];
    
    // open the dictionary file
    FILE* inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open the dictionary.\n");
        return false;
    }
    
    while (true)
    {   
        int i= 0;
        
        // EOF?
        if((actualCharacter = fgetc(inptr)) == EOF)
            return true;
        
        // store the line of the dictionary into the buffer
        do
        {
           buffer[i] = actualCharacter;
           i++; 
        }
        while ((actualCharacter = fgetc(inptr)) != '\n');
        buffer[i] = '\n';        
        words_count++;
        
        int strlen = i; // I create another variable that is more informative in the following for loop
        int index = 0;
        
        // create the path of the trie for the word in the buffer
        for (int j = 0; j < strlen; j++)
        { 
            // determine what will be the ith position of the letter in the children array
            if (buffer[j] == '\'')
            {
                index = 26;
            }
            else
            {
                index = tolower(buffer[j]) - 'a'; 
            }
            
            // does children[i] point somewhere yet?
            if (crawler->children[index] == NULL)
            {
                next = malloc(sizeof(node));
                
                // is there a problem with malloc?
                if (next == NULL)
                    return false;
                crawler->children[index] = next;          
            }           
            crawler = crawler->children[index];
        }
        crawler->is_word = true;
        crawler = root;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words_count;
}

// recursive function to free all the pointers in memory. It is used in unload(void).
void recursive(node* crawler)
{
    for (int i = 0; i < 27; i++)
    {
        if (crawler->children[i] != NULL)
        {
            recursive(crawler->children[i]);
        }
    }
    free(crawler);
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{       
    recursive(root);
    return true;
}
