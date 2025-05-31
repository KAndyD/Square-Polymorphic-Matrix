#include "Square_Matrix_Elem.h"
#include "Square_Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �������� ������
SquareMatrix* addMtrx(const SquareMatrix* matrix1, const SquareMatrix* matrix2) {
    // �������� ������� ����������
    if (!matrix1 || !matrix2 || matrix1->size != matrix2->size) {
        fprintf(stderr, "Error: Invalid matrices for addition\n");
        return NULL;
    }

    // �������� �������������� �������
    SquareMatrix* result = createMtrx(matrix1->size);
    if (!result) { // �������� �� �������������
        return NULL;
    }

    // ������������ ��������
    for (int i = 0; i < matrix1->size; i++) {
        for (int j = 0; j < matrix1->size; j++) {
            MatrixElement* elem1 = &matrix1->data[i * matrix1->size + j]; // �� ����������� �������
            MatrixElement* elem2 = &matrix2->data[i * matrix1->size + j];

            // �������� ������������� ���������
            if (!elem1 || !elem2 || elem1->type != elem2->type) {
                fprintf(stderr, "Error: Incompatible matrix elements for addition\n");
                destroyMtrx(result);
                return NULL;
            }
            // ��� ���������
            const DataType* type = elem1->type;
            if (!type || !type->add) {
                fprintf(stderr, "Error: Addition not supported for this type\n");
                destroyMtrx(result);
                return NULL;
            }

            // ��������� ������ ��� ����������
            void* sum = malloc(type->size);
            if (!sum) {
                fprintf(stderr, "Error: Memory allocation failed for sum\n");
                destroyMtrx(result);
                return NULL;
            }

            // ���������� �������� ����� ������� add �� ����� ������
            type->add(sum, elem1->data, elem2->data);

            // ��������� ����������
            if (setElem(result, i, j, sum, type) != 0) {
                fprintf(stderr, "Error: Failed to set element in result matrix\n");
                free(sum);
                destroyMtrx(result);
                return NULL;
            }

            // ������������ �����
            free(sum);
        }
    }

    return result;
}

// ��������� ������� �� ������
SquareMatrix* scalarMultiply(const SquareMatrix* matrix, void* scalar, const DataType* scalarType) {
    // �������� �� ������������ ��������� ������
    if (!matrix || !scalar || !scalarType) {
        fprintf(stderr, "Error: Invalid arguments for scalar multiplication\n");
        return NULL;
    }

    // �������� �������������� �������
    SquareMatrix* result = createMtrx(matrix->size);
    if (!result) {
        return NULL;
    }

    // ������������ ���������
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            MatrixElement* element = &matrix->data[i * matrix->size + j];
            const DataType* type = element->type; // ��� ��������

            // ���� ���� ������
            if (!type || !type->scalarMultiply) {
                fprintf(stderr, "Error: Scalar multiplication not supported for this type\n");
                destroyMtrx(result);
                return NULL;
            }

            // �������� ������ ��� �������� ����������
            void* product = malloc(type->size);
            if (!product) {
                fprintf(stderr, "Error: Memory allocation failed for product\n");
                destroyMtrx(result);
                return NULL;
            }

            // ��������� �� �������, ����������� ��� ������� ���� ������
            type->scalarMultiply(product, element->data, scalar);

            // ��������� ����������
            if (setElem(result, i, j, product, type) != 0) {
                fprintf(stderr, "Error: Failed to set element in result matrix\n");
                free(product);
                destroyMtrx(result);
                return NULL;
            }

            // ������������ ����������
            free(product);
        }
    }

    return result;
}

// ������� ��������� ������
SquareMatrix* multiplyMtrx(const SquareMatrix* matrix1, const SquareMatrix* matrix2) {
    // �������� ������������ ����� ������
    if (!matrix1 || !matrix2 || matrix1->size != matrix2->size) {
        fprintf(stderr, "Error: Invalid matrices for multiplication\n");
        return NULL;
    }

    // ������ �������
    int size = matrix1->size;
    SquareMatrix* result = createMtrx(size);
    if (!result) {
        return NULL;
    }

    // ��� ������(�� ������� ��������)
    const DataType* type = matrix1->data[0].type;
    if (!type || !type->multiply || !type->add) {
        fprintf(stderr, "Error: Operations not supported for this type\n");
        destroyMtrx(result);
        return NULL;
    }

    for (int i = 0; i < size; ++i) { // ������
        for (int j = 0; j < size; ++j) { // �������
            // ��������� ������ ��� ������������ � ���������
            // ����������� = ����������, � ������� ������������� ��������� ��������� ���������� ���������
            void* accumulator = malloc(type->size);
            if (!accumulator) {
                fprintf(stderr, "Memory allocation failed for accumulator at [%d][%d]\n", i, j);
                destroyMtrx(result);
                return NULL;
            }

            // ������������� ������������ ������ � ��������� �������
            if (type->size > 0) {
                memset(accumulator, 0, type->size);
            }

            for (int k = 0; k < size; ++k) {
                // ��������� ��������� ��� ���������
                MatrixElement* elem1 = &matrix1->data[i * size + k];
                MatrixElement* elem2 = &matrix2->data[k * size + j];

                // �������� ��������� �������
                if (!elem1 || !elem2 || !elem1->data || !elem2->data) {
                    fprintf(stderr, "Error: NULL element in matrix at [%d][%d] or [%d][%d]\n", i, k, k, j);
                    free(accumulator);
                    destroyMtrx(result);
                    return NULL;
                }

                // ��������� ������ ��� ������������ � ���������
                void* product = malloc(type->size);
                if (!product) {
                    fprintf(stderr, "Memory allocation failed for product at [%d][%d][%d]\n", i, j, k);
                    free(accumulator);
                    destroyMtrx(result);
                    return NULL;
                }

                // ���������� ��������
                type->multiply(product, elem1->data, elem2->data);
                type->add(accumulator, accumulator, product);

                free(product);
            }

            // ��������� ���������� � ���������
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

// ������� ���������������� �������
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
            MatrixElement* src = &matrix->data[i * size + j]; // ������� �������� �������
            MatrixElement* dest = &result->data[j * size + i]; // ������� �������������� �������

            // �������� ��������� ��������
            if (!src || !src->type || !src->data) {
                fprintf(stderr, "Error: Invalid source element at [%d][%d]\n", i, j);
                destroyMtrx(result);
                return NULL;
            }

            // ������������� ��������-����������
            dest->type = src->type;
            dest->data = malloc(src->type->size);

            if (!dest->data) {
                fprintf(stderr, "Error: Memory allocation failed for element [%d][%d]\n", j, i);
                destroyMtrx(result);
                return NULL;
            }

            // ����������� ������
            memcpy(dest->data, src->data, src->type->size);
        }
    }

    return result;
}