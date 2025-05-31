#define _CRT_SECURE_NO_WARNINGS
#include "Matrix_IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * глобальный реестр типов данных
 * хранит все зарегистрированные в системе типы матричных элементов
 * инициализируется нулями (NULL, 0, 0) при старте программы
 * - types: массив указателей на зарегистрированные типы
 * - count: текущее количество типов
 * - capacity: текущая вместимость массива
 */
TypeRegistry typeRegistry = { NULL, 0, 0 };

// регистрация нового типа данных в системе
void registerDataType(const DataType* type) {
    // увеличиваем буфер при необходимости
    if (typeRegistry.count >= typeRegistry.capacity) {
        // увеличиваем емкость в 2 раза или до 4 (если была 0)
        size_t new_capacity = typeRegistry.capacity ? typeRegistry.capacity * 2 : 4;
        
        // перевыделяем память с новым размером
        const DataType** new_types = realloc(typeRegistry.types, new_capacity * sizeof(DataType*));
        
        if (!new_types) return;

        typeRegistry.types = new_types;
        typeRegistry.capacity = new_capacity;
    }

    // добавляем тип в реестр
    typeRegistry.types[typeRegistry.count++] = type;
}

// функция нахождения типа данных по имени
const DataType* findDataTypeByName(const char* name) {
    // линейный поиск по всем зарегистрированным типам
    for (size_t i = 0; i < typeRegistry.count; i++) {
        if (strcmp(typeRegistry.types[i]->name, name) == 0) {
            return typeRegistry.types[i]; // тип найден
        }
    }
    return NULL; // тип не найден
}

// функция чтения матрицы из файла
SquareMatrix* readMatrixFromFile(FILE* file, int size, const DataType* type) {
    // проверка корректности входных параметров
    if (!file || size <= 0 || !type) {
        fprintf(stderr, "Invalid arguments to readMatrixFromFile\n");
        return NULL;
    }

    printf("Reading matrix of type %s, size %dx%d\n", type->name, size, size);

    // создание матрицы
    SquareMatrix* matrix = createMtrx(size);
    if (!matrix) return NULL; // проверка успешного создания

    // чтение элементов матрицы
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            MatrixElement* elem = &matrix->data[i * size + j];
            elem->type = type; // установка типа элемента
            
            // выделение памяти под данные элементы
            elem->data = malloc(type->size);

            if (!elem->data) {
                fprintf(stderr, "Memory allocation failed for element [%d][%d]\n", i, j);
                destroyMtrx(matrix);
                return NULL;
            }

            printf("Reading [%d][%d] as %s...", i, j, type->name);
            // использование функции чтения для конкретного типа
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

// функция записи матрицы в файл
void writeMatrixToFile(const SquareMatrix* matrix, const char* filename) {
    // проверка входных параметров
    if (!filename) {
        fprintf(stderr, "Error: NULL filename in writeMatrixToFile\n");
        return;
    }

    // открытие файла для записи
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    // обработка случая с пустой матрицей
    if (!matrix) {
        fprintf(file, "Matrix is NULL\n");
        fclose(file);
        return;
    }

    // поэлементная запись
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

// функция чтения типа данных из файла
const DataType* readTypeFromFile(FILE* file) {
    char type_str[20];
    // чтение строки с именем типа
    if (fscanf(file, "%19s", type_str) != 1) {
        fprintf(stderr, "Error reading type from file\n");
        return NULL;
    }
    type_str[19] = '\0'; // гарантированное завершение строки

    // поиск типа в реестре
    const DataType* type = findDataTypeByName(type_str);
    if (!type) {
        fprintf(stderr, "Unknown type: %s\n", type_str);
    }
    return type;
}