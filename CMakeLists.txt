cmake_minimum_required(VERSION 3.20)

project(AutopPainter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)

add_library(autopainter_core
    src/command.cpp
    src/image_classifier.cpp
    src/json_writer.cpp
    src/palette.cpp
    src/planner.cpp
)

target_include_directories(autopainter_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(autopainter_core
    PUBLIC
        ${OpenCV_LIBS}
)

add_executable(autopainter src/main.cpp)
target_link_libraries(autopainter PRIVATE autopainter_core)
