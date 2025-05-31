#define _CRT_SECURE_NO_WARNINGS
#include "Matrix_IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ���������� ������ ����� ������
 * ������ ��� ������������������ � ������� ���� ��������� ���������
 * ���������������� ������ (NULL, 0, 0) ��� ������ ���������
 * - types: ������ ���������� �� ������������������ ����
 * - count: ������� ���������� �����
 * - capacity: ������� ����������� �������
 */
TypeRegistry typeRegistry = { NULL, 0, 0 };

// ����������� ������ ���� ������ � �������
void registerDataType(const DataType* type) {
    // ����������� ����� ��� �������������
    if (typeRegistry.count >= typeRegistry.capacity) {
        // ����������� ������� � 2 ���� ��� �� 4 (���� ���� 0)
        size_t new_capacity = typeRegistry.capacity ? typeRegistry.capacity * 2 : 4;
        
        // ������������ ������ � ����� ��������
        const DataType** new_types = realloc(typeRegistry.types, new_capacity * sizeof(DataType*));
        
        if (!new_types) return;

        typeRegistry.types = new_types;
        typeRegistry.capacity = new_capacity;
    }

    // ��������� ��� � ������
    typeRegistry.types[typeRegistry.count++] = type;
}

// ������� ���������� ���� ������ �� �����
const DataType* findDataTypeByName(const char* name) {
    // �������� ����� �� ���� ������������������ �����
    for (size_t i = 0; i < typeRegistry.count; i++) {
        if (strcmp(typeRegistry.types[i]->name, name) == 0) {
            return typeRegistry.types[i]; // ��� ������
        }
    }
    return NULL; // ��� �� ������
}

// ������� ������ ������� �� �����
SquareMatrix* readMatrixFromFile(FILE* file, int size, const DataType* type) {
    // �������� ������������ ������� ����������
    if (!file || size <= 0 || !type) {
        fprintf(stderr, "Invalid arguments to readMatrixFromFile\n");
        return NULL;
    }

    printf("Reading matrix of type %s, size %dx%d\n", type->name, size, size);

    // �������� �������
    SquareMatrix* matrix = createMtrx(size);
    if (!matrix) return NULL; // �������� ��������� ��������

    // ������ ��������� �������
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            MatrixElement* elem = &matrix->data[i * size + j];
            elem->type = type; // ��������� ���� ��������
            
            // ��������� ������ ��� ������ ��������
            elem->data = malloc(type->size);

            if (!elem->data) {
                fprintf(stderr, "Memory allocation failed for element [%d][%d]\n", i, j);
                destroyMtrx(matrix);
                return NULL;
            }

            printf("Reading [%d][%d] as %s...", i, j, type->name);
            // ������������� ������� ������ ��� ����������� ����
            if (!type->read(file, elem->data)) {
                fprintf(stderr, "Failed to read value at [%d][%d]\n", i, j);
                destroyMtrx(matrix);
                return NULL;
            }
            printf("Success\n");
        }
    }
    return matrix;
}

// ������� ������ ������� � ����
void writeMatrixToFile(const SquareMatrix* matrix, const char* filename) {
    // �������� ������� ����������
    if (!filename) {
        fprintf(stderr, "Error: NULL filename in writeMatrixToFile\n");
        return;
    }

    // �������� ����� ��� ������
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    // ��������� ������ � ������ ��������
    if (!matrix) {
        fprintf(file, "Matrix is NULL\n");
        fclose(file);
        return;
    }

    // ������������ ������
    for (int i = 0; i < matrix->size; ++i) {
        for (int j = 0; j < matrix->size; ++j) {
            MatrixElement* elem = &matrix->data[i * matrix->size + j];

            if (!elem->type || !elem->type->print) {
                fprintf(file, "Unprintable ");
            }
            else {
                elem->type->print(file, elem->data);
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// ������� ������ ���� ������ �� �����
const DataType* readTypeFromFile(FILE* file) {
    char type_str[20];
    // ������ ������ � ������ ����
    if (fscanf(file, "%19s", type_str) != 1) {
        fprintf(stderr, "Error reading type from file\n");
        return NULL;
    }
    type_str[19] = '\0'; // ��������������� ���������� ������

    // ����� ���� � �������
    const DataType* type = findDataTypeByName(type_str);
    if (!type) {
        fprintf(stderr, "Unknown type: %s\n", type_str);
    }
    return type;
}