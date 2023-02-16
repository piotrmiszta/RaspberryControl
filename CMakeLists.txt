cmake_minimum_required(VERSION 3.21)
project(RaspberryControl)
set(CMAKE_C_STANDARD 23)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)

include_directories(${CMAKE_SOURCE_DIR}/Include)

add_executable(RaspberryControl main.c
		${SOURCE_DIR}/ClientInformations.c
		${SOURCE_DIR}/Logger.c
		${SOURCE_DIR}/Serial.c
		${SOURCE_DIR}/Tcpip.c
		)
