#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE   256

typedef struct _Node
{
    bool isEndOfWord;
    struct _Node* next[ALPHABET_SIZE];
} Node;

Node* createNode()
{
    int i;
    Node* newNode = malloc(sizeof(Node));
    newNode->isEndOfWord = false;
    for(i=0; i<ALPHABET_SIZE; i++)
        newNode->next[i] = NULL;
    return newNode;
}
bool insertWord(Node* root, char word[])
{
    int i;
    bool result;
    Node* temp = root;
    for(i=0; word[i]!='\0'; i++)
    {
        int idx = word[i];// - 'a';
        if(temp->next[idx]==NULL)
            temp->next[idx] = createNode();
        temp = temp->next[idx];
    }
    result = temp->isEndOfWord;
    temp->isEndOfWord = true;
    printf("\nInserted %s", word);
    return !result;
}
int showMenu()
{
    int choice;
    printf("\n\tMenu");
    printf("\n\t====");
    printf("\n\t1. Insert Word");
    printf("\n\t2. Auto Suggest");
    printf("\n\t3. Print All Words");
    printf("\n\t4. Exit");
    printf("\n\n\t Your Choice : ");

    scanf("%d", &choice);
    return choice;
}

void printAllWords(Node* root, char prefix[])
{
    int i;
    if(root->isEndOfWord == true)
        printf("\n%s", prefix);

    int len = strlen(prefix);
    char* newPrefix = malloc(len+2); // 1 letter, 1 --'\0'
    strcpy(newPrefix, prefix);
    for(i=0; i<ALPHABET_SIZE; i++)
    {
        if(root->next[i]!=NULL)
        {
            newPrefix[len] = i; // + 'a';
            newPrefix[len+1] = '\0';
            printAllWords(root->next[i], newPrefix);
        }
    }
    free(newPrefix);
}
void autoSuggest(Node* root, char prefix[])
{
    int i;
    Node* temp = root;
    for(i=0;prefix[i]!='\0';i++)
    {
        int idx = prefix[i];//-'a';
        if(temp->next[idx]==NULL)
        {
            printf("\nNo Words starting with '%s'", prefix);
            return;
        }
        temp = temp->next[idx];
    }
    printAllWords(temp, prefix);
}
int main()
{
    int choice;
    Node* root = createNode();
    int count = 0;
    char word[200];

    
    FILE* fp = fopen("/home/sumit/Desktop/AutoSuggest/dict.txt","r");

    while(!feof(fp))
    {
        fscanf(fp, "%s", word);
        insertWord(root, word);
    }

    fclose(fp);

    while(1)
    {
        choice = showMenu();
        switch(choice)
        {
        case 1:
            printf("\n\tEnter a word: ");
            scanf("%s", word);
           // fflush(stdin);
           // gets(word);
            if(insertWord(root, word) == true)
                count++;
            printf("\nTotal Words: %d\n", count);
            break;
        case 2:
            printf("\n\tEnter a prefix: ");
            scanf("%s", word);
            fflush(stdin);
            //gets(word);
            autoSuggest(root, word);
            break;
        case 3:
            printAllWords(root, "");
            break;
        case 4:
            return 0;
        default:
            printf("\n\t Bad Choice, Try Again!!\n");
        }
    }
    return 0;
}
