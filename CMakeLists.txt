cmake_minimum_required(VERSION 3.12)
project(projet_s3 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(projet_s3
        src/elementliste.c
        src/elementliste.h
        src/global.h
        src/liste.c
        src/liste.h
        src/main.c
        src/utils_sd.c
        src/utils_sd.h src/uninomiales.c src/uninomiales.h)
