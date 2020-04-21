project(lin_eq)

cmake_minimum_required(VERSION 3.12)

include_directories(../libraries/include)
link_directories(../libraries/lib)

set(SRC_FILES matrix.c core.c argparser.c)
add_definitions("-O")
add_executable(mnap ${SRC_FILES})
target_link_libraries(mnap config)
target_link_libraries(mnap m)