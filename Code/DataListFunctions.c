#define _CRT_SECURE_NO_WARNINGS
#include "DataListFunctions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void addValidDataInList(FILE* file, List* list, const char* fileName)
{
	char cUserName[SIZE_NAME], cNumber_Invoices[NUMBER_INVOICES], cDate[DATE], currency[LEN_CURRENCY];
	double sum;
	int result = 0;
	int number = -1;

	while (!feof(file))
	{
		char line[100];

		if (fgets(line, 100, file))
		{
			result = sscanf(line, "%[^';'];%[^';'];%[^';'];%[^';'];%lf", cUserName, cNumber_Invoices, cDate, currency, &sum);

			if (cUserName[0] >= '0' && cUserName[0] <= '9')
			{
				if (number < 0)
				{
					number = 1;
					continue;
				}
				else
				{
					return;
				}
			}
			User_data* new_node = (User_data*)malloc(sizeof(User_data));

			strcpy(new_node->cUserName, cUserName);
			strcpy(new_node->cNumber_Invoices, cNumber_Invoices);
			strcpy(new_node->cDate, cDate);
			strcpy(new_node->currency, currency);

			new_node->sum = sum;
			new_node->next = NULL;

			if (list->head == NULL)
			{
				list->head = new_node;
				list->tail = new_node;
			}
			else if (list->tail != NULL)
			{
				list->tail->next = new_node;
				list->tail = new_node;
			}
			else
			{
				fprintf(file, "%s The file could not be renamed.\n", fileName);
			}
		}
	}
}
void printList(List* list)
{
	User_data* current = list->head;

	while (current != NULL)
	{
		printf("%s -> %s -> %s -> %s -> %.2lf\n", current->cUserName, current->cNumber_Invoices, current->cDate, current->currency, current->sum);
		current = current->next;
	}
}
int nameCompare(User_data* current, User_data* next)
{
	int len = (int)strlen(current->cNumber_Invoices);

	for (int i = 0; i < len; i++)
	{
		if (current->cNumber_Invoices[i] < next->cNumber_Invoices[i])
		{
			return -1;
		}
		else if (current->cNumber_Invoices[i] > next->cNumber_Invoices[i])
		{
			return 1;
		}
	}
	return 0;
}
int numberInvoicesCompare(User_data* current, User_data* next)
{
	int len = (int)strlen(current->cNumber_Invoices);

	for (int i = 0; i < len; i++)
	{
		if (current->cNumber_Invoices[i] < next->cNumber_Invoices[i])
		{
			return -1;
		}
		else if (current->cNumber_Invoices[i] > next->cNumber_Invoices[i])
		{
			return 1;
		}
	}
	return 0;
}
void swapData(User_data* current, User_data* next)
{
	char cUserName[SIZE_NAME];
	strcpy(cUserName, current->cUserName);
	strcpy(current->cUserName, next->cUserName);
	strcpy(next->cUserName, cUserName);

	char cNumber_Invoices[NUMBER_INVOICES];
	strcpy(cNumber_Invoices, current->cNumber_Invoices);
	strcpy(current->cNumber_Invoices, next->cNumber_Invoices);
	strcpy(next->cNumber_Invoices, cNumber_Invoices);

	char cDate[DATE];
	strcpy(cDate, current->cDate);
	strcpy(current->cDate, next->cDate);
	strcpy(next->cDate, cDate);

	char currency[LEN_CURRENCY];
	strcpy(currency, current->currency);
	strcpy(current->currency, next->currency);
	strcpy(next->currency, currency);

	double sum = current->sum;
	current->sum = next->sum;
	next->sum = sum;
}
void sortListBySum(List* list)
{
	User_data* current = list->head;

	while (current != NULL)
	{
		User_data* next = current->next;

		while (next != NULL)
		{
			if (current->sum > next->sum)
			{
				swapData(current, next);
			}
			else if (current->sum == next->sum)
			{
				if (nameCompare((User_data*)current->cUserName, (User_data*)next->cUserName) > 0)
				{
					swapData(current, next);
				}
				else if (nameCompare((User_data*)current->cUserName, (User_data*)next->cUserName) == 0)
				{
					if (numberInvoicesCompare((User_data*)current->cNumber_Invoices, (User_data*)next->cNumber_Invoices) > 0)
					{
						swapData(current, next);
					}
					else if (numberInvoicesCompare((User_data*)current->cNumber_Invoices, (User_data*)next->cNumber_Invoices) == 0)
					{
						if (strcmp(current->cDate, next->cDate) > 0)
						{
							swapData(current, next);
						}
					}
				}
			}
			next = next->next;
		}
		current = current->next;
	}
}
void writeToFile(FILE* file, List* list)
{
	User_data* current = list->head;
	while (current != NULL)
	{
		fprintf(file, "%s;%s;%s;%s;%.2lf\n", current->cUserName, current->cNumber_Invoices, current->cDate, current->currency, current->sum);
		current = current->next;
	}
}