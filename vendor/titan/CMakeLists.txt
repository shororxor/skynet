cmake_minimum_required(VERSION 3.18)
project(titan_ext VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} test/test.cpp)

add_subdirectory(vendor/pybind11)

pybind11_add_module(titan src/compile.cpp)

include_directories(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/basics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/linalg
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/calculus
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/optimization
    ${CMAKE_CURRENT_SOURCE_DIR}/include/titan/statistics
)

target_link_libraries(${PROJECT_NAME})