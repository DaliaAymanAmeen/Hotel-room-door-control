#include "stdint.h" 
#include "tm4c123gh6pm.h"
#include "UART.h"
void  SystemInit(){}
	
	
int main ()	
{
		extern char options;
		extern char right_password[4];
		extern char password[4];
		extern char room_num;
		extern char setup_rooms[4];
		extern int flag_occupied; 
		PortF_init();	
		PortC_init();
		PortD_init();
		UART_init ();
		setup ();
	
		while(1)
		{
				room_num =  UART_Read ();
				
				if (room_num == setup_rooms[0]) //assumption that first enterd room number in the array is the room which is connected to the keypad, UART, and solenoid
				{
					options = UART_Read ();
					check_options ();
					
					
				}					
		}
		
		
}
	



