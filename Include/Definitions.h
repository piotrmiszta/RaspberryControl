#ifndef RASPBERRYCONTROL_DEFINITIONS_H
#define RASPBERRYCONTROL_DEFINITIONS_H

/**
 * DEFS FOR ERRORS AND SUCCESSFUL RETURNED FUNCTIONS
 */
#define SUCCESS         (0)
#define E_MALL          (-1)
#define E_FAIL          (-2)
#define E_ARG           (-3)
#define E_FILE_CORRUPT  (-4)
/**
 * Serial errors
 */
#define SERIAL_E_READ       (-10)
#define SERIAL_E_WRITE      (-11)

/**
 * DEFS FOR AUTHOR AND VERSION INFO
 *
*/
#define AUTHOR  ("PIOTR MISZTA")
#define VERSION ("1.0")
#define NAME    ("RASPBERRY PI CONTROL SERVER")

/**
 * When NO_FILE is defined dont print file desc
 * like /home/raspberryControl/Include/main.c In logger
 */
#define NO_FILE

#endif //RASPBERRYCONTROL_DEFINITIONS_H
