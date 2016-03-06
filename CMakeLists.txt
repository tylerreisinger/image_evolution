cmake_minimum_required(VERSION 2.8.11)
project(image_evolution)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories("src")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

add_executable(image_evolution ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -march=native")

#list(APPEND CMAKE_CXX_FLAGS "-std=c++14")
#list(APPEND CMAKE_CXX_FLAGS "-march=native")

set(PROJECT_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(image_evolution Qt5::Widgets)
target_link_libraries(image_evolution Qt5::Gui)
target_link_libraries(image_evolution pthread)
