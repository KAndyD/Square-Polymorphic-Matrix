#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Square_Matrix.h"
#include "Square_Matrix_Elem.h"
#include "complex.h"
#include "String.h"
#include "Matrix_IO.h"
#include "Int_Type.h"
#include "Double_Type.h"


// внешние объ€влени€ типов
extern const DataType IntType;
extern const DataType DoubleType;
extern const DataType ComplexType;
extern const DataType StringType;

// функци€ создани€ матрицы(интерактивного)
SquareMatrix* createMatrixInteractive() {
    int size;
    char type_str[20];
    const DataType* type = NULL;

    printf("Enter matrix size (N for NxN matrix): ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid matrix size\n");
        return NULL;
    }

    printf("Enter matrix type (INT/DOUBLE/COMPLEX/STRING): ");
    if (scanf("%19s", type_str) != 1) {
        fprintf(stderr, "Error reading matrix type\n");
        return NULL;
    }

    type_str[19] = '\0';
    // определение типа
    if (strcmp(type_str, "INT") == 0) type = &IntType;
    else if (strcmp(type_str, "DOUBLE") == 0) type = &DoubleType;
    else if (strcmp(type_str, "COMPLEX") == 0) type = &ComplexType;
    else if (strcmp(type_str, "STRING") == 0) type = &StringType;
    else {
        fprintf(stderr, "Unknown matrix type\n");
        return NULL;
    }

    SquareMatrix* matrix = createMtrx(size);
    if (!matrix) return NULL;

    printf("Enter %dx%d matrix elements:\n", size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("Element [%d][%d]: ", i, j);

            void* data = malloc(type->size);
            if (!data || !type->read(stdin, data)) {
                fprintf(stderr, "Error reading element [%d][%d]\n", i, j);
                free(data);
                destroyMtrx(matrix);
                return NULL;
            }

            if (setElem(matrix, i, j, data, type) != 0) {
                free(data);
                destroyMtrx(matrix);
                return NULL;
            }
            free(data);
        }
    }

    return matrix;
}

int main() {
    FILE* file = fopen("test.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening test.txt\n");
        return 1;
    }

    SquareMatrix* matrix1 = NULL, * matrix2 = NULL, * result = NULL;

    while (!feof(file)) {
        // чтение первой матрицы
        int size;
        if (fscanf(file, "%d", &size) != 1) break;

        const DataType* type = readTypeFromFile(file);
        if (!type) {
            fprintf(stderr, "Error reading matrix type\n");
            break;
        }

        matrix1 = readMatrixFromFile(file, size, type);
        if (!matrix1) {
            fprintf(stderr, "Error reading matrix from file\n");
            break;
        }

        // чтение операции
        char operation[20];
        if (fscanf(file, "%19s", operation) != 1) {
            fprintf(stderr, "Error reading operation\n");
            break;
        }

        operation[19] = '\0';
        // обработка операции
        if (strcmp(operation, "add") == 0 || strcmp(operation, "multiply") == 0) {
            // чтение второй матрицы
            int size2;
            if (fscanf(file, "%d", &size2) != 1) {
                fprintf(stderr, "Error reading second matrix size\n");
                break;
            }

            const DataType* type2 = readTypeFromFile(file);
            if (!type2) {
                fprintf(stderr, "Error reading second matrix type\n");
                break;
            }

            matrix2 = readMatrixFromFile(file, size2, type2);
            if (!matrix2) {
                fprintf(stderr, "Error reading second matrix\n");
                break;
            }

            if (strcmp(operation, "add") == 0) {
                result = addMtrx(matrix1, matrix2);
            }
            else {
                result = multiplyMtrx(matrix1, matrix2);
            }
        }
        else if (strcmp(operation, "scalarMultiply") == 0) {
            double scalar;
            if (fscanf(file, "%lf", &scalar) != 1) {
                fprintf(stderr, "Error reading scalar value\n");
                break;
            }
            result = scalarMultiply(matrix1, &scalar, &DoubleType);
        }
        else if (strcmp(operation, "transpose") == 0) {
            result = transposeMtrx(matrix1);
        }
        else {
            fprintf(stderr, "Unknown operation: %s\n", operation);
            break;
        }

        // чтение имени файла дл€ результата
        char filename[50];
        if (fscanf(file, "%49s", filename) != 1) {
            fprintf(stderr, "Error reading output filename\n");
            break;
        }

        // запись результата
        if (result) {
            writeMatrixToFile(result, filename);
            destroyMtrx(result);
            result = NULL;
        }

        // очистка
        destroyMtrx(matrix1);
        matrix1 = NULL;

        if (matrix2) {
            destroyMtrx(matrix2);
            matrix2 = NULL;
        }
    }

    // очистка на случай ошибки
    if (matrix1) destroyMtrx(matrix1);
    if (matrix2) destroyMtrx(matrix2);
    if (result) destroyMtrx(result);

    fclose(file);
    return 0;
}