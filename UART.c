#include "stdint.h" 
#include "D:/DALIAA/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "UART.h"
#include "Keypad.h"

char options = '0'; 
char room_num = '1';
char right_password[4]="0000"; 
char password[4]="1111";
char setup_rooms[4]="0000";
int flag_occupied = 0; //check this flag before case entering the room (check if the room is checked in or not)

void UART_init (void)
{
		SYSCTL_RCGCUART_R |= 0x01; //enable clk to UART
		//while( (SYSCTL_RCGCGPIO_R & 0x01)==0 ) {};   
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
		while((UART0_FR_R & 0x0020) != 0){}; //if the buffer not full , you can write data //check TXFF	
		UART0_DR_R = data; //set the data
}
 
		
void PortF_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000020; //portF activated
	while( (SYSCTL_RCGCGPIO_R & 0x20)==0 ) {};   
	GPIO_PORTF_DIR_R = 0X0E ; //output pf1,pf2,pf3
	GPIO_PORTF_DEN_R = 0X0E;  //enable digital
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock portF
	GPIO_PORTF_DATA_R=0x00; //led off initially
		
}

void setup (void)
{
	int i;
	for (i=0 ; i<5 ; i++)
	{
		setup_rooms[i] = UART_Read();
	}
	//assumption that first enterd room number is the room which is connected to the keypad, UART, and solenoid
}
	

void solenoid_unlocked (void)  
{
		GPIO_PORTF_DATA_R=0x08;  //led on
}
	
void solenoid_locked (void) 
{
		GPIO_PORTF_DATA_R=0x00; //led off
}	
	
void check_options (void)	
{
	 if (options == '0') //check in 
		 {		
			 int i;
			 for ( i = 0 ; i < 4 ; i++)
			 {
				 right_password[i] = UART_Read ();  //set password
			 }
			 flag_occupied = 1;
		 }
	 
	 	else if (options == '1') //check out
	 {	
			 flag_occupied = 0 ;
			 solenoid_locked ();	
	 }
	 
	 
	  else if (options == '2') //room service
	 {	
				solenoid_unlocked ();  
	 }
	 
	 
			// el mfrod ashel el option da w akhali el password ytakhed mn el keypad + y check el awel mn flag_occ
	  else  //enter the room and check the password
			{	
				if (flag_occupied == 1) //already the room is checked in
				{
					 int i;
					 for ( i = 0 ; i < 4 ; i++)
					 {
						 password[i] = (char)KeyPad_getPressedKey(); //get password from keypad
					 }
					 
						if(check_password(password)) //check the entered password
							{																		
								solenoid_unlocked ();  
							}
							else
								{
									solenoid_locked ();	
								}
					}
					else //the room is not checked in
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


void PortC_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000004; //portC activated
	while( (SYSCTL_RCGCGPIO_R & 0x04)==0 ) {};   
	GPIO_PORTC_DIR_R = 0X00; //input 
	GPIO_PORTC_DEN_R = 0XFF;  //enable digital
	GPIO_PORTC_DATA_R=0x00; 
		
}

void PortD_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000008; //portD activated
	while( (SYSCTL_RCGCGPIO_R & 0x08)==0 ) {}; 
	GPIO_PORTD_DIR_R = 0X00 ; //input 
	GPIO_PORTD_DEN_R = 0XFF;  //enable digital
	GPIO_PORTD_DATA_R=0x00; 
		
}