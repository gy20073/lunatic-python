// This file will be included by THGenerateAllTypes

case NUMPY_TYPE:
{
    // TODO prevents python's GC from ever deleting the array until the storage is freed
    // Should use newWithDataAndAllocator
    THStorage *storage = THStorage_(newWithData)(
        PyArray_DATA(arrObj),
        PyArray_NBYTES(arrObj) / sizeof(real));

    if (PyArray_SIZE(arrObj) != 0) {
        int ndims = PyArray_NDIM(arrObj);

        THLongStorage *sizes = THLongStorage_newWithSize(ndims);
        size_t sizeDim;
        for (sizeDim = 0; sizeDim < ndims; ++sizeDim) {
            THLongStorage_set(sizes, sizeDim, PyArray_DIM(arrObj, sizeDim));
        }

        THLongStorage *strides = THLongStorage_newWithSize(ndims);
        size_t strideDim;
        for (strideDim = 0; strideDim < ndims; ++strideDim) {
            long s = PyArray_STRIDE(arrObj, strideDim);
            if (s % sizeof(real) != 0) {
                printf("Numpy array is not properly aligned.");
            }
            // numpy uses bytes, torch uses elements
            THLongStorage_set(strides, strideDim, s / sizeof(real));
        }

        THTensor *tensor = THTensor_(newWithStorage)(
            storage,
            0,
            sizes,
            strides);
        luaT_pushudata(L, tensor, torch_Tensor);

        // Remove our extra ref to the storages
        THLongStorage_free(sizes);
        THLongStorage_free(strides);
        THStorage_(free)(storage);
    } else {
        THTensor *tensor = THTensor_(new)();
        luaT_pushudata(L, tensor, torch_Tensor);
    }
    
    ret = 1;
    break;
}
