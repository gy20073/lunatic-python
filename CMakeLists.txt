CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})

file(GLOB src src/*.c)
SET(luasrc "lpython.lua")

ADD_TORCH_PACKAGE(lpython "${src}" "${luasrc}")

# Link with the appropriate libraries for the C code
# TH because we use Tensors in our code
TARGET_LINK_LIBRARIES(lpython TH luaT ${PYTHON_LIBRARIES})
