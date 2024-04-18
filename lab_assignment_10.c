#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie* children[26];	
};


// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* pTrie=malloc(sizeof(struct Trie));
    pTrie->count=0;
    
    for(int i=0;i<26;i++){
        pTrie->children[i]=NULL;
    }
    return pTrie;
}
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i;
    struct Trie* temp=pTrie;
    for(i=0;i<strlen(word);i++){
        int nextIdx=word[i]-'a';
        if(temp->children[nextIdx]==NULL){
            temp->children[nextIdx]=createTrie();
        }
        temp=temp->children[nextIdx];

    }
    temp->count++;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int i;
    int count=0;
    struct Trie* temp=pTrie;
    for(i=0;i<strlen(word);i++){
        int nextIdx=word[i]-'a';
        if(temp->children[nextIdx]!=NULL){
           temp=temp->children[nextIdx]; 
        }
        else{
            return count;
        }        

    }
    return temp->count;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i=0;i<26;i++){
        if(pTrie->children[i]!=NULL)
            deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    pTrie=NULL;
    return pTrie;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* inFile = fopen(filename, "r");
	int size = 0;
    

	if (inFile)
	{
		fscanf(inFile, "%d\n", &size);
		for (int i = 0; i < size; ++i)
		{
            char word[100];
            fscanf(inFile,"%s\n",word);
            pInWords[i]=malloc(strlen(word)*sizeof(char));
            strcpy(pInWords[i],word);
		}

		fclose(inFile);
	}
    return size;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}