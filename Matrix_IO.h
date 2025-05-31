#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "Square_Matrix.h"
#include <stdio.h>

// функция чтения матрицы из файла
SquareMatrix* readMatrixFromFile(FILE* file, int size, const DataType* type);

// функция записи матрицы в файл
void writeMatrixToFile(const SquareMatrix* matrix, const char* filename);

// функция чтения типа данных из файла
const DataType* readTypeFromFile(FILE* file);

#endif