cmake_minimum_required(VERSION 3.0)
project(schedule_generator)

set(CMAKE_C_STANDARD 90)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(SOURCE_FILES
        defs.h
        input.c
        parse.c
        schedule.c)

set(TEST_FILES
        test/input_test.c
        test/parse_test.c
        test/schedule_test.c)

add_executable(schedule_generator main.c ${SOURCE_FILES})

add_executable(test_suite test/test.c ${TEST_FILES} ${SOURCE_FILES})
