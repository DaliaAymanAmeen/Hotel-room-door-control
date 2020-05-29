#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "D:/DALIAA/1DALIA/Academic_Projects/Materials/std_types.h"
#include "UART.h"
#ifndef KEYPAD_H_
#define KEYPAD_H_
/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define N_col 4
#define N_row 4
#define Keypad_ROWS_DATA         GPIO_PORTD_DATA_R // ROWS ON PORT D 
#define KeyPad_ROWS_DIR          GPIO_PORTD_DIR_R
#define Keypad_COLUMNS_DATA      GPIO_PORTC_DATA_R //COLUMNS ON PORT C
#define KeyPad_COLUMNS_DIR       GPIO_PORTC_DIR_R
 

/***  functions proto types *///
uint16 Keypad_getpressed(void);
#endif /*KEYPAD_H_*/