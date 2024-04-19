#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  int isWord;
  struct Trie *next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word, int index) {
  if (index == strlen(word)) {
    pTrie->isWord += 1;
    return;
  }

  int nextIndex = word[index] - 'a';
  if (pTrie->next[nextIndex] == NULL)
    pTrie->next[nextIndex] = malloc(sizeof(struct Trie));

  insert(pTrie->next[nextIndex], word, index + 1);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word, int index) {
  int occ = 0;
  if (index == strlen(word)) {
    occ += pTrie->isWord;
  }
  int nextIndex;
  if (word[index] == '\0') {
    nextIndex = 0;
  } else {
    nextIndex = word[index] - 'a';
  }

  if (pTrie->next[nextIndex] != NULL) {
    occ += numberOfOccurances(pTrie->next[nextIndex], word, index + 1);
  }
  return occ;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  for (int i = 0; i < 26; i++) {
    if (pTrie->next[i] != NULL)
      deallocateTrie(pTrie->next[i]);
  }
  free(pTrie);
  return NULL;
}

// Initializes a trie structure
struct Trie *createTrie() {
  struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
  pTrie->isWord = 0;
  for (int i = 0; i < 26; i++) {
    pTrie->next[i] = NULL;
  }
  return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  int numWords = 0;
  FILE *fp1 = fopen(filename, "r");
  fscanf(fp1, "%d", &numWords);
  for (int i = 0; i < numWords; i++) {
    pInWords[i] = (char *)malloc(100 * sizeof(char));
    fscanf(fp1, "%s", pInWords[i]);
  }
  return numWords;
}

int main(void) {
  char *inWords[256];

  // read the number of the words in the dictionary
  int numWords = readDictionary("dictionary-1.txt", inWords);
  for (int i = 0; i < numWords; ++i) {
    printf("%s\n", inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i = 0; i < numWords; i++) {
    insert(pTrie, inWords[i], 0);
  }

  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i], 0));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}