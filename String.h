#ifndef STRING_H
#define STRING_H

#include "Square_Matrix_Elem.h" // ��� DataType
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ������
typedef struct {
    char* data; // ��������� �� ������ ������
    size_t length; // ����� ������
} String;

// �������� � ��������
String* CreateString(size_t length, const char* initial_value);
void StringDelete(String* str);

// ������� ��� DataType
void StringAdd(void* result, const void* a, const void* b);
void StringMultiply(void* result, const void* a, const void* b);
void StringPrint(FILE* file, const void* data);
int StringRead(FILE* file, void* data);

// ���������� ��� ������ ��� �����
extern const DataType StringType;

#endif