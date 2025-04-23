cmake_minimum_required(VERSION 3.10)

project(symbol-tally)

set(CMAKE_CXX_STANDARD 23)

# where i installed poppler. need include and library.
set(POPPLER_INCLUDE_DIR "external/poppler/install/include")
set(POPPLER_LIB_DIR "external/poppler/install/lib")

include_directories(${POPPLER_INCLUDE_DIR})
link_directories(${POPPLER_LIB_DIR})

add_executable(run main.cpp)

target_link_libraries(run poppler-cpp)

