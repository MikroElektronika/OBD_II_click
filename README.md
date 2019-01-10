![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# OBD_II Click

- **CIC Prefix**  : OBDII
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : Nov 2017.

---

### Software Support

We provide a library for the OBD_II Click on our [LibStock](https://libstock.mikroe.com/projects/view/2252/obd-ii-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library carries generic functions, neccesasry for communication with the module. 

Key functions :

- ``` obdII_sendCommand ``` - Sending provided command to the module
- ``` obdII_readResponse ``` - Reads current response inside buffer
- ``` obdII_process ``` - State machine function. This function calles frequently.

**Examples Description**

Example demnstrates how to read RPM from your vecihle. 

- System Initialization - Intializes UART module and GPIO pins
- Application Initialization - Power on module and seting it to Automatic protocol detection by sending "ATSP0"
- Application Task - (code snippet) - Sequential send command for RPM and converts readed response to RPM depend on 

```.c
void applicationTask()
{
    uint8_t tmp[ 25 ];

    obdII_sendCommand( &RPM_CMD[0] );
    while( !obdII_responseReady() )
        ;
    obdII_readResponse( &rsp[0] );

    memcpy( &tmp[0], &rsp[11], 4 );
    tmp[5] = 0;
    rpm = xtoi( &tmp[0] );
    rpm = rpm / 4;
    WordToStr(rpm, &tmp[0]);

    mikrobus_logWrite( "Current RPM : ", _LOG_TEXT );
    mikrobus_logWrite( tmp, _LOG_LINE );
}
```

Note that not all vechiles uses same set of commands - so it might happens that routine for reading RPM on your 
vecihle is not same as these one provided inside example.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2252/obd-ii-click) page.

Other mikroE Libraries used in the example:

- Conversions
- String
- Stdlib

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
