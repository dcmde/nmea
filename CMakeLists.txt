cmake_minimum_required(VERSION 3.17)
project(nmea)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

include_directories(include)

set(USER_SRC
        main.cpp
        src/nmea.c)

add_executable(nmea ${USER_SRC})
