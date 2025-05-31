#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "Square_Matrix.h"
#include <stdio.h>

// ������� ������ ������� �� �����
SquareMatrix* readMatrixFromFile(FILE* file, int size, const DataType* type);

// ������� ������ ������� � ����
void writeMatrixToFile(const SquareMatrix* matrix, const char* filename);

// ������� ������ ���� ������ �� �����
const DataType* readTypeFromFile(FILE* file);

#endif