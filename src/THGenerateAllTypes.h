#ifndef TH_GENERIC_FILE
#error "You must define TH_GENERIC_FILE before including THGenerateAllTypes.h"
#endif

// Short and Char types have been removed
// Added a define NUMPY_TYPE for the corresponding numpy object
// and torch_Tensor that is not defined in TH

#define real unsigned char
#define accreal long
#define Real Byte
#define NUMPY_TYPE NPY_UINT8
#define TH_REAL_IS_BYTE
#line 1 TH_GENERIC_FILE
#include TH_GENERIC_FILE
#undef real
#undef accreal
#undef Real
#undef NUMPY_TYPE
#undef TH_REAL_IS_BYTE

#define real int
#define accreal long
#define Real Int
#define NUMPY_TYPE NPY_UINT32
#define TH_REAL_IS_INT
#line 1 TH_GENERIC_FILE
#include TH_GENERIC_FILE
#undef real
#undef accreal
#undef Real
#undef NUMPY_TYPE
#undef TH_REAL_IS_INT

#define real long
#define accreal long
#define Real Long
#define NUMPY_TYPE NPY_UINT64
#define TH_REAL_IS_LONG
#line 1 TH_GENERIC_FILE
#include TH_GENERIC_FILE
#undef real
#undef accreal
#undef Real
#undef NUMPY_TYPE
#undef TH_REAL_IS_LONG

#define real float
#define accreal double
#define Real Float
#define NUMPY_TYPE NPY_FLOAT
#define TH_REAL_IS_FLOAT
#line 1 TH_GENERIC_FILE
#include TH_GENERIC_FILE
#undef real
#undef accreal
#undef Real
#undef NUMPY_TYPE
#undef TH_REAL_IS_FLOAT

#define real double
#define accreal double
#define Real Double
#define NUMPY_TYPE NPY_DOUBLE
#define TH_REAL_IS_DOUBLE
#line 1 TH_GENERIC_FILE
#include TH_GENERIC_FILE
#undef real
#undef accreal
#undef Real
#undef NUMPY_TYPE
#undef TH_REAL_IS_DOUBLE

#undef TH_GENERIC_FILE