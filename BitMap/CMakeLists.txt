cmake_minimum_required(VERSION 3.15)
project(BitMap C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(BitMap
        expand.c
        expand.h
        general.h
        main.c output.c output.h buildStruct.c buildStruct.h build24BitStruct.c build24BitStruct.h build8BitStruct.c build8BitStruct.h analyse.c analyse.h)
