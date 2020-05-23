#include "stdint.h" 
#include "D:/DALIAA/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "UART.h"
void  SystemInit(){}
	
	
int main ()	
{
		extern int options;
		extern char right_password[4];
		extern char password[4];
		PortF_init();	
	
		while(1)
		{
				options = 0;
				check_options ();	

				options = 3;
				check_options ();	
				
		}
		
		
}
	



