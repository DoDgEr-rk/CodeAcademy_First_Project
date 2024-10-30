#define _CRT_SECURE_NO_WARNINGS
#include "dirent_project.h"
#include "FileDirFunctions.h"
#include "VerifyDataFunctions.h"
#include "DataListFunctions.h"
#include "Vector.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

Vector fileVector;
List list;

int main(int argc, char* argv[])
{
    //Enter and change the directory   
    char defaultFolder[] = "C:\\Proba\\";
    char* newFolder;
    
    newFolder = _strdup(defaultFolder);

    if (argc == 2) 
    {
        printf("The argument supplied is %s\n", argv[1]);
        newFolder = _strdup(argv[1]);
    }
    else if (argc > 2)
    {
        printf("Too many arguments supplied.\n");
    }
    else 
    {
        printf("One argument expected.\n");
    }
   
    printf("The argument supplied is %s\n", newFolder);

    changeDir(newFolder);
  
    freeVector(&fileVector);
   
    makeFileVector(newFolder);
    
    FILE* fp;
    fp = fopen("Invoice_ERRORS.txt", "a");
    if (fp == NULL)
    {
       exit(1);
    }
    
 //File name are checked and inserted into the vector
    for (int h = 0; h < fileVector.size; h++) 
    {   
        int isTheFileNameCorrect = checkFileNameIsCorrect(fileVector.data[h], fp);

        if (isTheFileNameCorrect == 0) 
        {
            removeAt(&fileVector, h);
            h--;
        }        
    }

 //Verify fail data and remake the vector            
    for (int h = 0; h < fileVector.size; h++) 
    {
        FILE* fpNew;
        fpNew = fopen(fileVector.data[h], "r");
        if (fpNew == NULL)
        {
            exit(1);
        }

        int result_rows = countRowsInFile(fpNew);
        fseek(fpNew, 0L, SEEK_SET);
        
        int resultDataFormat = checkFormatData(fpNew, fileVector.data[h], fp, result_rows);
                
        fseek(fpNew, 0L, SEEK_SET);
        fclose(fpNew);

            if (resultDataFormat == 0)
            {
                renameFileExtensionKO(fileVector.data[h], fp);
                removeAt(&fileVector, h);
                h--;
            }
    }

 //Sort the file data in list and copy in new fail
    for (int h = 0; h < fileVector.size; h++)
    {
        FILE* fpNew;
        fpNew = fopen(fileVector.data[h], "r");
        if (fpNew == NULL)
        {
            exit(1);
        }

        list.head = NULL;
        list.tail = NULL;

        addValidDataInList(fpNew, &list, fileVector.data[h]);
        sortListBySum(&list);
        
        char newFileName[100] = { '\0' };

        makeNewFile(fileVector.data[h],newFileName, fp );

        FILE* fpNewOkFile;
        fpNewOkFile = fopen(newFileName, "w");
        if (fpNewOkFile == NULL)
        {
            exit(1);
        }
        writeToFile(fpNewOkFile, &list);        
        fclose(fpNewOkFile);
        fclose(fpNew);
        fprintf(fp, "%s : The file is PERFECT\n", fileVector.data[h]);
        renameFileExtension(fileVector.data[h], fp);
    }
    
    fclose(fp);
    
    printf("\nThe program completed successfully.\n");

    return 0;
}
