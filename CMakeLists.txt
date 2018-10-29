cmake_minimum_required(VERSION 3.12)
project(projet-s3)

add_definitions(-std=c99)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()
