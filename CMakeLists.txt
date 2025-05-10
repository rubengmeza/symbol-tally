cmake_minimum_required(VERSION 3.10)

project(symbol-tally)

set(CMAKE_CXX_STANDARD 23)

# --------------------------------------------------------------------
# SFML
# --------------------------------------------------------------------
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML/install/lib/cmake/SFML")

include_directories("${CMAKE_SOURCE_DIR}/external/SFML/install/include")
link_directories("${CMAKE_SOURCE_DIR}/external/SFML/install/lib")

#find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# --------------------------------------------------------------------
# POPPLER
# --------------------------------------------------------------------
set(POPPLER_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/poppler/install/include")
set(POPPLER_LIB_DIR "${CMAKE_SOURCE_DIR}/external/poppler/install/lib")

include_directories(${POPPLER_INCLUDE_DIR})
link_directories(${POPPLER_LIB_DIR})

# --------------------------------------------------------------------
# OpenCV
# --------------------------------------------------------------------
# Path to OpenCV (has a config file for use with find_package)
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/external/opencv/install/lib/cmake/opencv4")

find_package(OpenCV REQUIRED)

# --------------------------------------------------------------------
# Executable target
# --------------------------------------------------------------------
add_executable(run src/main.cpp src/poppler_pdf_handler.cpp src/tally.cpp src/app.cpp)

# Include OpenCV headers
target_include_directories(run PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link Poppler and OpenCV libraries
target_link_libraries(run PRIVATE poppler-cpp ${OpenCV_LIBS} sfml-graphics sfml-window sfml-system)
