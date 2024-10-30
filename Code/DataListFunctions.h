#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#define BUFFER_SIZE 1024
#define SIZE_NAME 20
#define NUMBER_INVOICES 8
#define DATE_SIZE 8
#define DATE 9
#define LEN_FILE_NAME 50
#define LEN_TIME 6
#define LEN_CURRENCY 4

typedef struct User_data {
    char cUserName[SIZE_NAME];
    char cNumber_Invoices[NUMBER_INVOICES];
    char cDate[DATE];
    char currency[LEN_CURRENCY];
    double sum;
    struct User_data* next;
}User_data;

typedef struct List {
    struct User_data* head;
    struct User_data* tail;
}List;

void addValidDataInList(FILE* file, List* list, const char* fileName);
void printList(List* list);
int nameCompare(User_data* current, User_data* next);
int numberInvoicesCompare(User_data* current, User_data* next);
void swapData(User_data* current, User_data* next);
void sortListBySum(List* list);
void writeToFile(FILE* file, List* list);

#endif