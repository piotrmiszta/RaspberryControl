cmake_minimum_required(VERSION 3.21)
project(RaspberryControl)
set(CMAKE_C_STANDARD 23)

add_executable(RaspberryControl main.c Include/Logger.h Source/Logger.c Include/Definitions.h Include/Tcpip.h Source/Tcpip.c)