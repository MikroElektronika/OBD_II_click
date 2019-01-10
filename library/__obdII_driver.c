/*
    __obdII_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__obdII_driver.h"
#include "__obdII_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __OBDII_DRV_I2C__
static uint8_t _slaveAddress;
#endif

extern const uint8_t _OBDII_POLL_ENABLE;

static volatile uint16_t rx_cnt;
static volatile uint8_t  rsp_f;
static volatile uint8_t  rx_buffer[ 256 ];

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void _strcpy(uint8_t *dest, uint8_t *src);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void _strcpy(uint8_t *dest, uint8_t *src)
{
    char *tmp = dest;

    uint16_t i = 0;
    uint16_t j = 0;

    while ((dest[i++] = src[j++]) != '\0')
        ;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __OBDII_DRV_SPI__

void obdII_spiDriverInit(T_OBDII_P gpioObj, T_OBDII_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __OBDII_DRV_I2C__

void obdII_i2cDriverInit(T_OBDII_P gpioObj, T_OBDII_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __OBDII_DRV_UART__

void obdII_uartDriverInit(T_OBDII_P gpioObj, T_OBDII_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    rx_cnt = 0;
    rsp_f  = 0;

    hal_gpio_rstSet( 1 );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void obdII_reset()
{
    hal_gpio_rstSet( 0 );
    Delay_1sec();
    hal_gpio_rstSet( 1 );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

uint8_t obdII_getIntState()
{
    return hal_gpio_intGet();
}

void obdII_putc( uint8_t input )
{
    rx_buffer[ rx_cnt++ ] = input;

    if (0 == rsp_f)
    {
        if (rx_buffer[ rx_cnt - 1 ] == '>')
        {
            rsp_f = 1;
            rx_buffer[ --rx_cnt ] = 0;
        }
    }
}

void obdII_readResponse( uint8_t *output )
{
    _strcpy( output, rx_buffer );

    rsp_f = 0;
    rx_cnt = 0;
    rx_buffer[0] = 0;
}

void obdII_sendCommand( const uint8_t *command )
{
    uint16_t cnt = 0;

    rx_cnt = 0;
    rsp_f  = 0;
    rx_buffer[0] = 0;

    while (0 != command[cnt] )
        hal_uartWrite( command[cnt++] );

    hal_uartWrite( 13 );
    hal_uartWrite( 10 );
}

uint8_t obdII_responseReady()
{
    return rsp_f;
}

void obdII_process()
{
    uint8_t tmp;

    if (0 != _OBDII_POLL_ENABLE)
    {
        if (hal_uartReady())
        {
            tmp = hal_uartRead();
            obdII_putc( tmp );
        }
    }
}

/* -------------------------------------------------------------------------- */
/*
  __obdII_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */