project(lin_eq)

cmake_minimum_required(VERSION 3.12)


set(SRC_FILES matrix.c core.c solving_methods.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
add_definitions("-O")
add_executable(lin_eq ${SRC_FILES})
target_link_libraries(lin_eq m)