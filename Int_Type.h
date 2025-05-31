#ifndef INT_TYPE_H
#define INT_TYPE_H

#include "Square_Matrix_Elem.h"

// функции операций для int
void IntAdd(void* result, const void* a, const void* b); // сложение
void IntMultiply(void* result, const void* a, const void* b); // умножение
void IntScalarMultiply(void* result, const void* elem, const void* scalar); // умножение на скаляр
void IntPrint(FILE* file, const void* data); // вывод
int IntRead(FILE* file, void* data); // чтение

// глобальный тип данных для int
extern const DataType IntType;

#endif