/*#ifndef TYPE_FUNCTIONS_H
#define TYPE_FUNCTIONS_H

#include "Square_Matrix_Elem.h" // то, где определен data_t


// GenericAddFunction: указатель на функцию сложения двух элементов
// GenericScalarMultiplyFunction: указатель на функцию умножения элемента на скаляр
// GenericElementMultiplyFunction : указатель на функцию умножения двух элементов
typedef void (*GenericAddFunction)(void* result, const void* a, const void* b);
typedef void (*GenericScalarMultiplyFunction)(void* result, const void* matrixElement, const void* scalar);
typedef void (*GenericElementMultiplyFunction)(void* result, const void* a, const void* b);


// cтруктура, содержащая указатели на функции
typedef struct {
    data_t type; // идентификатор типа
    char* name; // строковое имя типа
    GenericAddFunction addFunction; // функция сложения
    GenericScalarMultiplyFunction scalarMultiplyFunction; // функция умножения на скаляр
    GenericElementMultiplyFunction elementMultiplyFunction; // функция умножения
    size_t elementSize; // размер элемента в байтах
    void (*writeFunction)(FILE*, void*); // функция вывода
    int (*readFunction)(FILE*, void*); // функция чтения
} TypeFunctions;

// функция для получения структуры TypeFunctions по имени типа данных
TypeFunctions* getTypeFunctions(data_t type);

// прототипы функций записи
void writeInt(FILE* file, void* data);
void writeDouble(FILE* file, void* data);
void writeComplex(FILE* file, void* data);
void writeString(FILE* file, void* data);

// прототипы функций чтения
int readInt(FILE* file, void* data);
int readDouble(FILE* file, void* data);
int readComplex(FILE* file, void* data);
int readString(FILE* file, void* data);

#endif*/