#ifndef COMPLEX_H
#define COMPLEX_H

#include "Square_Matrix_Elem.h"

typedef struct ComplexNumber {
    double real;
    double imag;
} ComplexNumber;

// операции для DataType
void ComplexAdd(void* result, const void* a, const void* b);
void ComplexMultiply(void* result, const void* a, const void* b);
void ComplexScalarMultiply(void* result, const void* elem, const void* scalar);
void ComplexPrint(FILE* file, const void* data);
int ComplexRead(FILE* file, void* data);

// глобальный тип данных
extern const DataType ComplexType;

#endif