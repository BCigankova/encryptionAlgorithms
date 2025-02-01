#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH_SIZE 100
#define MAX_SELECTION_SIZE 10
#define MAX_LINE_LEN 150

typedef struct {
    int top;
    char* string;
}dynamicString;

dynamicString* getDynamicString();

char* pathPrompt();
int accessCheck(char*);

char* readFile(char*);
dynamicString* resizeStringWithNewline(dynamicString*, int);

void cipherPromptText(char**, int);
int cipherPrompt();
int cipherSelectionCheck(char* , int);

char* encrypt(char*, int);

char* encryptCaesar(char*);
int isLetter (char);

int generateRandNum(int);

void encryptionProgram();



//pro pridani novych sifer update array v cipherPrompt a switch v encrypt

int main()
{
    encryptionProgram();
    return 0;
}

//top = 1 => v array je top -1 mist => v arrayi je 0 mist => array je NULL
//top = 5 => 4 mista => array[0] az array[3]

dynamicString* getDynamicString()
{
    dynamicString* array = malloc(sizeof(dynamicString));
    if(array == NULL)
    {
        fprintf(stderr, "Error allocating memory for dynamic string\n");
        return NULL;
    }
    array->string = NULL;
    array->top = 1;
    return array;
}


char* pathPrompt()
{
    char path[MAX_PATH_SIZE];
    char* plaintext;
    do
    {
        printf("Enter file path:\n");
        if(fgets(path, MAX_PATH_SIZE, stdin) == NULL)
        {
            fprintf(stderr, "Error reading input\n");
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

    char lineBuffer[MAX_LINE_LEN];
    dynamicString* plaintext = getDynamicString();
    int lineCount = 0;

    while(fgets(lineBuffer,MAX_LINE_LEN,file))
    {
        while((strlen(plaintext->string) + (strlen(lineBuffer))) > (plaintext->top - 1))
        {
            plaintext = resizeStringWithNewline(plaintext, lineCount + 1);
            if(plaintext == NULL)
            {
                return NULL;
            }
        }
        strcat(plaintext->string, strcat(lineBuffer, "\n"));
        lineCount++;
    }

    fclose(file);
    return plaintext->string;
}


dynamicString* resizeStringWithNewline(dynamicString* plaintext, int lineCount)
{
    plaintext->top *= 2;
    dynamicString* newPlaintext = realloc(plaintext->string, (sizeof(char) * plaintext->top) + lineCount);

    if (newPlaintext == NULL)
    {
        fprintf(stderr, "Error reallocating memory for dynamic array\n");
    }

    return newPlaintext;
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
        if(fgets(input, (ciphersSize/10) + 2, stdin) == NULL)
        {
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

char* encrypt(char* plaintext, int cipher)
{
    char* cipherText = NULL;
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
        cipherText[i] = isLetter(cipherText[i]) == 0 ? (char) (plaintext[i] + randomNumber) : plaintext[i];
    }
    return cipherText;
}

    //otestovat a dodelat pres ternary
int isLetter (char c)
{
    int value = c;
    if(((value > 64) && (value < 91)) || ((c >= 'a') && (c <= 'z')))
    {
        return 0;
    }
    return -1;
}

int generateRandNum(int max)
{
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);
    return (random() % (max + 1));
}

void encryptionProgram()
{
    char* plaintext = pathPrompt();
    printf("Ciphertext:\n\n%s\n", encrypt(plaintext, cipherPrompt()));
}
