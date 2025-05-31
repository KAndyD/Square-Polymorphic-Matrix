#ifndef SQUARE_MATRIX_ELEM_H
#define SQUARE_MATRIX_ELEM_H

#include <stdio.h> // ввод
#include <stdlib.h> // память

// структура, описывающая интерфейс для работы с конкретным типом данных
typedef struct DataType {
    const char* name; // имя типа

    // функция сложения двух элементов
    void (*add)(void* result, const void* a, const void* b);
    
    // функция умножения двух элементов
    void (*multiply)(void* result, const void* a, const void* b);
    
    // функция умножения элемента на скаляр
    void (*scalarMultiply)(void* result, const void* elem, const void* scalar);
    
    // функция вывода элемента в файл
    void (*print)(FILE* file, const void* data);
    
    // функция чтения элемента в файл
    int (*read)(FILE* file, void* data);
    
    // размер элемента в байтах
    size_t size;
} DataType;


// элемент матрицы
typedef struct {
	void* data; // указатель на данные
	const DataType* type; // указатель на описание типа данных
} MatrixElement;

// позволяет регистрировать новые типы данных и находить их по имени
typedef struct TypeRegistry {
    const DataType** types; // массив указателя на зарегистрированные типы
    size_t count; // количество зарегистрированных типов
    size_t capacity; // текущая вместимость массива
} TypeRegistry;

// глобальный реестр типов 
extern TypeRegistry typeRegistry;

// функции для работы с реестром
void registerDataType(const DataType* type); // регистрирация новый тип данных в системе
const DataType* findDataTypeByName(const char* name); // нахождение типа данных по имени

#endif