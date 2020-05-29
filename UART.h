#include "stdint.h" 
#include "D:/DALIAA/Keil/EE319Kware/inc/tm4c123gh6pm.h"

void UART_init (void);
char UART_Read (void);
void UART_write (char data);
void PortF_init(void);
void solenoid_unlocked (void);
void solenoid_locked (void);
void check_options (void);
_Bool check_password(char password[]);
void PortD_init(void);
void PortC_init(void);