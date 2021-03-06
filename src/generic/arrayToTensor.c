// This file will be included by THGenerateAllTypes
#define torch_Tensor TH_CONCAT_STRING_3(torch.,Real,Tensor)

case NUMPY_TYPE:
{

    // We need to have a specific allocator for our storage that will
    // prevent the modification of the underlying array.
    // The numpy array will not be freed not resisable since we have
    // a reference to it. This ref will be freed in the allocator when
    // the tensor will be freed.
    THStorage *storage = THStorage_(newWithDataAndAllocator)(
        PyArray_DATA(arrObj),
        PyArray_NBYTES(arrObj) / sizeof(real),
        getAllocForArray(),
        (void*) arrObj);

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

#undef torch_Tensor
