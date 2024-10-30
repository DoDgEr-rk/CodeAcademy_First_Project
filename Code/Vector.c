#define _CRT_SECURE_NO_WARNINGS
#include"Vector.h"
#include "FileDirFunctions.h"
#include "dirent_project.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Vector fileVector;

void initVector(Vector* v) 
{
	v->size = 0;
	v->capacity = 10;
	v->data = (char**)malloc(sizeof(char*) * v->capacity);

    if (v->data == NULL) 
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
}
void pushBackVector(Vector* v, char* elem) 
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        //new_data realloc
        v->data = (char**)realloc(v->data, sizeof(char*) * v->capacity);

        if (v->data == NULL)
        {
            fprintf(stderr, "Error reallocating memory\n");
            exit(EXIT_FAILURE);
        }
    }

    size_t elem_len = strlen(elem);
    v->data[v->size] = (char*)malloc(elem_len + 1);

    if (v->data[v->size] == NULL)
    {
        fprintf(stderr, "Error allocating memory for string\n");
        exit(EXIT_FAILURE);
    }
    strcpy(v->data[v->size], elem);
    v->size++;
}
void freeVector(Vector* v) 
{
    for (int i = 0; i < v->size; i++) 
    {
        free(v->data[i]);
    }
    free(v->data);
}
void popBackVector(Vector* v) 
{
    if (v->size > 0)
    {
        v->size--;
    }
}
char* getVector(Vector* v, int index) 
{
    if (index >= 0 && index < v->size)
    {
        return v->data[index];
    }

    return NULL;
}
void printVectorFront(Vector* v) 
{
    if (v->size == 0)
    {
        printf("Error: Vector is empty.\n");
        return;
    }

    free(v->data[0]);

    for (int i = 1; i < v->size; i++) 
    {
       printf("%s\n", v->data[i - 1] = v->data[i]);
    }
}
void removeAt(Vector* v, int index) 
{
    if (index < 0 || index >= v->size)
    {
        printf("Invalid index\n");
        return;
    }
    for (int i = index; i < v->size - 1; i++) 
    {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}
void makeFileVector(const char* newFolder)
{
    DIR* d;
    struct dirent* dir;
    d = opendir(newFolder);

    char fullPath[1000] = { '\0' };
    int count = 0;

    if (d)
    {
        initVector(&fileVector);
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                fullPath[0] = '\0';
                strcat(fullPath, newFolder);
                strcat(fullPath, dir->d_name);

                if (dir->d_type == DT_REG)
                {
                    pushBackVector(&fileVector, dir->d_name);
                }
                count++;
            }
        }
        closedir(d);
    }
}