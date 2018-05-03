/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

int count = 0;
//Defining a trie data structure
typedef struct trie
    {
        bool is_word;
        struct trie *children[27]; // 26 alphabets + '/'''
    }
    trie;
    
    trie root = {false, {NULL}};
    //trie* trav = &root;

//trie pointer location function
int insert_index (char c);
void free_trie(trie *currentNode);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    trie* trav = &root;
    
    for (int j = 0, len = strlen(word); j < len; j++)
    {
        if (trav -> children[insert_index(word[j])] == NULL)
            return false;
        else
        {
            trav = trav -> children[insert_index (word[j])];
        }
    }
    
    if (trav -> is_word == true)
    return true;
    else
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }
    
    while (!feof(fp))
    {
        //int count = 0;
        char dict_word [LENGTH + 1] = {};
        
        /*for (char c = fgetc(fp); c != '\n'; c = fgetc(fp))
        {
            int index = 0;
            dict_word[index] = c;
            index++;
        }*/
        
        fscanf (fp, "%s\n", dict_word);
        count++;
        trie* trav = &root;
        for (int i = 0, wordlen = strlen(dict_word); i < wordlen; i++)
        {
            if (trav -> children[insert_index(dict_word[i])] == NULL)
            {
                trie* next = malloc(sizeof(trie));
                * next = (trie) {false, {NULL}};
                trav -> children[insert_index(dict_word[i])] = next;
                trav = next;
            }
            else
            trav = trav -> children[insert_index(dict_word[i])];
        }
        trav -> is_word= true;
    }
    fclose (fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (count)
        return count;
    else
        return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{     
    // TODO
    for (int k = 0; k < 27; k++)            
    {
        if (root.children[k] != NULL)
        {
            free_trie(root.children[k]);
        }
    }
    return true;   
}



void free_trie(trie *currentNode)
{
    for (int l = 0; l < 27; l++)
    {
        if (currentNode->children[l] != NULL)   
        {
            free_trie(currentNode -> children[l]); 
        }
    }
    free(currentNode);
}




int insert_index (char c)
{
    int num;
    if (c == '\'')
        return 26;
    else if(c >= 'A' && c <= 'Z')
        c += 32;
    num = c - 'a';
    return num;
}