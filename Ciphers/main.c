#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 100
#define MAX_SELECTION_SIZE 10


int pathPrompt();
int accessCheck(char*);

void cipherPromptText(char**, int);
int cipherPrompt();
int cipherSelectionCheck(char* , int);

char* encrypt(char*, int);
char* encryptCaesar(char*)

int generateRandNum(int);



//pro pridani novych sifer update array v cipherPrompt a switch v encrypt

int main()
{
    int res = pathPrompt();
    res = cipherPrompt();
    return 0;
}


char* pathPrompt ()
{
    char path[MAX_PATH_SIZE];
    char* plaintext;
    do
    {
        printf("Enter file path:\n");
        if(fgets(path, MAX_PATH_SIZE, stdin) == NULL)
        {
            perror("Error reading file: ");
            return NULL;
        }
        plaintext = readFile(plaintext);
    }
    while(plaintext == NULL);
    return plaintext;
}

char* readFile(char* path)
{
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Please input a valid path\n");
        return NULL;
    }



}

void cipherPromptText(char* ciphers[], int ciphersSize)
{

    printf("Please select a cipher:\n");
    for(int i = 0; i < ciphersSize; i++)
    {
        printf("%s: %i\n", ciphers[i], i);
    }
}

int cipherPrompt()
{
    char* ciphers[] = {"Caesar"};
    int ciphersSize = sizeof(ciphers)/sizeof(ciphers[0]);
    char input[MAX_SELECTION_SIZE];
    int selection;

    do
    {
        cipherPromptText(ciphers, ciphersSize);
        if(fgets(input, (ciphersSize/10) + 10, stdin) == NULL)
        {
            perror("Error reading input: ");
            return -1;
        }
        input[strcspn(input, "\n")] = 0;
        selection = cipherSelectionCheck(input, ciphersSize);
    }
    while(selection == -1);

    return selection;
}

int cipherSelectionCheck(char input[], int ciphersSize)
{
    int selection;
    if(sscanf(input, "%d", &selection) == 0)
    {
        printf("Please enter an integer\n");
        return -1;
    }

    if(selection >= ciphersSize)
    {
        printf("Please enter a valid choice\n");
        return -1;
    }
    return selection;
}

char* encrypt(char plaintext[], int cipher)
{
    char cipherText[] = NULL;
    switch (cipher)
    {
        case 0:
            cipherText = encryptCaesar(plaintext);
        break;
    }
    return cipherText;
}


char* encryptCaesar(char plaintext[])
{
    int randomNumber = generateRandNum(93);
    char* cipherText = malloc(sizeof(char) * (strlen(plaintext) + 1));

    printf("Encrypting with Caesar, key: %d\n", randomNumber);

    for(int i = 0; plaintext[i] != '\0'; i++)
    {
        cipherText[i] = plaintext[i] + randomNumber;
    }
    return cipherText;
}


int generateRandNum(int max)
{
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);
    return (random() % (max + 1));
}

