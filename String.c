#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// �������� ������
String* CreateString(size_t length, const char* initial_value) {
    // ������� ��������� � ������
    String* str = (String*)calloc(1, sizeof(String));
    if (!str) return NULL;

    // ��� ������ ������
    if (length == 0) return str;

    // �������� ����������
    if (!initial_value) {
        free(str);
        return NULL;
    }

    // �������� ������ (+1 ��� '\0')
    str->data = (char*)calloc(length + 1, 1);
    if (!str->data) {
        free(str);
        return NULL;
    }

    // ����������� � �������
    size_t copy_len = strlen(initial_value);
    if (copy_len > length) copy_len = length;
    memcpy(str->data, initial_value, copy_len);
    str->data[copy_len] = '\0';
    str->length = length;

    return str;
}

// ������� �������� ������
void StringDelete(String* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

// ������������
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

    // ����������� ������ �� ����� �����
    memcpy((*res)->data, str1->data, str1->length);
    memcpy((*res)->data + str1->length, str2->data, str2->length);
    (*res)->data[total_len] = '\0';
}

void StringMultiply(void* result, const void* a, const void* b) {
    // ��� ����� ��������� - ��� ������������
    StringAdd(result, a, b);
}

// ������� ������ � ����
void StringPrint(FILE* file, const void* data) {
    const String* str = (const String*)data;
    if (str && str->data) {
        fprintf(file, "%s", str->data);
    }
    else {
        fprintf(file, "NULL");
    }
}

// ������� ������ �� �����
int StringRead(FILE* file, void* data) {
    if (!file || !data) return 0;

    String* str = (String*)data;
    char buffer[1024];

    // ������ ������
    if (!fgets(buffer, sizeof(buffer), file)) {
        return 0;
    }

    // �������� \n
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    // ���������� ������ ������
    char* new_data = (char*)malloc(len + 1);
    if (!new_data) return 0;
    memcpy(new_data, buffer, len + 1);

    // ���������� ������������ ������� data
    if (str->data) {
        // ������ �������� ���������
        if (IsValidPointer(str->data)) {
            free(str->data);
        }
    }

    str->data = new_data;
    str->length = len;
    return 1;
}

// ������� �������� ��������� - ��������
static int IsValidPointer(void* p) {
    // �������� �� NULL
    if (!p) return 0;

    // �������� �� ������������� (������ ��������� ��������� �� 4/8 ����)
    if ((uintptr_t)p % sizeof(void*) != 0) return 0;

    // �������� �� "��������" �������� �������
    const uintptr_t MIN_ADDR = 0x1000;
    const uintptr_t MAX_ADDR = 0x00007FFFFFFF0000; // ��� 64-��� Linux/Windows
    uintptr_t addr = (uintptr_t)p;

    return (addr >= MIN_ADDR && addr <= MAX_ADDR);
}

// ����������� ���� ������ ��� �����
const DataType StringType = {
    .name = "STRING",
    .add = StringAdd,
    .multiply = StringMultiply,
    .scalarMultiply = NULL, // �� ��������������
    .print = StringPrint,
    .read = StringRead,
    .size = sizeof(String)
};

static void register_string_type(void) {
    registerDataType(&StringType);
}

#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*string_registrar)(void) = register_string_type;