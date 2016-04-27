#include "AllocatorForArray.h"

static THAllocator THAllocForArray;

void allocForArrayInit(void) {
    THAllocForArray.malloc = &npy_malloc;
    THAllocForArray.realloc = &npy_realloc;
    THAllocForArray.free = &npy_free;
    import_array();
}

THAllocator* getAllocForArray(void) {
    return &THAllocForArray;
}

void* npy_malloc(void* ctx, long size) {
    printf("Tried to allocate memory on a Tensor created from a Numpy array.\n");
    return NULL;
}
void* npy_realloc(void* ctx, void* ptr, long size) {
    printf("Tried to reallocate memory on a Tensor created from a Numpy array.\n");
    return NULL;
}
void npy_free(void* ctx, void* ptr) {
    PyArrayObject *arr = (PyArrayObject *)ctx;
    // We want this to fail if the reference is incorrect
    Py_DECREF(arr);
}

