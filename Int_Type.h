#ifndef INT_TYPE_H
#define INT_TYPE_H

#include "Square_Matrix_Elem.h"

// ������� �������� ��� int
void IntAdd(void* result, const void* a, const void* b); // ��������
void IntMultiply(void* result, const void* a, const void* b); // ���������
void IntScalarMultiply(void* result, const void* elem, const void* scalar); // ��������� �� ������
void IntPrint(FILE* file, const void* data); // �����
int IntRead(FILE* file, void* data); // ������

// ���������� ��� ������ ��� int
extern const DataType IntType;

#endif