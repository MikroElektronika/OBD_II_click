_systemInit:
;Click_OBD_II_STM.c,42 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_OBD_II_STM.c,44 :: 		mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
MOVS	R2, #0
MOVS	R1, #1
MOVS	R0, #0
BL	_mikrobus_gpioInit+0
;Click_OBD_II_STM.c,45 :: 		mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
MOVS	R2, #1
MOVS	R1, #7
MOVS	R0, #0
BL	_mikrobus_gpioInit+0
;Click_OBD_II_STM.c,47 :: 		mikrobus_uartInit( _MIKROBUS1, &_OBDII_UART_CFG[0] );
MOVW	R0, #lo_addr(__OBDII_UART_CFG+0)
MOVT	R0, #hi_addr(__OBDII_UART_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_uartInit+0
;Click_OBD_II_STM.c,48 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_OBD_II_STM.c,50 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_OBD_II_STM.c,51 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_OBD_II_STM.c,53 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_OBD_II_STM.c,55 :: 		obdII_uartDriverInit( (T_OBDII_P)&_MIKROBUS1_GPIO, (T_OBDII_P)&_MIKROBUS1_UART );
MOVW	R1, #lo_addr(__MIKROBUS1_UART+0)
MOVT	R1, #hi_addr(__MIKROBUS1_UART+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_obdII_uartDriverInit+0
;Click_OBD_II_STM.c,56 :: 		obdII_sendCommand( &OBDII_AUTOMODE[0] );
MOVW	R0, #lo_addr(_OBDII_AUTOMODE+0)
MOVT	R0, #hi_addr(_OBDII_AUTOMODE+0)
BL	_obdII_sendCommand+0
;Click_OBD_II_STM.c,58 :: 		mikrobus_logWrite( "OBD II initialized", _LOG_LINE );
MOVW	R0, #lo_addr(?lstr1_Click_OBD_II_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_OBD_II_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_OBD_II_STM.c,59 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_OBD_II_STM.c,61 :: 		void applicationTask()
SUB	SP, SP, #32
STR	LR, [SP, #0]
;Click_OBD_II_STM.c,65 :: 		obdII_sendCommand( &RPM_CMD[0] );
MOVW	R0, #lo_addr(_RPM_CMD+0)
MOVT	R0, #hi_addr(_RPM_CMD+0)
BL	_obdII_sendCommand+0
;Click_OBD_II_STM.c,67 :: 		while( !obdII_responseReady() )
L_applicationTask2:
BL	_obdII_responseReady+0
CMP	R0, #0
IT	NE
BNE	L_applicationTask3
;Click_OBD_II_STM.c,68 :: 		obdII_process();
BL	_obdII_process+0
IT	AL
BAL	L_applicationTask2
L_applicationTask3:
;Click_OBD_II_STM.c,70 :: 		obdII_readResponse( &rsp[0] );
MOVW	R0, #lo_addr(_rsp+0)
MOVT	R0, #hi_addr(_rsp+0)
BL	_obdII_readResponse+0
;Click_OBD_II_STM.c,72 :: 		memcpy( &tmp[0], &rsp[11], 4 );
ADD	R0, SP, #4
MOVS	R2, #4
SXTH	R2, R2
MOVW	R1, #lo_addr(_rsp+11)
MOVT	R1, #hi_addr(_rsp+11)
BL	_memcpy+0
;Click_OBD_II_STM.c,73 :: 		tmp[5] = 0;
ADD	R2, SP, #4
ADDS	R1, R2, #5
MOVS	R0, #0
STRB	R0, [R1, #0]
;Click_OBD_II_STM.c,74 :: 		rpm = xtoi( &tmp[0] );
MOV	R0, R2
BL	_xtoi+0
MOVW	R1, #lo_addr(_rpm+0)
MOVT	R1, #hi_addr(_rpm+0)
STRH	R0, [R1, #0]
;Click_OBD_II_STM.c,75 :: 		rpm = rpm / 4;
UXTH	R0, R0
LSRS	R0, R0, #2
STRH	R0, [R1, #0]
;Click_OBD_II_STM.c,76 :: 		WordToStr(rpm, &tmp[0]);
ADD	R1, SP, #4
BL	_WordToStr+0
;Click_OBD_II_STM.c,78 :: 		mikrobus_logWrite( "Current RPM : ", _LOG_TEXT );
MOVW	R0, #lo_addr(?lstr2_Click_OBD_II_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_OBD_II_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_OBD_II_STM.c,79 :: 		mikrobus_logWrite( tmp, _LOG_LINE );
ADD	R0, SP, #4
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_OBD_II_STM.c,81 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask4:
SUBS	R7, R7, #1
BNE	L_applicationTask4
NOP
NOP
NOP
;Click_OBD_II_STM.c,82 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #32
BX	LR
; end of _applicationTask
_main:
;Click_OBD_II_STM.c,84 :: 		void main()
;Click_OBD_II_STM.c,86 :: 		systemInit();
BL	_systemInit+0
;Click_OBD_II_STM.c,87 :: 		applicationInit();
BL	_applicationInit+0
;Click_OBD_II_STM.c,89 :: 		while (1)
L_main6:
;Click_OBD_II_STM.c,91 :: 		applicationTask();
BL	_applicationTask+0
;Click_OBD_II_STM.c,92 :: 		}
IT	AL
BAL	L_main6
;Click_OBD_II_STM.c,93 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
