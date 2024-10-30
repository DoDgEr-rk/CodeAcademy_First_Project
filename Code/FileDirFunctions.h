#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void changeDir(const char* argv);
void renameFileExtension(char* fileName, FILE* fp);
void renameFileExtensionKO(char* fileName, FILE* fp2);
void makeNewFile(const char* fileName, char* newFileName, FILE* fp);


#endif 