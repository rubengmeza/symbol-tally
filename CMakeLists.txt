cmake_minimum_required(VERSION 3.10)

project(symbol-tally)

set(CMAKE_CXX_STANDARD 23)

# --------------------------------------------------------------------
# SFML
# --------------------------------------------------------------------
add_subdirectory(external/SFML)

# --------------------------------------------------------------------
# POPPLER (can disable) 
# --------------------------------------------------------------------
set(POPPLER_ENABLED FALSE)  

if(POPPLER_ENABLED)
    set(POPPLER_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/poppler/install/include")
    set(POPPLER_LIB_DIR "${CMAKE_SOURCE_DIR}/external/poppler/install/lib")
endif()

# --------------------------------------------------------------------
# OpenCV
# --------------------------------------------------------------------
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/external/opencv/build")
find_package(OpenCV REQUIRED)

# --------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------
set(SOURCES
    src/main.cpp
    src/tally.cpp
    src/app.cpp
)

if(POPPLER_ENABLED)
    list(APPEND SOURCES src/poppler_pdf_handler.cpp)
endif()

add_executable(run ${SOURCES})

# --------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------
target_include_directories(run PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

if(POPPLER_ENABLED)
    target_include_directories(run PRIVATE ${POPPLER_INCLUDE_DIR})
endif()

# --------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------
target_link_libraries(run PRIVATE
    ${OpenCV_LIBS}
    sfml-graphics sfml-window sfml-system
)

if(POPPLER_ENABLED)
    target_link_libraries(run PRIVATE poppler-cpp)
endif()
