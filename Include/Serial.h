#ifndef RASPBERRYCONTROL_SERIAL_H
#define RASPBERRYCONTROL_SERIAL_H
#include <stdio.h>
//#include <asm/termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "Logger.h"
#include "Definitions.h"

typedef enum Serial_BaudRate {
    B_0,
    B_50,
    B_75,
    B_110,
    B_134,
    B_150,
    B_200,
    B_300,
    B_600,
    B_1200,
    B_1800,
    B_2400,
    B_4800,
    B_9600,
    B_19200,
    B_38400,
    B_57600,
    B_115200,
    B_230400,
    B_460800,
}Serial_BaudRate;

typedef enum Serial_DataBits{
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
}Serial_DataBits;

typedef enum Serial_StopBits{
    ONE,
    TWO,
}Serial_StopBits;

typedef enum Serial_ParityBit{
    NONE,
    EVEN,
    ODD,
}Serial_ParityBit;

typedef enum Serial_State {
    CLOSED,
    OPEN,
}Serial_State;

typedef struct SerialPort SerialPort;
/**
 * Serial port is setting all parametrs to identify connection to serial port
 */
SerialPort* serial_create(Serial_BaudRate baudRate,
                        Serial_StopBits stopBits,
                        Serial_ParityBit parityBit,
                        Serial_DataBits dataBits,
                        bool echo,
                        const char* device);
/**
 * Constructor for SerialPort
 */
void serial_openPort(SerialPort* serial);
/**
 * Opening serialPort
 */
void serial_closePort(SerialPort* serial);
void serial_close(SerialPort* serial);

void serial_setBaudRate(Serial_BaudRate baudRate, SerialPort* serial);
void serial_setStopBits(Serial_StopBits stopBits, SerialPort* serial);
void serial_setParityBits(Serial_ParityBit parityBit, SerialPort* serial);
void serial_setDataBits(Serial_DataBits dataBits, SerialPort* serial);
void serial_setDevice(const char* device, SerialPort* serial);
void serial_setEcho(bool Enabled, SerialPort* serialPort);
int serial_read(size_t buffSize, char buff[buffSize], SerialPort* serial);
int serial_write(const char* msg, SerialPort* serial);
void* serial_thread(void* arg);

#define SERIAL_CREATE_DEFAULT(device)               serial_create(B_115200, ONE, NONE, EIGHT, CLOSED, device)
#endif //RASPBERRYCONTROL_SERIAL_H
