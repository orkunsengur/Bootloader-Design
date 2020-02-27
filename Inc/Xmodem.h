#ifndef XMODEM_H
#define XMODEM_H

#define STM32F070

#if defined (STM32F070)
 #include "stm32f0xx.h"
#else
 #error "Target MCU header file is not defined or unsupported."
#endif

#define XMODEM_SOH 0x01
#define XMODEM_STX 0x02
#define XMODEM_ETX 0x03
#define XMODEM_EOT 0x04
#define XMODEM_ACK 0x06
#define XMODEM_NAK 0x15
#define XMODEM_CAN 0x18
#define XMODEM_SUB 0x1A

#define XMODEM_DATA_LENGTH 128

uint8_t rxCallback(uint8_t);
extern uint8_t ack;
extern uint8_t nak;
extern uint8_t dataBuffer[XMODEM_DATA_LENGTH];


typedef enum
{
    IDLE = 0, SOH_RECEIVED, PN1_RECEIVED, PN2_RECEIVED, DATA_RECEIVED,
} XMODEM_RX_STATES;

#endif

