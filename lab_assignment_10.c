#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//define alphabet size for an array
#define ALPHABET_SIZE 26

struct TrieNode {
    //create array of the alphabet size (260)
    struct TrieNode *children[ALPHABET_SIZE];
    //counts number of times a word ends at a node
    int count;
};

struct Trie {
    //pointer for the root node
    struct TrieNode *root;
};

//function for inserting a word into the trie
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurrences(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

//keeps track of the number of times a word occurs in a trie
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    //if trie is empty returns 0
    if (pTrie == NULL || pTrie->root == NULL) {
        return 0;
    }

    struct TrieNode *pNode = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!pNode->children[index]) {
            return 0;
        }
        pNode = pNode->children[index];
    }

    return pNode->count;
}

void insert(struct Trie **ppTrie, char *word) {
    //checks if null and allocates memory for node if it is
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie *)malloc(sizeof(struct Trie));
        (*ppTrie)->root = (struct TrieNode *)calloc(1, sizeof(struct TrieNode));
    }

    //traverse thru the trie and create children for the nodes that need them
    struct TrieNode *pNode = (*ppTrie)->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!pNode->children[index]) {
            pNode->children[index] = (struct TrieNode *)calloc(1, sizeof(struct TrieNode));
        }
        pNode = pNode->children[index];
    }
    //increment count at where the word ends in the nodes
    pNode->count++;
}

//function to deallocate memory from the trie nodes and the children as well
void deallocateNode(struct TrieNode *pNode) {
    if (!pNode) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (pNode->children[i]) {
            //recursevely calls deallocatenode to deallocate memory
            deallocateNode(pNode->children[i]);
        }
    }
    free(pNode);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    deallocateNode(pTrie->root);
    free(pTrie);
    return NULL;
}

int main(void) {
    //array for the words given
    char *words[] = {"notaword", "ucf", "no", "note", "corg", "no", "no"};
    int n = sizeof(words) / sizeof(words[0]);

    struct Trie *trie = NULL;
    for (int i = 0; i < n; i++) {
        insert(&trie, words[i]);
    }
    //checks if the words are in the trie and prints out how many times the appear
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    //if trie is empty print an error message
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    //return 0 at end of program
    return 0;
}
