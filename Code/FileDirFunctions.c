#define _CRT_SECURE_NO_WARNINGS
#include "dirent_project.h"
#include "FileDirFunctions.h"
#include "DataListFunctions.h"
#include "VerifyDataFunctions.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>

void changeDir(const char* newFolder)
{
	int result = _chdir(newFolder);

    if (result != 0) 
    {
        perror("Error changing directory");
    }	
}
void renameFileExtension(char* fileName, FILE* fp) 
{
    char OK[] = ".ok";
	char NewName[100];
	int i = 0;

	strcpy(NewName, fileName);
	strtok(NewName, ".");
	strcat(NewName, OK);

	int result1 = rename(fileName, NewName);
	if (result1 != 0) 
    {

        fprintf(fp, "%s The file could not be renamed.\n", fileName);
	}	
}
void renameFileExtensionKO(char* fileName, FILE* fp2)
{
    char OK[] = ".ko";
    char NewName[100];
    int i = 0;

    strcpy(NewName, fileName);
    strtok(NewName, ".");
    strcat(NewName, OK);

    int result1 = rename(fileName, NewName);
    if (result1 != 0) 
    {
       fprintf(fp2, "%s The file could not be renamed.\n", fileName);
    }
}
void makeNewFile(const char* fileName, char* newFileName, FILE* fp)
{
    char oldStr[] = "IMPORT_INVOICES";
    char newStr[] = "INVOICES_ORDERED";
    int i = 0;
    int j = 0;
    int flag = 0;
    int start = 0;
    
    while (fileName[i] != '\0')
     {
         if (fileName[i] == oldStr[j])
         {
             if (!flag)
             {
                 start = i;
             }
             j++;

             if (oldStr[j] == '\0') 
             {
                 break;
             }
             flag = 1;
         }
         else
         {
             flag = start = j = 0;
         }
         i++;
     }
     if (oldStr[j] == '\0' && flag)
     {
         for (i = 0; i < start; i++) 
         {
             newFileName[i] = fileName[i];
         }
         // replace substring with another string 

         for (j = 0; j < strlen(newStr); j++)
         {
             newFileName[i] = newStr[j];
             i++;
         }
         // copy remaining portion of the input string "str" 

         for (j = start + (int)strlen(oldStr); j < (int)strlen(fileName); j++)
         {
             newFileName[i] = fileName[j];
             i++;
         }
         newFileName[i] = '\0';
     }
     else 
     {
         fprintf(fp, "%s : Can not make a new file\n", fileName);
     }
}
