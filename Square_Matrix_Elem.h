#ifndef SQUARE_MATRIX_ELEM_H
#define SQUARE_MATRIX_ELEM_H

#include <stdio.h> // ����
#include <stdlib.h> // ������

// ���������, ����������� ��������� ��� ������ � ���������� ����� ������
typedef struct DataType {
    const char* name; // ��� ����

    // ������� �������� ���� ���������
    void (*add)(void* result, const void* a, const void* b);
    
    // ������� ��������� ���� ���������
    void (*multiply)(void* result, const void* a, const void* b);
    
    // ������� ��������� �������� �� ������
    void (*scalarMultiply)(void* result, const void* elem, const void* scalar);
    
    // ������� ������ �������� � ����
    void (*print)(FILE* file, const void* data);
    
    // ������� ������ �������� � ����
    int (*read)(FILE* file, void* data);
    
    // ������ �������� � ������
    size_t size;
} DataType;


// ������� �������
typedef struct {
	void* data; // ��������� �� ������
	const DataType* type; // ��������� �� �������� ���� ������
} MatrixElement;

// ��������� �������������� ����� ���� ������ � �������� �� �� �����
typedef struct TypeRegistry {
    const DataType** types; // ������ ��������� �� ������������������ ����
    size_t count; // ���������� ������������������ �����
    size_t capacity; // ������� ����������� �������
} TypeRegistry;

// ���������� ������ ����� 
extern TypeRegistry typeRegistry;

// ������� ��� ������ � ��������
void registerDataType(const DataType* type); // ������������� ����� ��� ������ � �������
const DataType* findDataTypeByName(const char* name); // ���������� ���� ������ �� �����

#endif