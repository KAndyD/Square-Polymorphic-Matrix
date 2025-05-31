#include "Square_Matrix_Elem.h" // базовые определения элемента матрицы
#include "Square_Matrix.h" // интерфейс работы с матрицами
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <windows.h> // для прописывания типов - платформо-специфические функции

// функция создания матрицы по размеру
SquareMatrix* createMtrx(int size) {
    if (size <= 0) { // проверка корректности размера
        fprintf(stderr, "Error: Size must be positive\n");
        return NULL;
    }

    // выделение памяти под структуру матрицы
    SquareMatrix* matrix = (SquareMatrix*)malloc(sizeof(SquareMatrix));
    if (!matrix) { // проверка существования
        fprintf(stderr, "Error: Memory allocation failed for matrix structure\n");
        return NULL;
    }

    matrix->size = size;
    // выделение памяти под элементы матрицы
    matrix->data = (MatrixElement*)calloc(size * size, sizeof(MatrixElement)); // Используем calloc вместо malloc
    if (!matrix->data) { // проверка данных матрицы
        fprintf(stderr, "Error: Memory allocation failed for matrix data\n");
        free(matrix);
        return NULL;
    }

    // явная инициализация всех элементов
    for (int i = 0; i < size * size; ++i) {
        matrix->data[i].data = NULL;
        matrix->data[i].type = NULL; 
    }

    return matrix;
}

// функция уничтожения матрицы
void destroyMtrx(SquareMatrix* matrix) {
    if (!matrix) return; // если она вообще есть

    if (matrix->data) { // если есть, что очищать
        // освобождение памяти поэлементно
        for (int i = 0; i < matrix->size * matrix->size; ++i) {
            // проверяка обоих полей
            if (matrix->data[i].data) {
                free(matrix->data[i].data); // освобождение данных элемента
                matrix->data[i].data = NULL;
            }
            // type не нужно освобождать, так как он глобальный и const
        }
        free(matrix->data); // освобождение массива элементов
        matrix->data = NULL;
    }

    free(matrix); // освобождение самой структуры
}

// получение элемента матрицы по строке и столбцу
void* getElem(const SquareMatrix* matrix, int row, int col) {
    // проверка корректности параметров
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        return NULL;
    }
    // индекс в одномерном массиве
    int index = row * matrix->size + col;

    // проверка существования элемента
    if (!matrix->data || !matrix->data[index].data) {
        fprintf(stderr, "Error: Element at (%d, %d) is NULL\n", row, col);
        return NULL;
    }

    return matrix->data[index].data; // возвращение элемента по индексу
}

// установка элемента матрицы по строке, столбцу, значению и типу
int setElem(SquareMatrix* matrix, int row, int col, void* val, const DataType* type) {
    // проверка входных параметров
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size || !val || !type) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return -1;
    }

    // проверка наличия данных матрицы
    if (!matrix->data) {
        fprintf(stderr, "Error: Matrix data is NULL\n");
        return -1;
    }

    int index = row * matrix->size + col;

    // освобождение старого значения
    if (matrix->data[index].data) {
        free(matrix->data[index].data);
    }

    // выделение памяти и копирование данных
    matrix->data[index].data = malloc(type->size);
    if (!matrix->data[index].data) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }

    // копирование сырых бинарных данных из одного участка памяти в другой
    // memcpy(куда, откуда, сколько_байт);
    memcpy(matrix->data[index].data, val, type->size);

    // установка типа элемента
    matrix->data[index].type = type;

    return 0;
}

// функция вывода матрицы
int printMtrx(const SquareMatrix* matrix) {
    // проверка наличия матрицы
    if (!matrix) {
        fprintf(stderr, "Error: Matrix is NULL\n");
        return -1;
    }

    // проверка наличия данных
    if (!matrix->data) {
        fprintf(stderr, "Error: Matrix data is NULL\n");
        return -1;
    }

    for (int i = 0; i < matrix->size; ++i) {
        for (int j = 0; j < matrix->size; ++j) {
            int index = i * matrix->size + j;
            MatrixElement* element = &matrix->data[index]; // получение элемента по индексу

            // проверка элемента
            if (!element || !element->data) {
                printf("NULL ");
                continue;
            }

            // проверка наличия функции вывода
            if (!element->type || !element->type->print) {
                printf("Unprintable ");
            }
            else {
                element->type->print(stdout, element->data); // вывод элемента
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}