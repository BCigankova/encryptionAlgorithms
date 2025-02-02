#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "encryption_program.h"
#include "file_reader.h"
#include "caesar.h"

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

void encryptionProgram()
{
    char* plaintext = pathPrompt();
    printf("Ciphertext:\n\n%s\n", encrypt(plaintext, cipherPrompt()));
}

char* encrypt(char* plaintext, int cipher)
{
    char* ciphertext = NULL;
    switch (cipher)
    {
        case 0:
            ciphertext = encryptCaesar(plaintext);
        break;
    }
    return ciphertext;
}
