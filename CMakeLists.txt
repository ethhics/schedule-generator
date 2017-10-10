cmake_minimum_required(VERSION 3.8)
project(schedule_generator)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES
        src/defs.h
        src/input.c
        src/parse.c
        src/schedule.c)

set(TEST_FILES
        src/test/input_test.c
        src/test/parse_test.c
        src/test/schedule_test.c)

add_executable(schedule_generator src/main.c ${SOURCE_FILES})

add_executable(test_suite src/test/test.c ${TEST_FILES} ${SOURCE_FILES})