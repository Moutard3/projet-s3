cmake_minimum_required(VERSION 3.12)
project(projet-s3)

add_definitions(-std=c99)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

#target_include_directories(projet_s3 PRIVATE src)
add_executable(projet_s3
        src/main.c
        src/global.h
        src/liste.h
        src/elementliste.h
        src/liste.c
        src/elementliste.c
        )
