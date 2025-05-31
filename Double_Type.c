#define _CRT_SECURE_NO_WARNINGS
#include "Double_Type.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void DoubleAdd(void* result, const void* a, const void* b) {
    *(double*)result = *(const double*)a + *(const double*)b;
}

void DoubleMultiply(void* result, const void* a, const void* b) {
    *(double*)result = *(const double*)a * *(const double*)b;
}

void DoubleScalarMultiply(void* result, const void* elem, const void* scalar) {
    *(double*)result = *(const double*)elem * *(const double*)scalar;
}

void DoublePrint(FILE* file, const void* data) {
    fprintf(file, "%.2lf", *(const double*)data);
}

int DoubleRead(FILE* file, void* data) {
    // пропускаем пробелы
    int c;
    do {
        c = fgetc(file);
        if (c == EOF) return 0;
    } while (isspace(c));
    ungetc(c, file);

    return fscanf(file, "%lf", (double*)data) == 1;
}

const DataType DoubleType = {
    .name = "DOUBLE",
    .add = DoubleAdd,
    .multiply = DoubleMultiply,
    .scalarMultiply = DoubleScalarMultiply,
    .print = DoublePrint,
    .read = DoubleRead,
    .size = sizeof(double)
};

static void register_double_type(void) {
    registerDataType(&DoubleType);
}

#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*double_registrar)(void) = register_double_type;