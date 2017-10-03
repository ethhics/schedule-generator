cmake_minimum_required(VERSION 3.8)
project(schedule_generator)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES
        src/defs.h
        src/input.c
        src/parse.c
        src/schedule.c)

add_executable(schedule_generator src/main.c ${SOURCE_FILES})
