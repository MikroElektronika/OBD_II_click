#include "Click_OBD_II_types.h"

const uint8_t _OBDII_POLL_ENABLE = 1;

const uint32_t _OBDII_UART_CFG[ 6 ] = 
{
	9600, 
	0,                        // CPU FQ Parameter will be replaced during init call
	_UART_8_BIT_DATA, 
	_UART_NOPARITY,
    _UART_ONE_STOPBIT, 
    _UART_HIGH_SPEED
};
