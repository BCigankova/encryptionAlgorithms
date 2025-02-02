#ifndef ENCRYPTION_PROGRAM_H_INCLUDED
#define ENCRYPTION_PROGRAM_H_INCLUDED

#define MAX_SELECTION_SIZE 10

void cipherPromptText(char**, int);
int cipherPrompt();
int cipherSelectionCheck(char* , int);
void encryptionProgram();
char* encrypt(char*, int);

#endif // ENCRYPTION_PROGRAM_H_INCLUDED
