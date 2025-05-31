/*#ifndef TYPE_FUNCTIONS_H
#define TYPE_FUNCTIONS_H

#include "Square_Matrix_Elem.h" // ��, ��� ��������� data_t


// GenericAddFunction: ��������� �� ������� �������� ���� ���������
// GenericScalarMultiplyFunction: ��������� �� ������� ��������� �������� �� ������
// GenericElementMultiplyFunction : ��������� �� ������� ��������� ���� ���������
typedef void (*GenericAddFunction)(void* result, const void* a, const void* b);
typedef void (*GenericScalarMultiplyFunction)(void* result, const void* matrixElement, const void* scalar);
typedef void (*GenericElementMultiplyFunction)(void* result, const void* a, const void* b);


// c��������, ���������� ��������� �� �������
typedef struct {
    data_t type; // ������������� ����
    char* name; // ��������� ��� ����
    GenericAddFunction addFunction; // ������� ��������
    GenericScalarMultiplyFunction scalarMultiplyFunction; // ������� ��������� �� ������
    GenericElementMultiplyFunction elementMultiplyFunction; // ������� ���������
    size_t elementSize; // ������ �������� � ������
    void (*writeFunction)(FILE*, void*); // ������� ������
    int (*readFunction)(FILE*, void*); // ������� ������
} TypeFunctions;

// ������� ��� ��������� ��������� TypeFunctions �� ����� ���� ������
TypeFunctions* getTypeFunctions(data_t type);

// ��������� ������� ������
void writeInt(FILE* file, void* data);
void writeDouble(FILE* file, void* data);
void writeComplex(FILE* file, void* data);
void writeString(FILE* file, void* data);

// ��������� ������� ������
int readInt(FILE* file, void* data);
int readDouble(FILE* file, void* data);
int readComplex(FILE* file, void* data);
int readString(FILE* file, void* data);

#endif*/