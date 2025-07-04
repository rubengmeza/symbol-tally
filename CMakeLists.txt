cmake_minimum_required(VERSION 3.28)
project(symbol-tally LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(IMGUI
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(IMGUI)

FetchContent_Declare(IMGUI-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_MakeAvailable(IMGUI-SFML)

set(OpenCV_DIR "build/_deps/opencv/build")
find_package(OpenCV REQUIRED)

# --------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------
set(SOURCES
    src/main.cpp
    src/tally.cpp
    src/app.cpp
)

add_executable(run ${SOURCES})

# --------------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------------
target_link_libraries(run PRIVATE
	ImGui-SFML::ImGui-SFML SFML::Graphics
)

#if(POPPLER_ENABLED)
#    target_link_libraries(run PRIVATE poppler-cpp)
#endif()
