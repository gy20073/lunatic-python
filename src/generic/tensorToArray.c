// This file will be included by THGenerateAllTypes
#define torch_Tensor TH_CONCAT_STRING_3(torch.,Real,Tensor)
#define torch_Storage TH_CONCAT_STRING_3(torch.,Real,Storage)

{
  THTensor *tensor = luaT_toudata(L, n, torch_Tensor);
  if (tensor) {
    // Can we work with the given storage?
    THStorage* storage = THTensor_(storage)(tensor);
    if ((storage->flag & TH_STORAGE_RESIZABLE)==0) {
      printf("Trying to create an array from a fixed tensor. Abording.\n");
      break;
    }

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

    // Numpy will prevent any resizing of the underlying storage
    // The storage will not be released since we have a ref to the storage
    // that will exist until this numpy array exists
    LuaObject *luaObj = PyObject_New(LuaObject, &LuaObject_Type);
    THStorage_(retain)(storage);
    luaT_pushudata(LuaState, storage, torch_Storage);
    luaObj->ref = luaL_ref(LuaState, LUA_REGISTRYINDEX);
    luaObj->refiter = 0;
    int r = PyArray_SetBaseObject((PyArrayObject*)ret, (PyObject*)luaObj);
    if(r) {
      printf("Error linking the Tensor to the numpy array.\n");
    }

    if(dimsPtr) {
      free(dimsPtr);
    }
    if(stridesPtr) {
      free(stridesPtr);
    }
    break;
  }
}

#undef torch_Tensor
#undef torch_Storage
