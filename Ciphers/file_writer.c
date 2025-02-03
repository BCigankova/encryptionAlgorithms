#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_writer.h"



void fileWriterPrompt(char* ciphertext)
{
    char path[MAX_PATH_SIZE];
    int res = 2;
    do
    {
        printf("Input file path to write result or -1 to quit\n");
        if(fgets(path, MAX_PATH_SIZE, stdin) == NULL)
        {
            fprintf(stderr, "Error reading input\n");
            return;
        }
        path[strcspn(path, "\n")] = 0;
        res = strcmp(path, "-1");
        if(res == 0)
        {
            return;
        }
        res = fileWriter(path, ciphertext);
    }
    while(res == -1);
}

int fileWriter(char* path, char* ciphertext)
{
    FILE* file = fopen(path, "w");
    if(file == NULL)
    {
        printf("Please input a valid path");
        return -1;
    }
    if(fputs(ciphertext, file) == EOF)
    {
        fprintf(stderr, "Error writing to file\n");
    }
    return 0;
}
