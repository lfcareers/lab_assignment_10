#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie
{
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

// Inserts the word to the trie structure
void insert(struct Trie **ppTrie, char *word)
{
    struct Trie *curr = *ppTrie;
    if (curr == NULL)
    {
        curr = (struct Trie *)malloc(sizeof(struct Trie));
        curr->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            curr->children[i] = NULL;
        }
        *ppTrie = curr;
    }
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
        {
            curr->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            curr->children[index]->count = 0;
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                curr->children[index]->children[j] = NULL;
            }
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
    {
        return 0;
    }
    struct Trie *curr = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
        {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie != NULL)
    {
        trie->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            trie->children[i] = NULL;
        }
    }
    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    int numWords = 0;
    char word[100];

    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(&pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}