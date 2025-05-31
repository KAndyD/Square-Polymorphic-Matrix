#ifndef STRING_H
#define STRING_H

#include "Square_Matrix_Elem.h" // Для DataType
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структура строки
typedef struct {
    char* data; // указатель на данные строки
    size_t length; // длина строки
} String;

// создание и удаление
String* CreateString(size_t length, const char* initial_value);
void StringDelete(String* str);

// функции для DataType
void StringAdd(void* result, const void* a, const void* b);
void StringMultiply(void* result, const void* a, const void* b);
void StringPrint(FILE* file, const void* data);
int StringRead(FILE* file, void* data);

// глобальный тип данных для строк
extern const DataType StringType;

#endif