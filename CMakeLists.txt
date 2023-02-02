cmake_minimum_required(VERSION 3.21)
project(RaspberryControl)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS "-Werror")
set(CMAKE_C_FLAGS "-O0")

add_executable(RaspberryControl main.c Include/Logger.h Source/Logger.c Include/Definitions.h Include/Tcpip.h Source/Tcpip.c Source/Serial.c Include/Serial.h)