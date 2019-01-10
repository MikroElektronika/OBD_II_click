/*
Example for OBD_II Click

    Date          : Dec 2017.
    Author        : MikroE Team

Test configuration AVR :
    
    MCU              : ATMEGA32
    Dev. Board       : EasyAVR v7 
    AVR Compiler ver : v7.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO pins, and two UART modules. First one for 
communication with OBD II click and second one for data logging
- Application Initialization - Initializes OBD II Driver and setups auto mode.
- Application Task - (code snippet) - Sequentially queries OBD II click for 
current RPM. OBD II click provides response about current RPM in hexadecimal format 
so it is converted to decimal format and logged using UART module for information logging.

NOTE :

This example will not work on all vehicles because not all car manufacturers uses same
format of messages for diagnostic.

*/

#include "Click_OBD_II_types.h"
#include "Click_OBD_II_config.h"

const uint8_t OBDII_AUTOMODE[6] = "ATSP0";
const uint8_t RPM_CMD[5] = "010C";

uint16_t rpm;
uint8_t rsp[ 256 ];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_uartInit( _MIKROBUS1, &_OBDII_UART_CFG[0] );
    // mikrobus_logInit( _MIKROBUS3, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    obdII_uartDriverInit( (T_OBDII_P)&_MIKROBUS1_GPIO, (T_OBDII_P)&_MIKROBUS1_UART );
    obdII_sendCommand( &OBDII_AUTOMODE[0] );
    
    // mikrobus_logWrite( "OBD II initialized", _LOG_LINE );
}

void applicationTask()
{
    uint8_t res;
    uint8_t tmp[ 25 ];

    res = 0;

    obdII_sendCommand( &RPM_CMD[0] );

    while(res == 0)
    {
        res = obdII_responseReady();
        obdII_process();
    } 
        
    obdII_readResponse( &rsp[0] );

    memcpy( &tmp[0], &rsp[11], 4 );
    tmp[5] = 0;
    rpm = xtoi( &tmp[0] );
    rpm = rpm / 4;
    WordToStr(rpm, &tmp[0]);

    // mikrobus_logWrite( "Current RPM : ", _LOG_TEXT );
    // mikrobus_logWrite( tmp, _LOG_LINE );

    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }

