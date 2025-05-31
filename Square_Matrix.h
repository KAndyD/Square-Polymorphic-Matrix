#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "Square_Matrix_Elem.h"


// c��������, �������������� ���������� �������
typedef struct {
	int size; // N * N
	MatrixElement* data; // ��������� ������ ������ - ��������� �� ������
} SquareMatrix;


// ������� �������� �������
SquareMatrix* createMtrx(int size);

// ������� �������� �������
void destroyMtrx(SquareMatrix* matrix);

// ��������� �������� ������� �� ������ � �������(������)
void* getElem(const SquareMatrix* matrix, int row, int col);

// ��������� �������� ������� �� ������, ������� � value(� ����� ��� �� ������)
// ���������� ��� ���������� ��������� ������(������, ��������)
int setElem(SquareMatrix* matrix, int row, int col, void* val, const DataType* type);

// ������� ������ �������
int printMtrx(const SquareMatrix* matrix);

// ������� �������� ���� ������
SquareMatrix* addMtrx(const SquareMatrix* a, const SquareMatrix* b);

// ������� ��������� ������
SquareMatrix* multiplyMtrx(const SquareMatrix* a, const SquareMatrix* b);

// ������� ��������� ������� �� ������
SquareMatrix* scalarMultiply(const SquareMatrix* matrix, void* scalar, const DataType* scalarType);

// ������� ���������������� �������
SquareMatrix* transposeMtrx(const SquareMatrix* matrix);

#endif