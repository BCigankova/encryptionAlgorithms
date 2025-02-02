#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "caesar.h"

char* encryptCaesar(char plaintext[])
{
    int key = generateRandNum(NUMBER_OF_LETTERS);
    char* ciphertext = malloc(sizeof(char) * (strlen(plaintext) + 1));

    printf("Encrypting with Caesar, key: %d\n", key);

    for(int i = 0; plaintext[i] != '\0'; i++)
    {
        if((plaintext[i] >= 'A') && (plaintext[i] <= 'Z'))
        {
            ciphertext[i] = (char) ((plaintext[i] - 'A' + key) % 26 + 'A');
        }
        else if((plaintext[i] >= 'a') && (plaintext[i] <= 'z'))
        {
            ciphertext[i] = (char) ((plaintext[i] - 'a' + key) % 26 + 'a');
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}

int generateRandNum(int max)
{
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);
    return (random() % (max + 1));
}
