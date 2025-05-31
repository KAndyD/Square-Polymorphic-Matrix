#include "Square_Matrix_Elem.h"
#include "Square_Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// сложение матриц
SquareMatrix* addMtrx(const SquareMatrix* matrix1, const SquareMatrix* matrix2) {
    // проверка входных параметров
    if (!matrix1 || !matrix2 || matrix1->size != matrix2->size) {
        fprintf(stderr, "Error: Invalid matrices for addition\n");
        return NULL;
    }

    // создание результирующей матрицы
    SquareMatrix* result = createMtrx(matrix1->size);
    if (!result) { // проверка ее существования
        return NULL;
    }

    // поэлементное сложение
    for (int i = 0; i < matrix1->size; i++) {
        for (int j = 0; j < matrix1->size; j++) {
            MatrixElement* elem1 = &matrix1->data[i * matrix1->size + j]; // по одномерному индексу
            MatrixElement* elem2 = &matrix2->data[i * matrix1->size + j];

            // проверка совместимости элементов
            if (!elem1 || !elem2 || elem1->type != elem2->type) {
                fprintf(stderr, "Error: Incompatible matrix elements for addition\n");
                destroyMtrx(result);
                return NULL;
            }
            // тип элементов
            const DataType* type = elem1->type;
            if (!type || !type->add) {
                fprintf(stderr, "Error: Addition not supported for this type\n");
                destroyMtrx(result);
                return NULL;
            }

            // выделение памяти для результата
            void* sum = malloc(type->size);
            if (!sum) {
                fprintf(stderr, "Error: Memory allocation failed for sum\n");
                destroyMtrx(result);
                return NULL;
            }

            // выполнение сложения через функцию add от типов данных
            type->add(sum, elem1->data, elem2->data);

            // установка результата
            if (setElem(result, i, j, sum, type) != 0) {
                fprintf(stderr, "Error: Failed to set element in result matrix\n");
                free(sum);
                destroyMtrx(result);
                return NULL;
            }

            // освобождение суммы
            free(sum);
        }
    }

    return result;
}

// умножение матрицы на скаляр
SquareMatrix* scalarMultiply(const SquareMatrix* matrix, void* scalar, const DataType* scalarType) {
    // проверка на корректность введенных данных
    if (!matrix || !scalar || !scalarType) {
        fprintf(stderr, "Error: Invalid arguments for scalar multiplication\n");
        return NULL;
    }

    // создание результирующей матрицы
    SquareMatrix* result = createMtrx(matrix->size);
    if (!result) {
        return NULL;
    }

    // поэлементное умножение
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            MatrixElement* element = &matrix->data[i * matrix->size + j];
            const DataType* type = element->type; // тип элемента

            // если типы разные
            if (!type || !type->scalarMultiply) {
                fprintf(stderr, "Error: Scalar multiplication not supported for this type\n");
                destroyMtrx(result);
                return NULL;
            }

            // создания буфера для хранения результата
            void* product = malloc(type->size);
            if (!product) {
                fprintf(stderr, "Error: Memory allocation failed for product\n");
                destroyMtrx(result);
                return NULL;
            }

            // указатель на функцию, специфичную для данного типа данных
            type->scalarMultiply(product, element->data, scalar);

            // установка результата
            if (setElem(result, i, j, product, type) != 0) {
                fprintf(stderr, "Error: Failed to set element in result matrix\n");
                free(product);
                destroyMtrx(result);
                return NULL;
            }

            // освобождение результата
            free(product);
        }
    }

    return result;
}

// функция умножения матриц
SquareMatrix* multiplyMtrx(const SquareMatrix* matrix1, const SquareMatrix* matrix2) {
    // проверка корректности ввода данных
    if (!matrix1 || !matrix2 || matrix1->size != matrix2->size) {
        fprintf(stderr, "Error: Invalid matrices for multiplication\n");
        return NULL;
    }

    // размер матрицы
    int size = matrix1->size;
    SquareMatrix* result = createMtrx(size);
    if (!result) {
        return NULL;
    }

    // тип данных(по первому элементу)
    const DataType* type = matrix1->data[0].type;
    if (!type || !type->multiply || !type->add) {
        fprintf(stderr, "Error: Operations not supported for this type\n");
        destroyMtrx(result);
        return NULL;
    }

    for (int i = 0; i < size; ++i) { // строки
        for (int j = 0; j < size; ++j) { // столбцы
            // выделение памяти для аккумулятора с проверкой
            // аккумулятор = переменная, в которой накапливается результат умножения конкретных элементов
            void* accumulator = malloc(type->size);
            if (!accumulator) {
                fprintf(stderr, "Memory allocation failed for accumulator at [%d][%d]\n", i, j);
                destroyMtrx(result);
                return NULL;
            }

            // инициализация аккумулятора нулями с проверкой размера
            if (type->size > 0) {
                memset(accumulator, 0, type->size);
            }

            for (int k = 0; k < size; ++k) {
                // получение элементов для умножения
                MatrixElement* elem1 = &matrix1->data[i * size + k];
                MatrixElement* elem2 = &matrix2->data[k * size + j];

                // проверка элементов матрицы
                if (!elem1 || !elem2 || !elem1->data || !elem2->data) {
                    fprintf(stderr, "Error: NULL element in matrix at [%d][%d] or [%d][%d]\n", i, k, k, j);
                    free(accumulator);
                    destroyMtrx(result);
                    return NULL;
                }

                // выделение памяти для произведения с проверкой
                void* product = malloc(type->size);
                if (!product) {
                    fprintf(stderr, "Memory allocation failed for product at [%d][%d][%d]\n", i, j, k);
                    free(accumulator);
                    destroyMtrx(result);
                    return NULL;
                }

                // выполнение операций
                type->multiply(product, elem1->data, elem2->data);
                type->add(accumulator, accumulator, product);

                free(product);
            }

            // установка результата с проверкой
            if (setElem(result, i, j, accumulator, type) != 0) {
                fprintf(stderr, "Failed to set element at [%d][%d]\n", i, j);
                free(accumulator);
                destroyMtrx(result);
                return NULL;
            }

            free(accumulator);
        }
    }

    return result;
}

// функция транспонирование матрицы
SquareMatrix* transposeMtrx(const SquareMatrix* matrix) {
    if (!matrix) {
        fprintf(stderr, "Error: Matrix is NULL in transposeMtrx\n");
        return NULL;
    }

    int size = matrix->size;
    SquareMatrix* result = createMtrx(size);
    if (!result) {
        fprintf(stderr, "Error: Failed to create transposed matrix\n");
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            MatrixElement* src = &matrix->data[i * size + j]; // элемент исходной матрицы
            MatrixElement* dest = &result->data[j * size + i]; // элемент результирующей матрицы

            // проверка исходного элемента
            if (!src || !src->type || !src->data) {
                fprintf(stderr, "Error: Invalid source element at [%d][%d]\n", i, j);
                destroyMtrx(result);
                return NULL;
            }

            // инициализация элемента-назначения
            dest->type = src->type;
            dest->data = malloc(src->type->size);

            if (!dest->data) {
                fprintf(stderr, "Error: Memory allocation failed for element [%d][%d]\n", j, i);
                destroyMtrx(result);
                return NULL;
            }

            // копирование данных
            memcpy(dest->data, src->data, src->type->size);
        }
    }

    return result;
}