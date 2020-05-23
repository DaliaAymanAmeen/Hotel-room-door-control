#include "stdint.h" 
#include "D:/DALIAA/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "UART.h"

int options = 3; //check out, locked		
char right_password[4]="0000"; 
char password[4]="1111";

void UART_init (void)
{
		SYSCTL_RCGCUART_R |= 0x01; //enable clk to UART
		SYSCTL_RCGCGPIO_R |= 0x01; //enable clk to portA
		UART0_CTL_R &= (~0x01); //disable UART
		UART0_IBRD_R = 520; //baud rate
		UART0_FBRD_R = 53;	//baud rate
		UART0_LCRH_R = 0x0070; //bit 6,5(8bit) //bit 4(buffer)
		UART0_CTL_R  = 0x301; // bit 9,8(Rx,Tx) //bit 0(enable)
		GPIO_PORTA_AFSEL_R |= 0x03; //enable alternative function
		GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x11 ; //to select UART 
		GPIO_PORTA_DEN_R |= 0x03; //enable digital
		GPIO_PORTA_AMSEL_R &= (~0x03); //disable analog
}


char UART_Read (void)
{
		while((UART0_FR_R & 0x0010) != 0){}; //if the buffer not empty(full), return data //check RXFE
		return (char) (UART0_DR_R & 0xFF); //return the data
}

void UART_write (char data)
{
		while((UART0_FR_R & 0x0020) != 0){}; //if the bu //check TXFF	
		UART0_DR_R = data; //set the data
}

		
void PortF_init(void){	
	SYSCTL_RCGCGPIO_R |= 0x00000020; //portF activated
	while( (SYSCTL_RCGCGPIO_R & 0x20)==0 ) {};   
	GPIO_PORTF_DIR_R = 0X0E ; //output pf1,pf2,pf3
	GPIO_PORTF_DEN_R = 0X0E;  //enable digital
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock portF
	GPIO_PORTF_DATA_R=0x00; //led off initially
		
}


void solenoid_unlocked (void)  
{
		GPIO_PORTF_DATA_R=0x04;  //led on
}
	
void solenoid_locked (void) 
{
		GPIO_PORTF_DATA_R=0x00; //led off
}	
	
void check_options (void)	//el mfrod el option hena yegi mn el uart
{
	 if (options == 0) //check in 
	 {		
			int i;
		 	for ( i = 0 ; i < 4 ; i++)
			{
					right_password[i]='1'; //elmfrod enu haykhod da mn el uart //set password
			}
				
	 }
	 
	 	else if (options == 1) //check out
	 {	
			 solenoid_locked ();	
	 }
	 
	 
	  else if (options == 2) //room service
	 {	
				solenoid_unlocked ();  
	 }
	 
	  else if (options == 3) //enter the room
	 {	
			if(check_password("1111")) ///////////el password el mfrod yegeli mn el uart //momkn  akhod el data el awel a7otaha
			{																		//f array password w b3den ab3tu l ckek password
					solenoid_unlocked ();  
			}
			
				else
				{
						solenoid_locked ();	
				}
	 }
	 
 }

 


_Bool check_password(char password[]) 
{	
		int i;
		for ( i = 0 ; i < 4 ; i++)
		{
			if (password[i]!= right_password[i]) return 0;
		}
		
		return 1;
}	
		 

//el password w rakam el room w el option yegoli mn el uart
