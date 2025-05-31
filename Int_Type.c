#define _CRT_SECURE_NO_WARNINGS
#include "Int_Type.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

// ������� �������� ���� ����� �����
void IntAdd(void* result, const void* a, const void* b) {
    *(int*)result = *(const int*)a + *(const int*)b;
}
 
// ������� ��������� ���� ����� �����
void IntMultiply(void* result, const void* a, const void* b) {
    *(int*)result = *(const int*)a * *(const int*)b;
}

// ������� ��������� ������ ����� �� ������
void IntScalarMultiply(void* result, const void* elem, const void* scalar) {
    *(int*)result = *(const int*)elem * *(const double*)scalar;
}

// ������� ������ ������ ����� � ����
void IntPrint(FILE* file, const void* data) {
    fprintf(file, "%d", *(const int*)data);
}

// ������� ������ ������ ����� �� �����
int IntRead(FILE* file, void* data) {
    // ���������� ������� � ������ ������
    int c;
    do {
        c = fgetc(file);
        if (c == EOF) return 0;
    } while (isspace(c) && c != '\n');
    ungetc(c, file);

    // ������ ����� � ��������� ���������� ������
    return fscanf(file, "%d", (int*)data) == 1;
}

// ����������� ���� ������ 
const DataType IntType = {
    .name = "INT", // ��� ����
    .add = IntAdd, // ������� ��������
    .multiply = IntMultiply, // ������� ���������
    .scalarMultiply = IntScalarMultiply, // ������� ��������� �� ������
    .print = IntPrint, // ������� ������
    .read = IntRead, // ������� ������
    .size = sizeof(int) // ������ ����
};
 
// ������� ����������� ����
static void register_int_type(void) {
    registerDataType(&IntType);
}

// ���������� ������ ��� �������������� ����������� ��� ������
#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*int_registrar)(void) = register_int_type;