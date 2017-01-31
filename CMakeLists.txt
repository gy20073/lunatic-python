CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)
FIND_PACKAGE(PythonLibs 2.7 REQUIRED)
FIND_PACKAGE(PythonInterp 2.7 REQUIRED)
include(cmake/FindNumpy.cmake)

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIR} ${NUMPY_INCLUDE_DIR})

FILE(GLOB src src/*.c)
SET(luasrc "init.lua")

ADD_TORCH_PACKAGE(lpython "${src}" "${luasrc}")

# Link with the appropriate libraries for the C code
# TH because we use Tensors in our code
TARGET_LINK_LIBRARIES(lpython TH luaT ${PYTHON_LIBRARIES})
