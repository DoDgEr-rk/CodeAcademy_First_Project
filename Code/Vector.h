#ifndef VEC_H
#define VEC_H

typedef struct Vector {
	int size;
	int capacity;
	char** data;
}Vector;

void makeFileVector(const char* New_Folder);
void initVector(Vector* v);
void pushBackVector(Vector* v, char* elem);
void popBackVector(Vector* v);
char* getVector(Vector* v, int index);
void freeVector(Vector* v);
void printVectorFront(Vector* v);
void removeAt(Vector* v, int index);

#endif