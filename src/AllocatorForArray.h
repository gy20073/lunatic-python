#ifndef ALLOCATORFORARRAY_H
#define ALLOCATORFORARRAY_H

#include "TH.h"
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

void allocForArrayInit(void);
THAllocator* getAllocForArray(void);

void* npy_malloc(void* ctx, long size);
void* npy_realloc(void* ctx, void* ptr, long size);
void npy_free(void* ctx, void* ptr);

#endif
