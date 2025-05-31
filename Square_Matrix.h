#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "Square_Matrix_Elem.h"


// cтруктура, представл€юща€ квадратную матрицу
typedef struct {
	int size; // N * N
	MatrixElement* data; // двумерный массив массив - указатель на данные
} SquareMatrix;


// функци€ создани€ матрицы
SquareMatrix* createMtrx(int size);

// функци€ геноцида матрицы
void destroyMtrx(SquareMatrix* matrix);

// получение элемента матрицы по строке и столбцу(геттер)
void* getElem(const SquareMatrix* matrix, int row, int col);

// установка элемента матрицы по строке, столбцу и value(€ забыл как по русски)
// необходимо дл€ правильной обработки данных(пам€ть, например)
int setElem(SquareMatrix* matrix, int row, int col, void* val, const DataType* type);

// функци€ вывода матрицы
int printMtrx(const SquareMatrix* matrix);

// функци€ сложени€ двух матриц
SquareMatrix* addMtrx(const SquareMatrix* a, const SquareMatrix* b);

// функци€ умножени€ матриц
SquareMatrix* multiplyMtrx(const SquareMatrix* a, const SquareMatrix* b);

// функци€ умножени€ матрицы на скал€р
SquareMatrix* scalarMultiply(const SquareMatrix* matrix, void* scalar, const DataType* scalarType);

// функци€ транспонировани€ матрицы
SquareMatrix* transposeMtrx(const SquareMatrix* matrix);

#endif