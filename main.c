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
		PortF_init();	
	
		while(1)
		{
				room_num =  UART_Read ();
				options = UART_Read ();
				check_options ();			

		}
		
		
}
	



