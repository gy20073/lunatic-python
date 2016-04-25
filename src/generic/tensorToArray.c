// This file will be included by THGenerateAllTypes

{
  THTensor *tensor = luaT_toudata(L, n, torch_Tensor);
  if (tensor) {
    int ndims;
    npy_intp zero = 0;
    npy_intp* dimsPtr;
    npy_intp* stridesPtr = NULL;

    if (THTensor_(nDimension)(tensor) != 0) {
      ndims = THTensor_(nDimension)(tensor);
      dimsPtr = malloc(ndims * sizeof(*dimsPtr));
      size_t sizeDim = 0;
      for(sizeDim=0; sizeDim<ndims; ++sizeDim) {
        dimsPtr[sizeDim] = THTensor_(size)(tensor, sizeDim);
      }

      if (!THTensor_(isContiguous)(tensor)) {
        stridesPtr = malloc(ndims * sizeof(*stridesPtr));
        // Numpy strides use bytes; Torch strides use element counts.
        size_t strideDim = 0;
        for(strideDim=0; strideDim<ndims; ++strideDim) {
          stridesPtr[strideDim] = THTensor_(stride)(tensor, strideDim) * sizeof(real);
        }
      }
    } else {
      ndims = 1;
      dimsPtr = &zero;
    }

    ret = PyArray_New(
        &PyArray_Type, ndims, dimsPtr, NUMPY_TYPE,
        stridesPtr, THTensor_(data)(tensor), 0,
        NPY_ARRAY_ALIGNED, NULL);

    // TODO prevents lua's GC from ever deleting the storage
    // Should use PyArray_SetBaseObject to take care of the lua ref counting

    if(dimsPtr) {
      free(dimsPtr);
    }
    if(stridesPtr) {
      free(stridesPtr);
    }
    break;
  }
}