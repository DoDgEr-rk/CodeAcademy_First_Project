#define _CRT_SECURE_NO_WARNINGS
#include "VerifyDataFunctions.h"
#include "DataListFunctions.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

enum currency type_currency;
User_data users;
List list;
const char* nameCurruncy[5] = { "BGN", "USD", "EUR", "RSD", "TND" };

int countRowsInFile(FILE *fpNew) 
{
	char c;
	int count = 0;

	for (c = getc(fpNew); c != EOF; c = getc(fpNew))
	{
		if (c == '\n')
		{
			count++;
		}
	}
	return count;
}
void readFileFormat(const char* fileName) 
{
	FILE * fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		exit(1);
	}	
}
bool checkFormatData(FILE* fp, const char* fileName, FILE* fp2, int rows)
{
	int currentRow = 2;
	int lastRow = rows;
	int counterMatches = 0;
	char buffer[BUFFER_SIZE] = { '\0' };

	fgets(buffer, sizeof(buffer), fp);
	//convert the first line to integer number
	if (sscanf(buffer, "%d", &rows) == 1)
	{
		if (lastRow != rows) 
		{
			fprintf(fp2,"%s The first line is not a valid number of lines\n", fileName);
		}
		else 
		{
			counterMatches++;
		}
	}
	
	int  i = 1;
	float totalAmount = 0.0f;
	float lastLine = 0.0f;
	char before[LEN_CURRENCY] = { '\0' };
	int count = 0;

	while (fgets(buffer, sizeof(buffer), fp) && i < lastRow - 1)
	{
		char* token = strtok(buffer, ";");
		int validName = 1;
		int validInvoice = 1;
		int validDate = 1;
		int validCurrency = 1;
		int validAmount = 1;
		
		//check name
		validName = isStringOnlyLetters(token);
		if (!validName) 
		{
			validName = 0;
			fprintf(fp2, "%s : Row %d - The name is not correct.\n", fileName, currentRow);
		}
		//check invoice number
		token = strtok(NULL, ";");
		validInvoice = isInvoicesCorrect(token);
		if (!validInvoice) 
		{
			validInvoice = 0;
			fprintf(fp2, "%s : Row %d - The invoice number is not correct.\n", fileName, currentRow);
		}
		// check date 
		token = strtok(NULL, ";");
		validDate = isDateFormatCorrect(token);
		if (!validDate) 
		{
			validDate = 0;
			fprintf(fp2, "%s : Row %d - The date is not correct.\n", fileName, currentRow);
		}
		// check currency 
		token = strtok(NULL, ";");
		if (count == 0) 
		{
			strcpy(before, token);
			count = 1;
		}
		validCurrency = isCurrencyFormatCorrect(token, before);
		if (!validCurrency) 
		{
			validCurrency = 0;
			fprintf(fp2, "%s : Row %d - The currency is not correct.\n", fileName, currentRow);
		}
		// check amount 
		token = strtok(NULL, ";");
		double amount = 0.0;
		amount = atof(token);

		validAmount = isNumberDouble(token);
		if (!validAmount) 
		{
			validAmount = 0;
			fprintf(fp2, "%s : Row %d - The Amount is not correct.\n", fileName, currentRow);
		}

		if (validName && validInvoice && validDate && validCurrency && validAmount)
		{
			// add the amount to total amount 
			totalAmount += (float)amount;
			counterMatches++;
		}
		
		i++;
		currentRow++;
	}

	// read the last line 
	fgets(buffer, sizeof(buffer), fp);
	// convert the last line to double number 
	int clearError = sscanf(buffer, "%f", &lastLine);
	// check if the last line is equal to the sum of the invoices 

	if (totalAmount == lastLine)
	{
		counterMatches++;
	}
	else
	{
		fprintf(fp2, "%s : The last line does not match the invoice\n", fileName);
	}
	if (counterMatches == rows)
	{
		return 1;
	}
	return 0;
}
bool isStringOnlyLetters(const char* str) 
{
	while (*str != '\0') 
	{
		if (!isalpha(*str)) 
		{
			return 0;
		}
		str++;
	}
	return 1;
}
bool isInvoicesCorrect(const char* str)
{
	int counter = 0;
	int len = (int)strlen(str);

	while (*str != '\0') 
	{
		if (isalpha(str[0]) || isalpha(str[1]))
		{
			counter++;
		}
		else if (isdigit(*str))
		{
			counter++;
		}
		str++;
	}
	if (counter == len) 
	{
		return 1;
	}
	return 0;
}
bool isDateFormatCorrect(const char* str)
{
	int len = (int)strlen(str);
	int year = 0;
	int day = 0;
	int month = 0;

	if (DATE_SIZE < len || DATE_SIZE > len) 
	{
		return 0;
	}
	for (int i = 0; i < DATE_SIZE; i++)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}
	day = (str[0] - '0') * 10 + (str[1] - '0');
	month = (str[2] - '0') * 10 + (str[3] - '0');
	year = (str[4] - '0') * 1000 + (str[5] - '0') * 100 + (str[6] - '0') * 10 + (str[7] - '0');

	if (day < 1 || day > 31) 
	{
		return 0;
	}

	if (month < 1 || month > 12 || month == 2)
	{
		if (day > 29)
		{
			return 0;
		}
		return 0;
	}

	if (year < 1900 || year > 9999)
	{
		return 0;
	}

	int maxDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if ((month == 2) && (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))
	{
		maxDaysInMonth[1] = 29;
	}

	if (day > maxDaysInMonth[month - 1])
	{
		return 0;
	}

	return 1;
}
bool isCurrencyFormatCorrect(const char* str, char* before) 
{
	enum curruncy currCurruncy;
	bool curruncyIsFound = false;
	int count = 0;

	for (currCurruncy = BGN; currCurruncy <= TND; currCurruncy++)
	{
		if (strcmp(before, str) == 0)
		{
			return 1;
		}
	}
		return 0;
}
bool isNumberDouble(char* number)
{
	double fNumber = 0.0;
	if (sscanf(number, "%lf", &fNumber) == 1) {
		return 1;
	}
	return 0;
}
bool checkFileNameIsCorrect(const char* fileName, FILE* fp) 
{
	char prefix[LEN_FILE_NAME] = "IMPORT_INVOICES_";
	char Buffer[BUFFER_];
	char dateStr[DATE_SIZE_];
	char timeStr[TIME_SIZE_];
	char* token;

	strcpy(Buffer, fileName);
	// check if file name starts with "IMPORT_INVOICES_"
	if (strncmp(Buffer, prefix, strlen(prefix)) == 0) 
	{
		// use strtok to extract the date and time from the file name
		token = strtok(Buffer + strlen(prefix), "_.");
		strncpy(dateStr, token, DATE_SIZE);
		dateStr[DATE_SIZE] = '\0';
		token = strtok(NULL, "_.");
		strncpy(timeStr, token, LEN_TIME);
		timeStr[LEN_TIME] = '\0';

		int iResultDate = isDateFormatCorrectInFileName(dateStr);
		int iResultTime = checkTimeFormatInFileName(timeStr);

		if (iResultDate == 1 && iResultTime == 1) 
		{
			return 1;
		}
	}
	fprintf(fp, "%s : The file name is NOT correct\n", fileName);
	return 0;
}
bool checkTimeFormatInFileName(const char* fileName) 
{
	time_t currentTime = time(NULL);
	struct tm* timeInfo = gmtime(&currentTime);
	int iHours = timeInfo->tm_hour;
	int iMinutes = timeInfo->tm_min;
	int iSeconds = timeInfo->tm_sec;

	// Check if the hour is valid
	if (iHours < 0 || iHours > 23) 
	{
		//printf("Invalid hour\n");
		return 0;
	}
	if (iMinutes < 0 || iMinutes > 59) 
	{
		//printf("Invalid minutes\n");
		return 0;
	}
	if (iSeconds < 0 || iSeconds > 59) 
	{
		//printf("Invalid seconds\n");
		return 0;
	}

	return 1;
}
bool isDateFormatCorrectInFileName(const char* str) 
{
	int len = (int)strlen(str);
	int year, day, month;

	if (DATE_SIZE < len || DATE_SIZE > len)
	{
		return 0;
	}

	for (int i = 0; i < DATE_SIZE; i++)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}

	year = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
	month = (str[4] - '0') * 10 + (str[5] - '0');
	day = (str[6] - '0') * 10 + (str[7] - '0');

	if (day < 1 || day > 31) 
	{
		return 0;
	}
	if (month < 1 || month > 12 || month == 2) 
	{
		if (day > 29) {
			return 0;
		}
		if (month < 1 || month > 12) 
		{
			return 0;
		}

	}

	if (year < 1900 || year > 9999) 
	{
		return 0;
	}

	int maxDaysMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if ((month == 2) && (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) 
	{
		maxDaysMonth[1] = 29;
	}

	if (day > maxDaysMonth[month - 1])
	{
		return 0;
	}
	return 1;
}
