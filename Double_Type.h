#ifndef DOUBLE_TYPE_H
#define DOUBLE_TYPE_H

#include "Square_Matrix_Elem.h"

// функции операций для double
void DoubleAdd(void* result, const void* a, const void* b);
void DoubleMultiply(void* result, const void* a, const void* b);
void DoubleScalarMultiply(void* result, const void* elem, const void* scalar);
void DoublePrint(FILE* file, const void* data);
int DoubleRead(FILE* file, void* data);

// глобальный тип данных для double
extern const DataType DoubleType;

#endif