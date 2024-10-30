#ifndef TEST_H
#define TEST_H

#define DATE_SIZE_ 9
#define TIME_SIZE_ 7
#define BUFFER_ 100

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum currency { BGN, USD, EUR, RSD, TND };

int countRowsInFile(FILE* fpNew);
void readFileFormat(const char* file);
bool checkFormatData(FILE* fp, const char* fileName, FILE* fp2, int rows);
bool isStringOnlyLetters(const char* str);
bool isDateFormatCorrect(const char* str);
bool isInvoicesCorrect(const char* str);
bool isNumberDouble(char* str);
bool isCurrencyFormatCorrect(const char* str, char* before);
bool checkFileNameIsCorrect(const char* fileName, FILE* fp);
bool checkTimeFormatInFileName(const char* fileName);
bool isDateFormatCorrectInFileName(const char* str);


#endif 