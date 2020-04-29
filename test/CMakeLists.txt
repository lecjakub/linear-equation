project(tests_lin_eq)
cmake_minimum_required(VERSION 3.12)

include_directories(../vendor/ceedling/vendor/unity/src)
include_directories(../vendor/ceedling/vendor/cmock/src)
include_directories(../vendor/ceedling/vendor/c_exception/lib)
include_directories(../src)
include_directories(../vendor/plugins)
include_directories(../build/test/mocks)
include_directories(../vendor/ceedling/plugins/fake_function_framework/src)
include_directories(support)

set(TST_FILES test_matrix.c test_solving_methods.c)

add_executable(tstap ${TST_FILES})