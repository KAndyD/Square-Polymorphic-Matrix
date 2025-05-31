#ifndef DOUBLE_TYPE_H
#define DOUBLE_TYPE_H

#include "Square_Matrix_Elem.h"

// ������� �������� ��� double
void DoubleAdd(void* result, const void* a, const void* b);
void DoubleMultiply(void* result, const void* a, const void* b);
void DoubleScalarMultiply(void* result, const void* elem, const void* scalar);
void DoublePrint(FILE* file, const void* data);
int DoubleRead(FILE* file, void* data);

// ���������� ��� ������ ��� double
extern const DataType DoubleType;

#endif