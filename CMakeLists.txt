cmake_minimum_required (VERSION 2.6)
project (esirc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(${esirc_SOURCE_DIR}/include)


add_subdirectory(src)

