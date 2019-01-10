#line 1 "E:/git/click-boards/OBD_II_Click_/SW/example/c/ARM/STM/Click_OBD_II_STM.c"
#line 1 "e:/git/click-boards/obd_ii_click_/sw/example/c/arm/stm/click_obd_ii_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "e:/git/click-boards/obd_ii_click_/sw/example/c/arm/stm/click_obd_ii_config.h"
#line 1 "e:/git/click-boards/obd_ii_click_/sw/example/c/arm/stm/click_obd_ii_types.h"
#line 3 "e:/git/click-boards/obd_ii_click_/sw/example/c/arm/stm/click_obd_ii_config.h"
const uint8_t _OBDII_POLL_ENABLE = 1;

const uint32_t _OBDII_UART_CFG [ 4 ] =
{
 9600,
 _UART_8_BIT_DATA,
 _UART_NOPARITY,
 _UART_ONE_STOPBIT
};
#line 1 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 68 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_uartDriverInit( const uint8_t*  gpioObj,  const uint8_t*  uartObj);
#line 79 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_reset();
#line 86 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
uint8_t obdII_getIntState();
#line 97 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_putc( uint8_t input );
#line 108 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_readResponse( uint8_t *output );
#line 117 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_sendCommand( const uint8_t *command );
#line 124 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
uint8_t obdII_responseReady();
#line 132 "e:/git/click-boards/obd_ii_click_/sw/library/__obdii_driver.h"
void obdII_process();
#line 35 "E:/git/click-boards/OBD_II_Click_/SW/example/c/ARM/STM/Click_OBD_II_STM.c"
const uint8_t OBDII_AUTOMODE[6] = "ATSP0";
const uint8_t RPM_CMD[5] = "010C";


uint16_t rpm;
uint8_t rsp[ 256 ];

void systemInit()
{
 mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
 mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

 mikrobus_uartInit( _MIKROBUS1, &_OBDII_UART_CFG[0] );
 mikrobus_logInit( _LOG_USBUART_A, 9600 );

 Delay_ms( 100 );
}

void applicationInit()
{
 obdII_uartDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_UART );
 obdII_sendCommand( &OBDII_AUTOMODE[0] );

 mikrobus_logWrite( "OBD II initialized", _LOG_LINE );
}

void applicationTask()
{
 uint8_t tmp[ 25 ];

 obdII_sendCommand( &RPM_CMD[0] );

 while( !obdII_responseReady() )
 obdII_process();

 obdII_readResponse( &rsp[0] );

 memcpy( &tmp[0], &rsp[11], 4 );
 tmp[5] = 0;
 rpm = xtoi( &tmp[0] );
 rpm = rpm / 4;
 WordToStr(rpm, &tmp[0]);

 mikrobus_logWrite( "Current RPM : ", _LOG_TEXT );
 mikrobus_logWrite( tmp, _LOG_LINE );

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
}
