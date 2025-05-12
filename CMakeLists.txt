cmake_minimum_required(VERSION 3.10)

project(symbol-tally)

set(CMAKE_CXX_STANDARD 23)

# --------------------------------------------------------------------
# SFML
# --------------------------------------------------------------------
add_subdirectory(external/SFML)

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
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/external/opencv/build")

find_package(OpenCV REQUIRED)

# --------------------------------------------------------------------
# Executable target
# --------------------------------------------------------------------
add_executable(run src/main.cpp src/poppler_pdf_handler.cpp src/tally.cpp src/app.cpp)

# Include OpenCV headers
target_include_directories(run PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link Poppler and OpenCV libraries
target_link_libraries(run PRIVATE poppler-cpp ${OpenCV_LIBS} sfml-graphics sfml-window sfml-system)

# Add RPATH for Poppler and OpenCV
set_target_properties(run PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/external/poppler/install/lib;${CMAKE_SOURCE_DIR}/external/opencv/build/lib"
)


