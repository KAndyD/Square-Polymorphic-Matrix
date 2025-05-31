/*#define _CRT_SECURE_NO_WARNINGS

#include "TypeFunctions.h"
#include "Square_Matrix.h"
#include "String.h"
#include "_Complex.h"
#include <stdlib.h>

// связывает каждый тип данных (data_t) с соответствующими функциями для выполнения операций
static TypeFunctions typeFunctions[] = {
    {INT, "INT", (GenericAddFunction)intAdd, NULL, (GenericElementMultiplyFunction)intElementMultiply, sizeof(int), writeInt, readInt},
    {DOUBLE, "DOUBLE", (GenericAddFunction)doubleAdd, NULL, (GenericElementMultiplyFunction)doubleElementMultiply, sizeof(double), writeDouble, readDouble},
    {MY_COMPLEX, "MY_COMPLEX", (GenericAddFunction)addComplex, (GenericScalarMultiplyFunction)Complex_scalarMultiply, (GenericElementMultiplyFunction)complexElementMultiply, sizeof(complex), writeComplex, readComplex},
    {MY_STRING, "MY_STRING", (GenericAddFunction)StringAdd, (GenericScalarMultiplyFunction)String_scalarMultiply, (GenericElementMultiplyFunction)stringElementMultiply, sizeof(String), writeString, readString}
};

// функция поиска операций(функция, которая ищет в массивe TypeFunctions запись по типу)
// НАПРИМЕР
// int a = 5, b = 3, res;
// TypeFunctions* intOps = getTypeFunctions(INT);
// intOps->addFunction(&res, &a, &b); // Вызовет intAdd
TypeFunctions* getTypeFunctions(data_t type) {
    for (size_t i = 0; i < sizeof(typeFunctions) / sizeof(typeFunctions[0]); ++i) {
        if (typeFunctions[i].type == type) {
            return &typeFunctions[i];
        }
    }
    return NULL;
}

// реализация функций записи по типам
void writeInt(FILE* file, void* data) {
    fprintf(file, "%d ", *(int*)data);
}

void writeDouble(FILE* file, void* data) {
    fprintf(file, "%lf ", *(double*)data);
}

void writeComplex(FILE* file, void* data) {
    complex* c = (complex*)data;
    fprintf(file, "%.2lf,%.2lfi ", c->real_part, c->imag_part);
}

void writeString(FILE* file, void* data) {
    String* str = (String*)data;
    fprintf(file, "%zu,%s ", str->length, str->data); // Соответствующая запись длины строки и ее содержания
}


// реализация функций чтения по типам
int readInt(FILE* file, void* data) {
    return fscanf(file, "%d", (int*)data) == 1;
}

int readDouble(FILE* file, void* data) {
    return fscanf(file, "%lf", (double*)data) == 1;
}

int readComplex(FILE* file, void* data) {
    complex* c = (complex*)data;
    return fscanf(file, "%lf,%lfi", &c->real_part, &c->imag_part) == 2;
}

int readString(FILE* file, void* data) {
    String* str = (String*)data;
    size_t length;
    if (fscanf(file, "%zu,", &length) != 1) {
        fprintf(stderr, "Error reading string length\n");
        return 0;
    }

    str->length = length;
    str->data = (char*)malloc((length + 1) * sizeof(char));
    if (!str->data) {
        fprintf(stderr, "Error allocating memory for string data\n");
        return 0;
    }

    // Чтение строки с использованием fgets для безопасности
    if (fgets(str->data, (int)length + 1, file) == NULL) {
        fprintf(stderr, "Error reading string data\n");
        free(str->data);
        str->data = NULL;
        return 0;
    }
    str->data[str->length] = '\0'; 

    size_t len = strlen(str->data);
    if (len > 0 && str->data[len - 1] == '\n') {
        str->data[len - 1] = '\0';
        str->length--;
    }
    return 1;
}
*/