#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// создание строки
String* CreateString(size_t length, const char* initial_value) {
    // создаем структуру с нулями
    String* str = (String*)calloc(1, sizeof(String));
    if (!str) return NULL;

    // для пустой строки
    if (length == 0) return str;

    // проверка параметров
    if (!initial_value) {
        free(str);
        return NULL;
    }

    // выделяем память (+1 для '\0')
    str->data = (char*)calloc(length + 1, 1);
    if (!str->data) {
        free(str);
        return NULL;
    }

    // копирование с защитой
    size_t copy_len = strlen(initial_value);
    if (copy_len > length) copy_len = length;
    memcpy(str->data, initial_value, copy_len);
    str->data[copy_len] = '\0';
    str->length = length;

    return str;
}

// функция удаления строки
void StringDelete(String* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

// конкатенация
void StringAdd(void* result, const void* a, const void* b) {
    const String* str1 = (const String*)a;
    const String* str2 = (const String*)b;

    if (!str1 || !str2) {
        fprintf(stderr, "Error: NULL string in StringAdd\n");
        return;
    }

    size_t total_len = str1->length + str2->length;
    String** res = (String**)result;
    *res = CreateString(total_len, "");

    if (!*res) return;

    // копирование данных из обеих строк
    memcpy((*res)->data, str1->data, str1->length);
    memcpy((*res)->data + str1->length, str2->data, str2->length);
    (*res)->data[total_len] = '\0';
}

void StringMultiply(void* result, const void* a, const void* b) {
    // для строк умножение - это конкатенация
    StringAdd(result, a, b);
}

// функция вывода в файл
void StringPrint(FILE* file, const void* data) {
    const String* str = (const String*)data;
    if (str && str->data) {
        fprintf(file, "%s", str->data);
    }
    else {
        fprintf(file, "NULL");
    }
}

// функция чтения из файла
int StringRead(FILE* file, void* data) {
    if (!file || !data) return 0;

    String* str = (String*)data;
    char buffer[1024];

    // чтение строки
    if (!fgets(buffer, sizeof(buffer), file)) {
        return 0;
    }

    // удаление \n
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    // безопасная замена данных
    char* new_data = (char*)malloc(len + 1);
    if (!new_data) return 0;
    memcpy(new_data, buffer, len + 1);

    // безопасное освобождение старого data
    if (str->data) {
        // полная проверка указателя
        if (IsValidPointer(str->data)) {
            free(str->data);
        }
    }

    str->data = new_data;
    str->length = len;
    return 1;
}

// Функция проверки указателя - рудимент
static int IsValidPointer(void* p) {
    // Проверка на NULL
    if (!p) return 0;

    // Проверка на выровненность (обычно указатели выровнены по 4/8 байт)
    if ((uintptr_t)p % sizeof(void*) != 0) return 0;

    // Проверка на "разумный" диапазон адресов
    const uintptr_t MIN_ADDR = 0x1000;
    const uintptr_t MAX_ADDR = 0x00007FFFFFFF0000; // Для 64-бит Linux/Windows
    uintptr_t addr = (uintptr_t)p;

    return (addr >= MIN_ADDR && addr <= MAX_ADDR);
}

// определение типа данных для строк
const DataType StringType = {
    .name = "STRING",
    .add = StringAdd,
    .multiply = StringMultiply,
    .scalarMultiply = NULL, // Не поддерживается
    .print = StringPrint,
    .read = StringRead,
    .size = sizeof(String)
};

static void register_string_type(void) {
    registerDataType(&StringType);
}

#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*string_registrar)(void) = register_string_type;