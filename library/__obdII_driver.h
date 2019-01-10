/*
    __obdII_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __obdII_driver.h
@brief    OBD_II Driver
@mainpage OBD_II Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   OBDII
@brief      OBD_II Click Driver
@{

| Global Library Prefix | **OBDII** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Dec 2017.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _OBDII_H_
#define _OBDII_H_

/** 
 * @macro T_OBDII_P
 * @brief Driver Abstract type 
 */
#define T_OBDII_P    const uint8_t*

/** @defgroup OBDII_COMPILE Compilation Config */              /** @{ */

//  #define   __OBDII_DRV_SPI__                            /**<     @macro __OBDII_DRV_SPI__  @brief SPI driver selector */
//  #define   __OBDII_DRV_I2C__                            /**<     @macro __OBDII_DRV_I2C__  @brief I2C driver selector */                                          
  #define   __OBDII_DRV_UART__                           /**<     @macro __OBDII_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup OBDII_INIT Driver Initialization */              /** @{ */

#ifdef   __OBDII_DRV_SPI__
void obdII_spiDriverInit(T_OBDII_P gpioObj, T_OBDII_P spiObj);
#endif
#ifdef   __OBDII_DRV_I2C__
void obdII_i2cDriverInit(T_OBDII_P gpioObj, T_OBDII_P i2cObj, uint8_t slave);
#endif
#ifdef   __OBDII_DRV_UART__
void obdII_uartDriverInit(T_OBDII_P gpioObj, T_OBDII_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup OBDII_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Reset sequence
 *
 * Resets the OBD II click.
 */
void obdII_reset();

/**
 * @brief Interrupt pin state
 *
 * Returns current state of the interrupt pin.
 */
uint8_t obdII_getIntState();

/**
 * @brief Putc function
 *
 * @param[in] input received character
 *
 * This function is used to put new characters received to the RX buffer.
 * In case of polling disabled this function should be placed inside 
 * UART ISR.
 */
void obdII_putc( uint8_t input );

/**
 * @brief Read response
 *
 * @param[out] output received response
 *
 * This function copies received response to the provided location. 
 * Maximum size of the response is 256 bytes so provided array must 
 * be at least 256 charactes wide.
 */
void obdII_readResponse( uint8_t *output );

/**
 * @brief Send command
 *
 * @param[in] command 
 *
 * Provided command should be string without any additional characters.
 */
void obdII_sendCommand( const uint8_t *command );

/**
 * @brief Response Ready 
 *
 * Function returns the state of response.
 */
uint8_t obdII_responseReady();

/**
 * @brief State machine
 *
 * This function is neccesary in case of polling enabled. It should be
 * placed inside infinite loop which is called as frequently as possible.
 */
void obdII_process();
                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_OBD_II_STM.c
    @example Click_OBD_II_TIVA.c
    @example Click_OBD_II_CEC.c
    @example Click_OBD_II_KINETIS.c
    @example Click_OBD_II_MSP.c
    @example Click_OBD_II_PIC.c
    @example Click_OBD_II_PIC32.c
    @example Click_OBD_II_DSPIC.c
    @example Click_OBD_II_AVR.c
    @example Click_OBD_II_FT90x.c
    @example Click_OBD_II_STM.mbas
    @example Click_OBD_II_TIVA.mbas
    @example Click_OBD_II_CEC.mbas
    @example Click_OBD_II_KINETIS.mbas
    @example Click_OBD_II_MSP.mbas
    @example Click_OBD_II_PIC.mbas
    @example Click_OBD_II_PIC32.mbas
    @example Click_OBD_II_DSPIC.mbas
    @example Click_OBD_II_AVR.mbas
    @example Click_OBD_II_FT90x.mbas
    @example Click_OBD_II_STM.mpas
    @example Click_OBD_II_TIVA.mpas
    @example Click_OBD_II_CEC.mpas
    @example Click_OBD_II_KINETIS.mpas
    @example Click_OBD_II_MSP.mpas
    @example Click_OBD_II_PIC.mpas
    @example Click_OBD_II_PIC32.mpas
    @example Click_OBD_II_DSPIC.mpas
    @example Click_OBD_II_AVR.mpas
    @example Click_OBD_II_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __obdII_driver.h

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

