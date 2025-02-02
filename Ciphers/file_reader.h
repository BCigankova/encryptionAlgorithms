#ifndef FILE_READER_H_INCLUDED
#define FILE_READER_H_INCLUDED

#define MAX_PATH_SIZE 100
#define MAX_LINE_LEN 150


char* pathPrompt();
char* readFile(char*);
char* concatStrings(char*, char*);

#endif // FILE_READER_H_INCLUDED
