#define _CRT_SECURE_NO_WARNINGS
#include "Int_Type.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

// функция сложения двух целых чисел
void IntAdd(void* result, const void* a, const void* b) {
    *(int*)result = *(const int*)a + *(const int*)b;
}
 
// функция умножения двух целых чисел
void IntMultiply(void* result, const void* a, const void* b) {
    *(int*)result = *(const int*)a * *(const int*)b;
}

// функция умножения целого числа на скаляр
void IntScalarMultiply(void* result, const void* elem, const void* scalar) {
    *(int*)result = *(const int*)elem * *(const double*)scalar;
}

// функция вывода целого числа в файл
void IntPrint(FILE* file, const void* data) {
    fprintf(file, "%d", *(const int*)data);
}

// функция чтения целого числа из файла
int IntRead(FILE* file, void* data) {
    // пропускаем пробелы и пустые строки
    int c;
    do {
        c = fgetc(file);
        if (c == EOF) return 0;
    } while (isspace(c) && c != '\n');
    ungetc(c, file);

    // читаем число и проверяем успешность чтения
    return fscanf(file, "%d", (int*)data) == 1;
}

// определение типа данных 
const DataType IntType = {
    .name = "INT", // имя типа
    .add = IntAdd, // функция сложения
    .multiply = IntMultiply, // функция умножения
    .scalarMultiply = IntScalarMultiply, // функция умножения на скаляр
    .print = IntPrint, // функция вывода
    .read = IntRead, // функция чтения
    .size = sizeof(int) // размер типа
};
 
// функция регистрации типа
static void register_int_type(void) {
    registerDataType(&IntType);
}

// пециальная секция для автоматической регистрации при старте
#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*int_registrar)(void) = register_int_type;