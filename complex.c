#define _CRT_SECURE_NO_WARNINGS
#include "complex.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>

void ComplexAdd(void* result, const void* a, const void* b) {
    const ComplexNumber* ca = (const ComplexNumber*)a;
    const ComplexNumber* cb = (const ComplexNumber*)b;
    ComplexNumber* res = (ComplexNumber*)result;

    res->real = ca->real + cb->real;
    res->imag = ca->imag + cb->imag;
}

void ComplexMultiply(void* result, const void* a, const void* b) {
    const ComplexNumber* ca = (const ComplexNumber*)a;
    const ComplexNumber* cb = (const ComplexNumber*)b;
    ComplexNumber* res = (ComplexNumber*)result;

    res->real = ca->real * cb->real - ca->imag * cb->imag;
    res->imag = ca->real * cb->imag + ca->imag * cb->real;
}

void ComplexScalarMultiply(void* result, const void* elem, const void* scalar) {
    const ComplexNumber* c = (const ComplexNumber*)elem;
    double s = *(const double*)scalar;
    ComplexNumber* res = (ComplexNumber*)result;

    res->real = c->real * s;
    res->imag = c->imag * s;
}

void ComplexPrint(FILE* file, const void* data) {
    const ComplexNumber* z = (const ComplexNumber*)data;
    if (z) {
        fprintf(file, "%.2f%+.2fi", z->real, z->imag);
    }
    else {
        fprintf(file, "NULL");
    }
}


int ComplexRead(FILE* file, void* data) {
    ComplexNumber* cn = (ComplexNumber*)data;

    // Пропускаем пробелы
    int c;
    do {
        c = fgetc(file);
        if (c == EOF) return 0;
    } while (isspace(c));
    ungetc(c, file);

    return fscanf(file, "%lf,%lf", &cn->real, &cn->imag) == 2;
}

const DataType ComplexType = {
    .name = "COMPLEX",
    .add = ComplexAdd,
    .multiply = ComplexMultiply,
    .scalarMultiply = ComplexScalarMultiply,
    .print = ComplexPrint,
    .read = ComplexRead,
    .size = sizeof(ComplexNumber)
};

static void register_complex_type(void) {
    registerDataType(&ComplexType);
}

#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (*complex_registrar)(void) = register_complex_type;