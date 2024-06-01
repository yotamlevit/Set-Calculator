cmake_minimum_required(VERSION 3.26)
project(MMN22 C)

set(CMAKE_C_STANDARD 90)

include_directories(.)

add_executable(MMN22
        Errors.c
        Errors.h
        myset.c
        set.c
        set.h
        set.c
        CommandDispatcher.c
        CommandParser.c
        HashMap.c
        HashMap.h
        SetMap.c
)
