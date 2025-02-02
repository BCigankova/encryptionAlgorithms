#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"

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
        path[strcspn(path, "\n")] = 0;
        plaintext = readFile(path);
    }
    while(plaintext == NULL);
    return plaintext;
}

char* readFile(char* path)
{
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Please input a valid path, inserted: \n%s\n", path);
        return NULL;
    }
    char lineBuffer[MAX_LINE_LEN];
    char* plaintext = malloc(sizeof(char));
    if(plaintext == NULL)
    {
        fprintf(stderr, "Error allocating string\n");
        return NULL;
    }
    plaintext[0] = '\0';

    while(fgets(lineBuffer,MAX_LINE_LEN - 1,file))
    {
        plaintext = concatStrings(plaintext, lineBuffer);
    }

    fclose(file);
    return plaintext;
}


char* concatStrings(char* strdest, char* str)
{
    size_t lenStrdest = strlen(strdest);
    size_t lenStr = strlen(str);
    char* res = malloc((lenStrdest + lenStr + 1) * sizeof(char));
    if(res)
    {
        strcpy(res, strdest);
        strcpy(res + lenStrdest, str);
    }
    return res;
}

