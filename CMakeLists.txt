cmake_minimum_required(VERSION 3.21)
project(RaspberryControl)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(RaspberryControl main.c
			Include/ClientInformations.h	Source/ClientInformations.c
			Include/Logger.h		Source/Logger.c
			Include/Serial.h		Source/Serial.c
			Include/Tcpip.h			Source/Tcpip.c
			Include/Definitions.h)
