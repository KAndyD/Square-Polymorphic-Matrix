#include "Square_Matrix_Elem.h" // ������� ����������� �������� �������
#include "Square_Matrix.h" // ��������� ������ � ���������
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <windows.h> // ��� ������������ ����� - ���������-������������� �������

// ������� �������� ������� �� �������
SquareMatrix* createMtrx(int size) {
    if (size <= 0) { // �������� ������������ �������
        fprintf(stderr, "Error: Size must be positive\n");
        return NULL;
    }

    // ��������� ������ ��� ��������� �������
    SquareMatrix* matrix = (SquareMatrix*)malloc(sizeof(SquareMatrix));
    if (!matrix) { // �������� �������������
        fprintf(stderr, "Error: Memory allocation failed for matrix structure\n");
        return NULL;
    }

    matrix->size = size;
    // ��������� ������ ��� �������� �������
    matrix->data = (MatrixElement*)calloc(size * size, sizeof(MatrixElement)); // ���������� calloc ������ malloc
    if (!matrix->data) { // �������� ������ �������
        fprintf(stderr, "Error: Memory allocation failed for matrix data\n");
        free(matrix);
        return NULL;
    }

    // ����� ������������� ���� ���������
    for (int i = 0; i < size * size; ++i) {
        matrix->data[i].data = NULL;
        matrix->data[i].type = NULL; 
    }

    return matrix;
}

// ������� ����������� �������
void destroyMtrx(SquareMatrix* matrix) {
    if (!matrix) return; // ���� ��� ������ ����

    if (matrix->data) { // ���� ����, ��� �������
        // ������������ ������ �����������
        for (int i = 0; i < matrix->size * matrix->size; ++i) {
            // ��������� ����� �����
            if (matrix->data[i].data) {
                free(matrix->data[i].data); // ������������ ������ ��������
                matrix->data[i].data = NULL;
            }
            // type �� ����� �����������, ��� ��� �� ���������� � const
        }
        free(matrix->data); // ������������ ������� ���������
        matrix->data = NULL;
    }

    free(matrix); // ������������ ����� ���������
}

// ��������� �������� ������� �� ������ � �������
void* getElem(const SquareMatrix* matrix, int row, int col) {
    // �������� ������������ ����������
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return NULL;
    }
    // ������ � ���������� �������
    int index = row * matrix->size + col;

    // �������� ������������� ��������
    if (!matrix->data || !matrix->data[index].data) {
        fprintf(stderr, "Error: Element at (%d, %d) is NULL\n", row, col);
        return NULL;
    }

    return matrix->data[index].data; // ����������� �������� �� �������
}

// ��������� �������� ������� �� ������, �������, �������� � ����
int setElem(SquareMatrix* matrix, int row, int col, void* val, const DataType* type) {
    // �������� ������� ����������
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size || !val || !type) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return -1;
    }

    // �������� ������� ������ �������
    if (!matrix->data) {
        fprintf(stderr, "Error: Matrix data is NULL\n");
        return -1;
    }

    int index = row * matrix->size + col;

    // ������������ ������� ��������
    if (matrix->data[index].data) {
        free(matrix->data[index].data);
    }

    // ��������� ������ � ����������� ������
    matrix->data[index].data = malloc(type->size);
    if (!matrix->data[index].data) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }

    // ����������� ����� �������� ������ �� ������ ������� ������ � ������
    // memcpy(����, ������, �������_����);
    memcpy(matrix->data[index].data, val, type->size);

    // ��������� ���� ��������
    matrix->data[index].type = type;

    return 0;
}

// ������� ������ �������
int printMtrx(const SquareMatrix* matrix) {
    // �������� ������� �������
    if (!matrix) {
        fprintf(stderr, "Error: Matrix is NULL\n");
        return -1;
    }

    // �������� ������� ������
    if (!matrix->data) {
        fprintf(stderr, "Error: Matrix data is NULL\n");
        return -1;
    }

    for (int i = 0; i < matrix->size; ++i) {
        for (int j = 0; j < matrix->size; ++j) {
            int index = i * matrix->size + j;
            MatrixElement* element = &matrix->data[index]; // ��������� �������� �� �������

            // �������� ��������
            if (!element || !element->data) {
                printf("NULL ");
                continue;
            }

            // �������� ������� ������� ������
            if (!element->type || !element->type->print) {
                printf("Unprintable ");
            }
            else {
                element->type->print(stdout, element->data); // ����� ��������
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}