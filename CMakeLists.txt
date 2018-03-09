cmake_minimum_required(VERSION 3.5)
project(CtpSystem)

add_compile_options(-std=c++11)
#add_compile_options(-lpthread)
set(CMAKE_EXE_LINKER_FLAGS "-lpthread -lrt")

# include directories
INCLUDE_DIRECTORIES(
 ${PROJECT_SOURCE_DIR}/include
 /usr/local/include
 /usr/include
)

# lib directories
LINK_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}/lib
 ${PROJECT_BINARY_DIR}/lib
 /usr/local/lib
 /usr/lib
)

SET(CMAKE_BUILD_TYPE "Debug")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
